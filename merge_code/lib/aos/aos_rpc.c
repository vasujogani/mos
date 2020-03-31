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
<<<<<<< HEAD

errval_t aos_rpc_send_number(struct aos_rpc *chan, uintptr_t val)
{
    // TODO: implement functionality to send a number ofer the channel
    // given channel and wait until the ack gets returned.
    return SYS_ERR_OK;
}

=======
#include <barrelfish_kpi/asm_inlines_arch.h>

void handshake_send_handler(void *arg);
void acknowledgement_recv_handler(void *arg);
void number_send_handler(void *arg);
void ram_cap_send_handler(void *args);
void ram_cap_recv_handler(void *args);
void send_string_handler(void* args);
void recv_string_handler(void* args);
void putchar_send_handler(void *arg);
void spawn_send_handler(void *args);
void spawn_recv_handler(void *args);
void handshake_recv_client_handler(void *arg);
uint32_t get_time(void);


void number_send_handler(void *arg)
{
    uintptr_t *uargs = (uintptr_t *) arg;
 
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    uintptr_t val = uargs[1];
 
    errval_t err;
    err = lmp_chan_send3(&rpc->channel, LMP_FLAG_SYNC, NULL_CAP, RPC_NUMBER, rpc->clientdata_pointer, val);
    assert(!err_is_fail(err));
    event_dispatch(rpc->ws);
}

errval_t aos_rpc_send_number(struct aos_rpc *chan, uintptr_t val)
{
    uintptr_t args[2];
    args[0] = (uintptr_t) chan;
    args[1] = val;

    errval_t err = lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE(number_send_handler, args));
    err = lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE(acknowledgement_recv_handler, chan));

    event_dispatch(chan->ws);
    return SYS_ERR_OK;
}

void send_string_handler(void* args) {
    uintptr_t *uargs = (uintptr_t *) args;
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    errval_t err = lmp_chan_send9(&rpc->channel, LMP_FLAG_SYNC, NULL_CAP, RPC_STRING, uargs[1], uargs[2], uargs[3], uargs[4], uargs[5], uargs[6], uargs[7], uargs[8]);
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
 
>>>>>>> week5
errval_t aos_rpc_send_string(struct aos_rpc *chan, const char *string)
{
    // TODO: implement functionality to send a string over the given channel
    // and wait for a response.
<<<<<<< HEAD
    return SYS_ERR_OK;
}

errval_t aos_rpc_get_ram_cap(struct aos_rpc *chan, size_t request_bits,
                             struct capref *retcap, size_t *ret_bits)
{
    // TODO: implement functionality to request a RAM capability over the
    // given channel and wait until it is delivered.
=======
    reset_cycle_counter();

    // uint32_t start = get_time();
    uint32_t uargs[9];
    uargs[0] = (uint32_t) chan;
    uargs[1] = chan->clientdata_pointer;
 
    uint32_t len = strlen(string) + 1;
    int count = 2;
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
            count = 2;
            uargs[count] = 24;
        }
    }
    if (len%24 != 0) {
        uargs[2] = len%24;
            // assert(false);
            // assert(chan->ws);
        errval_t err = lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) send_string_handler, uargs));
        assert(err_is_ok(err));
        err = lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE((void *) recv_string_handler, uargs));
        assert(err_is_ok(err));
 
        event_dispatch(chan->ws);
        event_dispatch(chan->ws);
    }
    uintptr_t end = get_time();
    debug_printf("rpc aos_rpc_send_string took %u cycles\n", end);
    // if (end > start) {
    //     debug_printf("rpc send_string took %u cycles\n", end - start);
    //  }
 
    return SYS_ERR_OK;
}


