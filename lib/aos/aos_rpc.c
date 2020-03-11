/**
 * \file
 * \brief Implementation of AOS rpc-like messaging
 */

/*
 * Copyright (c) 2013 - 2016, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Universitaetstr. 6, CH-8092 Zurich. Attn: Systems Group.
 */

#include <aos/aos_rpc.h>

void handshake_send_handler(void *arg);
void acknowledgement_recv_handler(void *arg);
void number_send_handler(void *arg);
void ram_cap_send_handler(void *args);
void ram_cap_recv_handler(void *args);
void send_string_handler(void* args);
void recv_string_handler(void* args);
void putchar_send_handler(void *arg);
uint32_t get_time(void);
// void spawn_send_handler(void *args);
// void spawn_recv_handler(void *args);


void number_send_handler(void *arg)
{
    uintptr_t *uargs = (uintptr_t *) arg;
 
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    uintptr_t val = uargs[1];
 
    errval_t err;
    err = lmp_chan_send2(&rpc->channel, LMP_FLAG_SYNC, rpc->channel.local_cap, RPC_NUMBER, val);
    assert(!err_is_fail(err));
    event_dispatch(rpc->ws);
}

errval_t aos_rpc_send_number(struct aos_rpc *chan, uintptr_t val)
{
    uintptr_t args[2];
    args[0] = (uintptr_t) chan;
    args[1] = val;

    errval_t err = lmp_chan_alloc_recv_slot(&chan->channel);
    err = lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE(number_send_handler, args));
    err = lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE(acknowledgement_recv_handler, chan));

    event_dispatch(chan->ws);
    return SYS_ERR_OK;
}

void send_string_handler(void* args) {
    uintptr_t *uargs = (uintptr_t *) args;
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    errval_t err = lmp_chan_send9(&rpc->channel, LMP_FLAG_SYNC, rpc->channel.local_cap, RPC_STRING, uargs[1], uargs[2], uargs[3], uargs[4], uargs[5], uargs[6], uargs[7], uargs[8]);
    assert(err_is_ok(err));
}

void recv_string_handler(void* args) {
    uintptr_t *uargs = (uintptr_t *) args;
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    struct capref cap;
   
    errval_t err = lmp_chan_recv(&rpc->channel, &msg, &cap);
    assert(err_is_ok(err));
    assert(msg.words[0] == RPC_OK);
}
 
errval_t aos_rpc_send_string(struct aos_rpc *chan, const char *string)
{
    // TODO: implement functionality to send a string over the given channel
    // and wait for a response.
    uint32_t uargs[9];
    uargs[0] = (uint32_t) chan;
 
    uint32_t len = strlen(string) + 1;
    int count = 1;
    uargs[count] = len;
 
    for (int i = 0; i <= len; i++) {
        if (i % 4 == 0) {
            uargs[++count] = string[i];
        } else {
            uargs[count] += string[i] << ((i%4) * 8);
        }
        if (count == 8 && i%4 == 3) {
            // assert(false);
            errval_t err = lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) send_string_handler, uargs));
            assert(err_is_ok(err));
            err = lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE((void *) recv_string_handler, uargs));
            assert(err_is_ok(err));
           
            event_dispatch(chan->ws);
            event_dispatch(chan->ws);
            count = 1;
            uargs[count] = 28;
        }
    }
    if (len%28 != 0) {
        uargs[1] = len%28;
            // assert(false);
            // assert(chan->ws);
        errval_t err = lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) send_string_handler, uargs));
        assert(err_is_ok(err));
        err = lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE((void *) recv_string_handler, uargs));
        assert(err_is_ok(err));
 
        event_dispatch(chan->ws);
        event_dispatch(chan->ws);
    }
 
    return SYS_ERR_OK;
}


void ram_cap_send_handler(void *args)
{
    uintptr_t *uargs = (uintptr_t *)args;
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    size_t *bytes = (size_t *) uargs[1];
 
    errval_t err;
    err = lmp_chan_send2(&rpc->channel, LMP_FLAG_SYNC, rpc->channel.local_cap, RPC_MEMORY, *bytes);
    assert(err_is_ok(err));
    event_dispatch(rpc->ws);
}

