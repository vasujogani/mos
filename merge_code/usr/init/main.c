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
<<<<<<< HEAD
#include <aos/paging.h>
=======
#include <aos/dispatcher_arch.h>
#include <aos/aos_rpc.h>
#include <aos/paging.h>
#include <aos/pid.h>
#include <spawn/spawn.h>
>>>>>>> week5

#include <mm/mm.h>
#include "mem_alloc.h"

coreid_t my_core_id;
struct bootinfo *bi;
<<<<<<< HEAD
=======
// domainid_t next_pid = 0;

struct client_data {
    struct lmp_chan lc;
    char* buf;
    char* latest_buf;
    size_t buf_idx;
    struct capability id_cap;
    struct client_data *next;
    int len;
    int latest_len;
};

struct client_data* clients = NULL;
 
void handshake_recv_handler(struct lmp_chan *lc, struct capref recv_cap);
void handshake_send_client_handler(void *arg);
void acknowledgement_send_handler(void *arg);
void number_receive_handler(struct lmp_chan *lc, uintptr_t value, struct client_data *data);
void generic_recv_handler(void *arg);
void ram_cap_handler(struct lmp_chan *lc, size_t requested_size, struct client_data *data);
void memory_send_handler(void *arg);
// struct client_data* find_client(struct capref* cap);
void add_client(struct client_data *client);
void process_spawn_handler(struct lmp_chan *lc, coreid_t core, struct client_data *data);
void pid_send_handler(void *arg);
void string_recv_handler(void *args, struct lmp_recv_msg *msg, struct client_data *c);

void test_many_spawns(void);


// struct client_data* find_client(struct capref* cap) {
//     struct capability capp; // to store info
//     errval_t err = debug_cap_identify(*cap, &capp);

//     assert(err_is_ok(err));
//     struct client_data* to_ret = clients;
//     while (to_ret) {
//         if (to_ret->id_cap.u.endpoint.listener == capp.u.endpoint.listener && to_ret->id_cap.u.endpoint.epoffset == capp.u.endpoint.epoffset) {
//             break;
//         }
//         to_ret = to_ret->next;
//     }
 
//     return to_ret;
// }

void add_client(struct client_data *client) {
    if (clients == NULL) {
        clients = client;
    } else {
        client->next = clients;
        clients = client;
    }
}
>>>>>>> week5

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

<<<<<<< HEAD
=======
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

    init_pid();
    if (DEBUG_PID)
        debug_pid_lists();
    add_pid("init", my_core_id);
    debug_printf("my_core_id: %d\n", my_core_id);

    if (DEBUG_PID)
        debug_pid_lists();

    add_pid("memeater", my_core_id);
    if (DEBUG_PID) {
        debug_pid_lists();
        test_pid();
    }

    spawn_load_by_name("memeater", (struct spawninfo *) malloc(sizeof(struct spawninfo)));

>>>>>>> week5
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
<<<<<<< HEAD

    return EXIT_SUCCESS;
}
=======
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
    if (messageType == RPC_HANDSHAKE) {
        handshake_recv_handler(lc, recv_cap);
    } else {
        // find the correct channel to execute on
        struct client_data *client = (struct client_data *)msg.words[1];
        switch (messageType) {
            case RPC_NUMBER:
                number_receive_handler(lc, msg.words[2], client);
                break;
            case RPC_STRING:
                string_recv_handler(arg, &msg, client);
                break;
            case RPC_MEMORY:
                ram_cap_handler(lc, (size_t)msg.words[2], client);
                break;
            case RPC_SPAWN:
                process_spawn_handler(lc, (coreid_t) msg.words[2], client);
        }
    }

    // reset the callback for this handshake channel
    err = lmp_chan_register_recv(lc, get_default_waitset(), MKCLOSURE(generic_recv_handler, lc));
    // printf("SLOT NUM NOW %d\n", lc->endpoint->recv_slot.slot);
}

void handshake_recv_handler(struct lmp_chan *lc, struct capref recv_cap) {
    // printf("IN HANDSHAKE RECV\n");
    // create new channel for communication
    struct lmp_chan new_chan;
    errval_t err = lmp_chan_accept(&new_chan, DEFAULT_LMP_BUF_WORDS, recv_cap);
    assert(err_is_ok(err));
    assert(capcmp(recv_cap, new_chan.remote_cap));

    struct client_data *client = malloc(sizeof(struct client_data));
    client->lc = new_chan;
    client->buf = NULL;
    client->latest_buf = NULL;
    client->buf_idx = 0;
    client->next = NULL;
    debug_cap_identify(recv_cap, &client->id_cap);
    add_client(client);
    err = lmp_chan_alloc_recv_slot(lc);

    lmp_chan_register_send(&new_chan, get_default_waitset(), MKCLOSURE((void *)handshake_send_client_handler, client));

    event_dispatch(get_default_waitset());
}

