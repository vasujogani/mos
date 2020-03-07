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
#include <aos/aos_rpc.h>
#include <aos/paging.h>
#include <spawn/spawn.h>

#include <mm/mm.h>
#include "mem_alloc.h"

coreid_t my_core_id;
struct bootinfo *bi;

void handshake_recv_handler(struct lmp_chan *lc, struct capref recv_cap);
void acknowledgement_send_handler(void *arg);
void number_receive_handler(struct lmp_chan *lc, uintptr_t value);
void generic_recv_handler(void *arg);
void ram_cap_handler(struct lmp_chan *lc, size_t requested_size);
void memory_send_handler(void *arg);

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
    // struct capref dispatcher;
    // err = slot_alloc(&dispatcher);

    // dispatcher_handle_t handle = curdispatcher();
    // struct capref dispatch_cap = get_dispatcher_generic(handle)->dcb_cap;

    // copy into selfep slot
    err = cap_retype(cap_selfep, cap_dispatcher, 0, ObjType_EndPoint, 0, 1);

    // create a channel for open receiving
    struct lmp_chan lc;
    lmp_chan_init(&lc);
    err = endpoint_create(DEFAULT_LMP_BUF_WORDS, &(lc.local_cap), &(lc.endpoint));
    err = cap_copy(cap_initep, lc.local_cap);
    err = lmp_chan_alloc_recv_slot(&lc);
    err = lmp_chan_register_recv(&lc, get_default_waitset(), MKCLOSURE(generic_recv_handler, &lc));

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

void generic_recv_handler(void *arg) {
    errval_t err;
    struct lmp_chan *lc = arg;
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    struct capref recv_cap;
    err = lmp_chan_recv(lc, &msg, &recv_cap);
    // check that a proper message type was sent    
    assert(msg.buf.msglen > 0);
    uintptr_t messageType = msg.words[0];
    switch (messageType) {
        case RPC_HANDSHAKE:
            handshake_recv_handler(lc, recv_cap);
            break;
        case RPC_NUMBER:
            number_receive_handler(lc, msg.words[1]);
            break;
        case RPC_STRING:
            break;
        case RPC_MEMORY:
            printf("REQUESTING MEMORY\n");
            ram_cap_handler(lc, (size_t)msg.words[1]);
            break;
    }

    // reset the callback for this handshake channel
    err = lmp_chan_register_recv(lc, get_default_waitset(), MKCLOSURE(generic_recv_handler, lc));
    err = lmp_chan_alloc_recv_slot(lc);
}

void handshake_recv_handler(struct lmp_chan *lc, struct capref recv_cap) {
    printf("IN HANDSHAKE RECV\n");
    // create new channel for communication
    struct lmp_chan new_chan;
    errval_t err = lmp_chan_accept(&new_chan, DEFAULT_LMP_BUF_WORDS, recv_cap);
    // assert(!capref_is_null(recv_cap));
     assert(capcmp(recv_cap, new_chan.remote_cap));
    // printf("HERRRE\n");
    // set the callbacks for the new channel
    err = lmp_chan_alloc_recv_slot(&new_chan);
    err = lmp_chan_register_send(&new_chan, get_default_waitset(), MKCLOSURE(acknowledgement_send_handler, &new_chan));
    err = lmp_chan_register_recv(&new_chan, get_default_waitset(), MKCLOSURE(generic_recv_handler, &new_chan));
    event_dispatch(get_default_waitset());
}

void acknowledgement_send_handler(void *arg) {
    printf("IN ACKNOWLEDGE SEND\n");
    errval_t err;
    struct lmp_chan *lc = arg;
    err = lmp_chan_send1(lc, LMP_SEND_FLAGS_DEFAULT, NULL_CAP, RPC_OK);
}

void number_receive_handler(struct lmp_chan *lc, uintptr_t value) {
    printf("Number received: %d\n", value);
}

void ram_cap_handler(struct lmp_chan *lc, size_t requested_size) {
    //  allocate a ram cap and return 
    printf("Size requested is %d\n", requested_size);
    struct capref ram_cap;
    errval_t err = ram_alloc(&ram_cap, requested_size);
    assert(err_is_ok(err));
    uintptr_t uargs[2];
    uargs[0] = (uintptr_t) lc;
    uargs[1] = (uintptr_t) &ram_cap;

    err = lmp_chan_register_send(lc, get_default_waitset(), MKCLOSURE(memory_send_handler, uargs));
    event_dispatch(get_default_waitset());
}

void memory_send_handler(void *arg) {
    printf("IN MEMORY SEND HANDLER\n");
    uintptr_t *uarg = (uintptr_t *)arg;
    struct lmp_chan *lc = (struct lmp_chan *)uarg[0];
    struct capref ram_cap = *((struct capref *)uarg[1]);
    struct capref test;
    slot_alloc(&test);
    errval_t err = cap_copy(test, ram_cap);
    capaddr_t cap_level = get_cap_addr(ram_cap);
    printf("cap addr %d\n", cap_level);
    printf("cap addr %d\n", lc->remote_cap);
    if (err_is_fail(err)) {
        printf("ERROR IS %s\n", err_getstring(err));
    }
    printf("Ram slot num is %d\n", ram_cap.slot);
    err = lmp_chan_send1(lc, LMP_SEND_FLAGS_DEFAULT, ram_cap, RPC_OK);
    printf("Err is %s\n", err_getstring(err));
    assert(err_is_ok(err));
    printf("AT END OF MEMORY_SEND_HANDLER\n");
}