void ram_cap_recv_handler(void *args) {
    uintptr_t *uargs = (uintptr_t *)args;
    struct aos_rpc* rpc = (struct aos_rpc*) uargs[0];
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    struct capref recv_cap;
    errval_t err = lmp_chan_recv(&rpc->channel, &msg, &recv_cap);
    assert(err_is_ok(err));
    assert(msg.buf.msglen > 0);
    assert(msg.words[0] == RPC_OK);
    struct capref *retcap = (struct capref *)uargs[2];
    err = cap_copy(*retcap, recv_cap);
}

errval_t aos_rpc_get_ram_cap(struct aos_rpc *chan, size_t request_bytes,
                             struct capref *retcap, size_t *ret_bytes)
{
    uint32_t start = get_time();
    debug_printf("*************************************Time started: %u\n", start);
    // printf("in aos_rpc_get_ram_cap\n");
    // Fill in args 1. aos_rpc 2. request_bytes 3. retcap 4. ret_bytes
    uintptr_t args[3];
    args[0] = (uintptr_t) chan;
    args[1] = (uintptr_t) &request_bytes;
    args[2] = (uintptr_t) retcap;

    slot_alloc(retcap);
 
    lmp_chan_alloc_recv_slot(&chan->channel);

    lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) ram_cap_send_handler, args));
    // printf("ALLOCATED SEND HANDLER\n");
    lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE((void *) ram_cap_recv_handler, args));
    // printf("ALLOCATED RECEIVE HANDLER\n");

    uint32_t end = get_time();
    debug_printf("*************************************Time end: %u\n", end);
    event_dispatch(chan->ws);
    if (ret_bytes) {
        *ret_bytes = request_bytes;
    }
    return SYS_ERR_OK;
}

errval_t aos_rpc_serial_getchar(struct aos_rpc *chan, char *retc)
{
    // TODO implement functionality to request a character from
    // the serial driver.
    return SYS_ERR_OK;
}

// errval_t send_handler(uintptr_t *args) {
//     // errval_t err;
//     // struct aos_rpc *rpc = (struct aos_rpc *) args[0];
//     // int message_type = *((int *)args[1]);
//     // if (message_type == RPC_PUTCHAR) {
//     //     err = lmp_chan_send2(&rpc->channel, LMP_FLAG_SYNC, NULL_CAP, RPC_PUTCHAR, args[2]);
//     //     if (err_is_fail(err)) {
//     //         return err_push(err, LIB_ERR_LMP_CHAN_SEND);
//     //     }
//     // } else if (message_type == RPC_NUMBER) {
//     //     err = lmp_chan_send2(&rpc->channel, LMP_FLAG_SYNC, NULL_CAP, RPC_NUMBER, args[2]);
//     //     if (err_is_fail(err)) {
//     //         return err_push(err, LIB_ERR_LMP_CHAN_SEND);
//     //     }
//     // }
// }

void putchar_send_handler(void *arg) {
    //sf 
    uintptr_t *args = (uintptr_t *) arg;
    struct aos_rpc *rpc = (struct aos_rpc *) args[0];
    char* to_put = (char*) args[1];
    errval_t err;
    err = lmp_chan_send2(&rpc->channel, LMP_FLAG_SYNC, rpc->channel.local_cap, RPC_PUTCHAR, *to_put);
    if (err_is_fail(err)) {
        printf("Error\n");
    }
    // re-register
    // register again if failed
}

errval_t aos_rpc_serial_putchar(struct aos_rpc *chan, char c)
{
    // TODO implement functionality to send a character to the
    // serial port.
    uintptr_t args[3];
    args[0] = (uintptr_t) chan;
    args[1] = RPC_PUTCHAR;
    args[2] = c;

    errval_t err = lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE(putchar_send_handler, args));
    event_dispatch(chan->ws);
    assert(err_is_ok(err));
    return SYS_ERR_OK;
}

errval_t aos_rpc_get_device_cap(struct aos_rpc *rpc,
                                lpaddr_t paddr, size_t bytes,
                                struct capref *frame)
{
    return LIB_ERR_NOT_IMPLEMENTED;
}

// errval_t handshake_send_handler(void *args) {
//     // struct aos_rpc *rpc = (struct aos_rpc *) args;
//     // errval_t err;
//     // lmp_chan_send1(&rpc->channel, LMP_FLAG_SYNC, NULL, RPC_HANDSHAKE);
//     return SYS_ERR_OK;
// }