void handshake_send_client_handler(void *arg) {
    struct lmp_chan *lc = &((struct client_data *)arg)->lc;
    lmp_chan_send2(lc, LMP_SEND_FLAGS_DEFAULT, NULL_CAP, RPC_OK, (uintptr_t)arg);
}

void acknowledgement_send_handler(void *arg) {
    // printf("IN ACKNOWLEDGE SEND\n");
    errval_t err;
    struct lmp_chan *lc = arg;
    err = lmp_chan_send1(lc, LMP_SEND_FLAGS_DEFAULT, NULL_CAP, RPC_OK);
}

void number_receive_handler(struct lmp_chan *lc, uintptr_t value, struct client_data *data) {
    // printf("Number received: %d\n", value);
    lmp_chan_register_send(&data->lc, get_default_waitset(), MKCLOSURE((void *)acknowledgement_send_handler, &data->lc));
}

void ram_cap_handler(struct lmp_chan *lc, size_t requested_size, struct client_data *data) {
    //  allocate a ram cap and return 
    struct capref ram_cap;
    errval_t err = ram_alloc(&ram_cap, requested_size);
    assert(err_is_ok(err));
    uintptr_t uargs[2];
    uargs[0] = (uintptr_t) &data->lc;
    uargs[1] = (uintptr_t) &ram_cap;

    err = lmp_chan_register_send(&data->lc, get_default_waitset(), MKCLOSURE(memory_send_handler, uargs));
    event_dispatch(get_default_waitset());
}

void memory_send_handler(void *arg) {
    uintptr_t *uarg = (uintptr_t *)arg;
    struct lmp_chan *lc = (struct lmp_chan *)uarg[0];
    struct capref ram_cap = *((struct capref *)uarg[1]);

    errval_t err = lmp_chan_send1(lc, LMP_SEND_FLAGS_DEFAULT, ram_cap, RPC_OK);
    assert(err_is_ok(err));
}

void process_spawn_handler(struct lmp_chan *lc, coreid_t core, struct client_data *data) {
    // TODO(M5): Use the core arg

    char *name = data->latest_buf; // buffer stuff
    if (RPC_DEBUG_SPAWN) 
    {
        debug_printf("Entering process_spawn_handler\n");
        debug_printf("core: %d\n", core);
        debug_printf("process name: %p\n", name);
        debug_printf("process name: %s\n", name);
    }

    domainid_t newpid = add_pid(name, core);
    if (DEBUG_PID)
        debug_pid_lists();
    errval_t err;
    
    // Start the new process
    err = spawn_load_by_name(name, (struct spawninfo *) malloc(sizeof(struct spawninfo)));
    assert(err_is_ok(err));
    
    uintptr_t uargs[2];
    uargs[0] = (uintptr_t) &data->lc;
    uargs[1] = (uintptr_t) &newpid;

    // Send the pid back to the parent process 
    err = lmp_chan_register_send(&data->lc, get_default_waitset(), MKCLOSURE(pid_send_handler, uargs));
    event_dispatch(get_default_waitset());
}

// Return the new pid to the parent process
void pid_send_handler(void *arg) {
    uintptr_t *uarg = (uintptr_t *)arg;
    struct lmp_chan *lc = (struct lmp_chan *)uarg[0];
    domainid_t *newpid = (domainid_t *) uarg[1];

    errval_t err = lmp_chan_send2(lc, LMP_SEND_FLAGS_DEFAULT, NULL_CAP, RPC_OK, *newpid);
    assert(err_is_ok(err));
}

void string_recv_handler(void *args, struct lmp_recv_msg *msg, struct client_data *c) {
    // printf("String received\n");
    assert(c);
    int len = msg->words[2];
    if (c->buf == NULL) {
        c->buf = (char *) malloc(len * sizeof(char));
        c->buf_idx = 0;
        c->len = len;
    }
    int end = len < 24 ? len: 24;
    for (int i = 0; i < end; i++) {
        uint32_t w = (uint32_t) msg->words[3 + i / 4];
        c->buf[c->buf_idx++] = (char) (w >> (8 * (i % 4)));
    }
    if (c->buf_idx == c->len) {
        // Now that we've received the entire string, store it in latest_buf so it can be used 
        // later, and clear buf so we can receive a new string
        c->latest_buf = c->buf;
        c->latest_len = c->len;
        c->buf_idx = 0;
        c->len = 0;
        debug_printf("String is : %s\n", c->buf);
        c->buf = NULL;
    }
 
    lmp_chan_register_send(&c->lc, get_default_waitset(), MKCLOSURE((void *) acknowledgement_send_handler, &c->lc));
 }

 void test_many_spawns(void) {
    for (int i = 0; i < 10; ++i)
    {
        spawn_load_by_name("memeater", (struct spawninfo *) malloc(sizeof(struct spawninfo)));
    }
}
>>>>>>> week5