void ram_cap_send_handler(void *args)
{
    uintptr_t *uargs = (uintptr_t *)args;
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    size_t *bytes = (size_t *) uargs[1];
 
    errval_t err;
    err = lmp_chan_send3(&rpc->channel, LMP_FLAG_SYNC, NULL_CAP, RPC_MEMORY, rpc->clientdata_pointer, *bytes);
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
    // uint32_t start = get_time();
    // debug_printf("*************************************Time started: %u\n", start);
    // uint32_t time = 0;
    // __asm__ volatile ("MRC p15, 0, %0, c9, c13, 0" : "=r" (time));
    // debug_printf("^^^^^^^^^^%u\n", time);
    
    // printf("in aos_rpc_get_ram_cap\n");
    // Fill in args 1. aos_rpc 2. request_bytes 3. retcap 4. ret_bytes
    reset_cycle_counter();

    // uint32_t start = get_time();
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


    event_dispatch(chan->ws);
    if (ret_bytes) {
        *ret_bytes = request_bytes;
    }
    // uint32_t end = get_time();
    // debug_printf("*************************************Time end: %u\n", end);
    // uint32_t diff = end - start;
    // debug_printf("*************************************Time taken: %u\n", diff);
    uintptr_t end = get_time();
    debug_printf("rpc ram_cap took %u cycles\n", end);
    // if (end > start) {
    //     debug_printf("rpc ram_cap took %u cycles\n", end - start);
    // }

>>>>>>> week5
    return SYS_ERR_OK;
}

errval_t aos_rpc_serial_getchar(struct aos_rpc *chan, char *retc)
{
    // TODO implement functionality to request a character from
    // the serial driver.
    return SYS_ERR_OK;
}

<<<<<<< HEAD
=======
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
    err = lmp_chan_send3(&rpc->channel, LMP_FLAG_SYNC, NULL_CAP, RPC_PUTCHAR, rpc->clientdata_pointer, *to_put);
    if (err_is_fail(err)) {
        printf("Error\n");
    }
    // re-register
    // register again if failed
}
>>>>>>> week5

errval_t aos_rpc_serial_putchar(struct aos_rpc *chan, char c)
{
    // TODO implement functionality to send a character to the
    // serial port.
<<<<<<< HEAD
    return SYS_ERR_OK;
}

errval_t aos_rpc_process_spawn(struct aos_rpc *chan, char *name,
                               coreid_t core, domainid_t *newpid)
{
    // TODO (milestone 5): implement spawn new process rpc
    return SYS_ERR_OK;
}

=======
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
    debug_printf("doing a lil test\n");
    reset_cycle_counter();
    uintptr_t test = get_time();
    debug_printf("%u\n", test);

    reset_cycle_counter();
     test = get_time();
    debug_printf("%u\n", test);

    reset_cycle_counter();
     test = get_time();
    debug_printf("%u\n", test);
    debug_printf("test is done!!\n");

    reset_cycle_counter();
    // uint32_t start = get_time();
    // debug_printf("*************************************INIT Time started: %u\n", start);
    
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
    err = lmp_chan_register_recv(&rpc->channel,rpc->ws, MKCLOSURE((void*)handshake_recv_client_handler, rpc));
    err = lmp_chan_register_send(&rpc->channel,rpc->ws, MKCLOSURE((void*)handshake_send_handler, rpc));
    // loop till success?
    event_dispatch(rpc->ws);
    uintptr_t end = get_time();
    debug_printf("rpc aos_rpc_init took %u cycles\n", end);
     // if (end > start) {
     //    debug_printf("rpc init took %u cycles\n", end - start);
     // }
    
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

void handshake_recv_client_handler(void *arg) {
    // assert(false);
    errval_t err;
    
    struct aos_rpc *rpc = (struct aos_rpc *) arg;
    struct lmp_chan chan = rpc->channel;
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    // struct capref recv_cap;
    err = lmp_chan_recv(&chan, &msg, NULL);
    assert(msg.buf.msglen == 2 && msg.words[0] == RPC_OK);
    rpc->clientdata_pointer = msg.words[1];

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
    if (RPC_DEBUG_SPAWN) {
        debug_printf("Entering aos_rpc_process_spawn\n");
        debug_printf("name: %p\n", name);
        debug_printf("name: %s\n", name);
        debug_printf("core: %d\n", core);
        if (newpid != NULL) {
            debug_printf("newpid: %p\n", newpid);
        }
    }

    aos_rpc_send_string(chan, name);
    
    uintptr_t args[3];
    args[0] = (uintptr_t) chan;
    args[1] = (uintptr_t) core;
    args[2] = (uintptr_t) newpid;
    
    lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) spawn_send_handler, args));
 
    lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE((void *) spawn_recv_handler, args));
 
    event_dispatch(chan->ws);

    if (RPC_DEBUG_SPAWN)
        debug_printf("Exiting aos_rpc_process_spawn\n");
    return SYS_ERR_OK;
}