// errval_t handshake_recv_handler(void *args) {
//     // struct aos_rpc *rpc = (struct aos_rpc *) args;
//     // struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
//     // struct capref cap;
//     // errval_t err = lmp_chan_recv(&rpc->channel, &msg, &cap);
//     // assert(err_is_ok(err));

//     // assert(msg.words[0] == RPC_OK);

//     return SYS_ERR_OK;
// }

errval_t aos_rpc_init(struct aos_rpc *rpc)
{
    errval_t err;
    
    // create an lmp_chan structure for communicating with init
    struct lmp_chan init_chan;
    lmp_chan_init(&init_chan);

    // create endpoints
    err = endpoint_create(DEFAULT_LMP_BUF_WORDS, &(init_chan.local_cap), &(init_chan.endpoint));
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_ENDPOINT_CREATE);
    }
    init_chan.remote_cap = cap_initep;

    rpc->ws = get_default_waitset();
    assert(rpc->ws != NULL);
    rpc->channel = init_chan;
    err = lmp_chan_alloc_recv_slot(&rpc->channel);
    err = lmp_chan_register_recv(&rpc->channel,rpc->ws, MKCLOSURE((void*)acknowledgement_recv_handler, rpc));
    err = lmp_chan_register_send(&rpc->channel,rpc->ws, MKCLOSURE((void*)handshake_send_handler, rpc));
    // loop till success?
    event_dispatch(rpc->ws);
    return SYS_ERR_OK;
}

void handshake_send_handler(void *arg) {
    struct aos_rpc *rpc = (struct aos_rpc *) arg;
    struct lmp_chan chan = rpc->channel;

    errval_t err;
    // create a local ep copy for init
    struct capref init_copy;
    slot_alloc(&init_copy);
    err = cap_copy(init_copy, chan.local_cap);
    assert(!capref_is_null(init_copy));
    err = lmp_chan_send1(&chan, LMP_FLAG_SYNC, chan.local_cap, RPC_HANDSHAKE);

    event_dispatch(rpc->ws);
}

void acknowledgement_recv_handler(void *arg) {
    // assert(false);
    errval_t err;
    
    struct aos_rpc *rpc = (struct aos_rpc *) arg;
    struct lmp_chan chan = rpc->channel;
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    // struct capref recv_cap;
    err = lmp_chan_recv(&chan, &msg, NULL);
    assert(msg.buf.msglen == 1 && msg.words[0] == RPC_OK);

}

// void init_recv_handler(void *arg) {

//     struct lmp_chan *chan = (struct lmp_chan *)arg;
//     struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
//     struct capref recv_cap; 
//     // allocate a slot for the received capability
//     errval_t err = lmp_chan_alloc_recv_slot(&chan);
//     err = lmp_chan_recv(chan, &msg, &recv_cap);
//     assert(msg.buf.buflen > 0);
//     uintptr_t messageType = msg.words[0];
//     if (messageType == RPC_OK) {
//         // do nothing
//     } else if (messageType == RPC_NUMBER) {
//         // just print the number for now
//         printf("Received number: %d\n", msg.words[1]);
//     } else if (messageType == RPC_MEMORY) {
//         // allocate a ram cap and return 
//         struct capref ram_cap;
//         uintptr_t args[2];
//         args[0] = (uintptr_t) chan;
//         size_t requested_size = (size_t) msg.words[1];
//         err = ram_alloc(&ram_cap, requested_size);
//         args[1] = (uintptr_t) &ram_cap;
//         err = lmp_chan_register_send(chan, get_default_waitset(), MKCLOSURE(send_memory, &ram_cap));
//         event_dispatch(get_default_waitset());
//     } else if (messageType == RPC_STRING) {
//         // just print the string for now
//         char buffer
//         printf("Received string: %s\n", )
//     }
// }

// void send_memory(void *arg) {
//     struct lmp_chan *chan = (struct lmp_chan *)arg[0];
//     struct capref ram_cap = *((struct capref *)arg[1]);
//     lmp_chan_send2(chan, LMP_FLAG_SYNC, ram_cap, RPC_OK);
// }

