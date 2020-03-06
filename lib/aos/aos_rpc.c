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

errval_t aos_rpc_send_number(struct aos_rpc *chan, uintptr_t val)
{
    // TODO: implement functionality to send a number ofer the channel
    // given channel and wait until the ack gets returned.
    return SYS_ERR_OK;
}

errval_t aos_rpc_send_string(struct aos_rpc *chan, const char *string)
{
    // TODO: implement functionality to send a string over the given channel
    // and wait for a response.
    return SYS_ERR_OK;
}

errval_t aos_rpc_get_ram_cap(struct aos_rpc *chan, size_t request_bits,
                             struct capref *retcap, size_t *ret_bits)
{
    // TODO: implement functionality to request a RAM capability over the
    // given channel and wait until it is delivered.
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
    err =lmp_chan_register_recv(&rpc->channel,rpc->ws, MKCLOSURE((void*)handshake_recv_handler, rpc));
    err = lmp_chan_register_send(&rpc->channel,rpc->ws, MKCLOSURE((void*)handshake_send_handler, rpc));
    // loop till success?
    event_dispatch(rpc->ws);

    return SYS_ERR_OK;
}
