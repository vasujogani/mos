/**
 * \file
 * \brief init process for child spawning
 */

/*
 * Copyright (c) 2007, 2008, 2009, 2010, 2016, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#include <stdio.h>
#include <stdlib.h>

#include <aos/aos.h>
#include <aos/waitset.h>
#include <aos/morecore.h>
#include <aos/dispatcher_arch.h>
#include <aos/paging.h>
#include <spawn/spawn.h>

#include <mm/mm.h>
#include "mem_alloc.h"

coreid_t my_core_id;
struct bootinfo *bi;

void init_recv_handler(void *arg);

int main(int argc, char *argv[])
{
    errval_t err;

    /* Set the core id in the disp_priv struct */
    err = invoke_kernel_get_core_id(cap_kernel, &my_core_id);
    assert(err_is_ok(err));
    disp_set_core_id(my_core_id);

    debug_printf("init: on core %" PRIuCOREID " invoked as:", my_core_id);
    for (int i = 0; i < argc; i++) {
       printf(" %s", argv[i]);
    }
    printf("\n");

    /* First argument contains the bootinfo location, if it's not set */
    bi = (struct bootinfo*)strtol(argv[1], NULL, 10);
    if (!bi) {
        assert(my_core_id > 0);
    }

    err = initialize_ram_alloc();
    if(err_is_fail(err)){
        DEBUG_ERR(err, "initialize_ram_alloc");
    }

    lmp_endpoint_init();


    // set slot TASKCN_SLOT_INIT_ENDPOINT to be the current endpoint
    // this requires creating an endpoint from the dispatcher because
    // init's CSPACE is not filled out for some reason
    struct capref dispatcher;
    err = slot_alloc(&dispatcher);
    if (err_is_fail(err)) {
        printf("Errrr\n");
    }

    dispatcher_handle_t handle = curdispatcher();
    struct capref dispatch_cap = get_dispatcher_generic(handle)->dcb_cap;

    // copy into selfep slot
    struct capref temp;
    err = slot_alloc(&temp);
    err = cap_retype(temp, dispatch_cap, 0, ObjType_EndPoint, 0, 1);
    err = cap_copy(cap_selfep, temp);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "unable to set up selfep");
        abort();
    }

    // create a channel for open receiving
    struct lmp_chan lc;
    lmp_chan_init(&lc);
    err = endpoint_create(DEFAULT_LMP_BUF_WORDS, &(lc.local_cap), &(lc.endpoint));
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_ENDPOINT_CREATE);
    }

    struct capref init_endpoint = {
        .cnode = cnode_task,
        .slot = TASKCN_SLOT_INITEP,
    };
    err = cap_copy(init_endpoint, lc.local_cap);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_CAP_COPY);
    }
    err = lmp_chan_alloc_recv_slot(&lc);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_LMP_ALLOC_RECV_SLOT);
    }
    err = lmp_chan_register_recv(&lc, get_default_waitset(), MKCLOSURE(init_recv_handler, &lc));
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_CHAN_REGISTER_RECV);
    }

    // spawn_load_by_name("hello", (struct spawninfo *) malloc(sizeof(struct spawninfo)));

    spawn_load_by_name("memeater", (struct spawninfo *) malloc(sizeof(struct spawninfo)));

    debug_printf("Message handler loop\n");
    // Hang around
    struct waitset *default_ws = get_default_waitset();
    while (true) {
        err = event_dispatch(default_ws);
        if (err_is_fail(err)) {
            DEBUG_ERR(err, "in event_dispatch");
            abort();
        }
    }

    return EXIT_SUCCESS;
}

void init_recv_handler(void *arg) {
    errval_t err;
    struct lmp_chan *lc = arg;
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    struct capref recv_cap;
    err = lmp_chan_recv(lc, &msg, &recv_cap);
    if (err_is_fail(err)) {
        printf("WTF\n");
    }
    printf("HEREEE\n");
    struct lmp_chan new_chan;
    err = lmp_chan_accept(&new_chan, DEFAULT_LMP_BUF_WORDS, recv_cap);
    if (err_is_fail(err)) {
        printf("ERR %s\n", err_getstring(err));
    }

    // reset the callback for this current channel
    err = lmp_chan_register_recv(lc, get_default_waitset(), MKCLOSURE(init_recv_handler, arg));
    if (err_is_fail(err)) {
        printf("ERR %s\n", err_getstring(err));
    }

    // send an acknowledgement to the remote domain
    err = lmp_ep_send0(new_chan.remote_cap, LMP_SEND_FLAGS_DEFAULT, NULL_CAP);
    if (err_is_fail(err)) {
        printf("ERR %s\n", err_getstring(err));
    }
    // return SYS_ERR_OK;
}