/**
 * \brief Request process manager to start a new process
 * \arg name the name of the process that needs to be spawned (without a
 *           path prefix)
 * \arg newpid the process id of the newly spawned process
 */
errval_t aos_rpc_process_spawn(struct aos_rpc *chan, char *name,
        coreid_t core, domainid_t *newpid) {
    // if (RPC_DEBUG_SPAWN) {
    //     printf("Entering aos_rpc_process_spawn\n");
    //     printf("name: %p\n", name);
    //     printf("name: %s\n", name);
    //     printf("core: %d\n", core);
    //     if (newpid != NULL) {
    //         printf("newpid: %p\n", newpid);
    //         printf("newpid: %d\n", *newpid);
    //     }
    // }
    
    // uintptr_t args[4];
    // args[0] = (uintptr_t) chan;
    // args[1] = (uintptr_t) name;
    // args[2] = (uintptr_t) core;
    // args[3] = (uintptr_t) newpid;
    
    // lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) spawn_send_handler, args));
 
    // lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE((void *) spawn_recv_handler, args));
 
    // event_dispatch(chan->ws);

    // if (RPC_DEBUG_SPAWN)
    //     printf("Exiting aos_rpc_process_spawn\n");
    return SYS_ERR_OK;
}

// void spawn_send_handler(void *args)
// {
//     if (RPC_DEBUG_SPAWN)
//         printf("Entering spawn_send_handler\n");
    
//     uintptr_t *uargs = (uintptr_t *)args;
//     struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
//     char *name = (char *) uargs[1];
//     coreid_t core = (coreid_t) uargs[2];
//     domainid_t *newpid = (domainid_t *) uargs[3];
 
//     if (RPC_DEBUG_SPAWN) {
//         printf("spawn send handler args: \n");
//         printf("name: %p\n", name);
//         printf("name: %s\n", name);
//         printf("core: %d\n", core);
//         if (newpid != NULL) {
//             printf("newpid: %p\n", newpid);
//             printf("newpid: %d\n", *newpid);
//         }
//     }
//     errval_t err;
//     err = lmp_chan_send4(&rpc->channel, LMP_FLAG_SYNC, rpc->channel.local_cap, RPC_SPAWN, 
//                          *name, core, *newpid);
//     assert(err_is_ok(err));
//     event_dispatch(rpc->ws);
    
//     if (RPC_DEBUG_SPAWN)
//         printf("Exiting spawn_send_handler\n");
// }

// void spawn_recv_handler(void *args)
// {
//     if (RPC_DEBUG_SPAWN)
//         printf("Entering spawn_recv_handler\n");

//     uintptr_t *uargs = (uintptr_t *)args;
//     struct aos_rpc* rpc = (struct aos_rpc*) uargs[0];
//     struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
//     struct capref recv_cap;
    
//     errval_t err = lmp_chan_recv(&rpc->channel, &msg, &recv_cap);
//     assert(err_is_ok(err));
//     assert(msg.buf.msglen > 0);
//     assert(msg.words[0] == RPC_OK);
    
//     domainid_t *newpid = (domainid_t *) uargs[3];
//     *newpid = msg.words[1];
//     if (RPC_DEBUG_SPAWN) {
//         if (newpid != NULL) {
//             printf("newpid: %p\n", newpid);
//             printf("newpid: %d\n", *newpid);
//         }
//         printf("msg.words[1]: %d\n", (domainid_t) msg.words[1]);
//     }
//     if (RPC_DEBUG_SPAWN)
//         printf("Exiting spawn_recv_handler\n");
// }

errval_t aos_rpc_process_get_name(struct aos_rpc *chan, domainid_t pid,
                                  char **name)
{
    // TODO (milestone 5): implement name lookup for process given a process
    // id
    return SYS_ERR_OK;
}

errval_t aos_rpc_process_get_all_pids(struct aos_rpc *chan,
                                      domainid_t **pids, size_t *pid_count)
{
    // TODO (milestone 5): implement process id discovery
    return SYS_ERR_OK;
}

uint32_t get_time(void) {
    uint32_t time = 0;
    __asm__ volatile ("mcr p15, 0, %0, c9, c13, 0" : "=r"(time));
    return time;
}