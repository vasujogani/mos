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

errval_t number_send_handler(void *args)
{
    uintptr_t *uargs = (uintptr_t *) args;
 
    struct aos_rpc *rpc = (struct aos_rpc *) uargs[0];
    uintptr_t val = uargs[1];
 
    errval_t err;
    err = lmp_chan_send2(&rpc->chan, LMP_FLAG_SYNC, rpc->chan.local_cap, RPC_NUMBER, val);
    assert(!err_is_fail(err));
 
    return SYS_ERR_OK;
}

errval_t aos_rpc_send_number(struct aos_rpc *chan, uintptr_t val)
{
    uintptr_t args[2];
 
    args[0] = (uintptr_t) chan;
    args[1] = (uintptr_t) val;
 
    lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) number_send_handler, args)));
    event_dispatch(chan->ws);
 
    return SYS_ERR_OK;
}

errval_t string_send_handler(uintptr_t *args)
{
    struct aos_rpc *rpc = (struct aos_rpc *) args[0];
 
    errval_t err = lmp_chan_send9(&rpc->channel, LMP_FLAG_SYNC, rpc->channel.local_cap, RPC_STRING, args[8], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
    assert(!err_is_fail(err));
    return SYS_ERR_OK;
}

errval_t string_recv_handler(uintptr_t *args)
{
    struct aos_rpc* rpc = (struct aos_rpc*) args[0];
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
 
    struct capref cap;
    errval_t err = lmp_chan_recv(&rpc->channel, &msg, &cap);
    assert(!err_is_fail(err));
    assert(!lmp_err_is_transient(err));
 
    assert(msg.buf.msglen == 1);
    assert(msg.words[0] == AOS_RPC_OK);
    return err;
}

errval_t aos_rpc_send_string(struct aos_rpc *chan, const char *string)
{
    assert(rpc != NULL);
 
    uint32_t len = strlen(string) + 1;
 
    uint32_t args[9];
    args[0] = (uint32_t) rpc;
 
    uint8_t count = 0;
 
    for (uint32_t i=0; i<=len;++i){
        if (i%4==0){
            args[++count] = string[i];
        } else {
            args[count] += string[i] << ((i%4)*8);
        }
        if (count == 8 && i%4==3) {
            errval_t err = lmp_chan_register_send(&rpc->channel, rpc->ws, MKCLOSURE((void *) string_send_handler, args));
            err = lmp_chan_register_recv(&rpc->channel, rpc->ws, MKCLOSURE((void *) string_recv_handler, args));
            event_dispatch(rpc->ws);
            event_dispatch(rpc->ws);
            count = 0;
        }
    }
 
    if (len%32 != 0){
        errval_t err = lmp_chan_register_send(&rpc->channel, rpc->ws, MKCLOSURE((void *) string_send_handler, args));
        err = lmp_chan_register_recv(&rpc->channel, rpc->ws, MKCLOSURE((void *) string_recv_handler, args));
        event_dispatch(rpc->ws);
        event_dispatch(rpc->ws);
    }
 
    return SYS_ERR_OK;
}

errval_t ram_send_handler(uintptr_t *args)
{
    struct aos_rpc *rpc = (struct aos_rpc *) args[0];
    size_t *bits = (size_t *) args[1];
 
    errval_t err;
    err = lmp_chan_send2(&rpc->chan, LMP_FLAG_SYNC, rpc->chan.local_cap, RPC_MEMORY, *bits);
    assert(err_is_ok(err));
    return SYS_ERR_OK;
}

errval_t aos_rpc_get_ram_cap(struct aos_rpc *chan, size_t request_bits,
                             struct capref *retcap, size_t *ret_bits)
{
    // Fill in args 1. aos_rpc 2. request_bytes 3. retcap 4. ret_bytes
    uintptr_t args[4];
 
    args[0] = (uintptr_t) chan;
    args[1] = (uintptr_t) &request_bits;
    args[2] = (uintptr_t) retcap;
    args[3] = (uintptr_t) ret_bits;
 
    lmp_chan_alloc_recv_slot(&chan->channel);
 
    lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE((void *) ram_cap_send_handler, args));
 
    lmp_chan_register_recv(&chan->channel, chan->ws, MKCLOSURE((void *) ram_cap_recv_handler, args));
 
    event_dispatch(chan->ws);
    event_dispatch(chan->ws);
 
    *retcap = *((struct capref *) args[2]);
    *ret_bits = *((size_t *) args[3]);
 
    return SYS_ERR_OK;
}

errval_t aos_rpc_serial_getchar(struct aos_rpc *chan, char *retc)
{
    // TODO implement functionality to request a character from
    // the serial driver.
    return SYS_ERR_OK;
}

errval_t putchar_send_handler(uintptr_t *args) {
    //sf 
    struct aos_rpc *rpc = (struct aos_rpc *) args[0];
    char* to_put = (char*) args[1];
    errval_t err;
    err = lmp_chan_send2(&rpc->channel, LMP_FLAG_SYNC, NULL /* rpc->channel.local_cap */, AOS_RPC_PUTCHAR, *to_put);
    assert(err_is_ok(err));
    // register again if failed
    return SYS_ERR_OK;
}

errval_t aos_rpc_serial_putchar(struct aos_rpc *chan, char c)
{
    // TODO implement functionality to send a character to the
    // serial port.
    uintptr_t args[2];
    args[0] = (uintptr_t) chan;
    args[1] = (uintptr_t) &c;

    errval_t err = lmp_chan_register_send(&chan->channel, chan->ws, MKCLOSURE(putchar_send_handler, args));
    event_dispatch(chan->ws);
    assert(err_is_ok(err));
    return SYS_ERR_OK;
}

errval_t aos_rpc_process_spawn(struct aos_rpc *chan, char *name,
                               coreid_t core, domainid_t *newpid)
{
    // TODO (milestone 5): implement spawn new process rpc
    return SYS_ERR_OK;
}

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

errval_t aos_rpc_get_device_cap(struct aos_rpc *rpc,
                                lpaddr_t paddr, size_t bytes,
                                struct capref *frame)
{
    return LIB_ERR_NOT_IMPLEMENTED;
}

errval_t handshake_send_handler(void *args) {
    struct aos_rpc *rpc = (struct aos_rpc *) args;
    errval_t err;
    lmp_chan_send1(&rpc->channel, LMP_FLAG_SYNC, NULL, RPC_HANDSHAKE);
    return SYS_ERR_OK;
}

errval_t handshake_recv_handler(void *args) {
    struct aos_rpc *rpc = (struct aos_rpc *) args;
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    struct capref cap;
    errval_t err = lmp_chan_recv(&rpc->channel, &msg, &cap);
    assert(err_is_ok(err));

    assert(msg.words[0] == RPC_OK);

    return SYS_ERR_OK;
}

errval_t aos_rpc_init(struct aos_rpc *rpc)
{
    // TODO: Initialize given rpc channel
    errval_t err;
    rpc->ws = get_default_waitset();
    struct waitset *ws = get_default_waitset();
    err = lmp_chan_accept(&rpc->channel, DEFAULT_LMP_BUF_WORDS, cap_initep);
    // err = lmp_chan_
    err = lmp_chan_register_recv(&rpc->channel,rpc->ws, MKCLOSURE((void*)handshake_recv_handler, rpc));
    err = lmp_chan_register_send(&rpc->channel,rpc->ws, MKCLOSURE((void*)handshake_send_handler, rpc));
    // loop till success?
    event_dispatch(rpc->ws);

    return SYS_ERR_OK;
}