void spawn_send_handler(void *args)
{
    if (RPC_DEBUG_SPAWN)
        debug_printf("Entering spawn_send_handler\n");
 
    uintptr_t *uargs = (uintptr_t *)args;
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    coreid_t core = (coreid_t) uargs[1];

    if (RPC_DEBUG_SPAWN) {
        debug_printf("spawn send handler args: \n");
        debug_printf("core: %d\n", core);
    }
    errval_t err;
    err = lmp_chan_send3(&rpc->channel, LMP_FLAG_SYNC, NULL_CAP, RPC_SPAWN, rpc->clientdata_pointer, core);

    assert(err_is_ok(err));
    event_dispatch(rpc->ws);
 
    if (RPC_DEBUG_SPAWN)
        debug_printf("Exiting spawn_send_handler\n");
}

void spawn_recv_handler(void *args)
{
    if (RPC_DEBUG_SPAWN)
        debug_printf("Entering spawn_recv_handler\n");

    uintptr_t *uargs = (uintptr_t *)args;
    struct aos_rpc* rpc = (struct aos_rpc*) uargs[0];
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    struct capref recv_cap;
 
    errval_t err = lmp_chan_recv(&rpc->channel, &msg, &recv_cap);
    assert(err_is_ok(err));
    assert(msg.buf.msglen > 0);
    assert(msg.words[0] == RPC_OK);
    debug_printf("after receive\n");
    domainid_t *newpid = (domainid_t *) uargs[2];
    if (newpid) {
        *newpid = msg.words[1];
    }
    if (RPC_DEBUG_SPAWN) {
        if (newpid != NULL) {
            debug_printf("newpid: %p\n", newpid);
            debug_printf("newpid: %d\n", *newpid);
            debug_printf("msg.words[1]: %d\n", (domainid_t) msg.words[1]);
        }
        else {
            debug_printf("returned pid was null\n");
        } 
    }
    if (RPC_DEBUG_SPAWN)
        debug_printf("Exiting spawn_recv_handler\n");
}

>>>>>>> week5
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

<<<<<<< HEAD
errval_t aos_rpc_get_device_cap(struct aos_rpc *rpc,
                                lpaddr_t paddr, size_t bytes,
                                struct capref *frame)
{
    return LIB_ERR_NOT_IMPLEMENTED;
}

errval_t aos_rpc_init(struct aos_rpc *rpc)
{
    // TODO: Initialize given rpc channel
    return SYS_ERR_OK;
=======
uint32_t get_time(void) {
    
    // uint32_t pmcr = 0;
    
    // __asm__ volatile ("MRC p15,0, %0, c9,c12,0" : "=r" (pmcr) );
    // debug_printf("pmcr %u\n", pmcr & 0x4);

    // uint32_t time = 0;
    // __asm__ volatile ("mrc p15, 0, %0, c9, c13, 0" : "=r" (time) : : );

// uint32_t val;
//     __asm volatile ("mrc p15, 0, %0, c9, c13, 0\t\n": "=r"(val));
    return  get_cycle_count();
    // volatile uint32_t* timeptr;
    // __asm__ volatile ("MRC p15, 0, %0, c9, c13, 0" : "=r" (timeptr) : : );    

    // debug_printf("timeptr %u deref %u\n", timeptr, *timeptr);

    // __asm__ volatile ("mrc p15, 0, %%r12, c9, c13, 0" : : : "%r12");
    //value of r0 should be clock cycles now
    // int* p = NULL;
    // int v = *p;
    // debug_printf("%d\n", v);
    // __asm__ volatile ("mov %0, %%r12" : "=r" (time) : : "%r12");

    // return time;
>>>>>>> week5
}
