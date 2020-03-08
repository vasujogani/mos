/**
 * \file
 * \brief Barrelfish library initialization.
 */

/*
 * Copyright (c) 2007-2016, ETH Zurich.
 * Copyright (c) 2014, HP Labs.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, CAB F.78, Universitaetstr. 6, CH-8092 Zurich,
 * Attn: Systems Group.
 */

#include <stdio.h>
#include <aos/aos.h>
#include <aos/dispatch.h>
#include <aos/curdispatcher_arch.h>
#include <aos/dispatcher_arch.h>
#include <barrelfish_kpi/dispatcher_shared.h>
#include <aos/morecore.h>
#include <aos/paging.h>
#include <aos/aos_rpc.h>
#include <barrelfish_kpi/domain_params.h>
#include "threads_priv.h"
#include "init.h"

/// Are we the init domain (and thus need to take some special paths)?
static bool init_domain;

extern size_t (*_libc_terminal_read_func)(char *, size_t);
extern size_t (*_libc_terminal_write_func)(const char *, size_t);
extern void (*_libc_exit_func)(int);
extern void (*_libc_assert_func)(const char *, const char *, const char *, int);

void libc_exit(int);

void libc_exit(int status)
{
    // Use spawnd if spawned through spawnd
    if(disp_get_domain_id() == 0) {
        errval_t err = cap_revoke(cap_dispatcher);
        if (err_is_fail(err)) {
            sys_print("revoking dispatcher failed in _Exit, spinning!", 100);
            while (1) {}
        }
        err = cap_delete(cap_dispatcher);
        sys_print("deleting dispatcher failed in _Exit, spinning!", 100);

        // XXX: Leak all other domain allocations
    } else {
        debug_printf("libc_exit NYI!\n");
    }

    thread_exit(status);
    // If we're not dead by now, we wait
    while (1) {}
}

static void libc_assert(const char *expression, const char *file,
                        const char *function, int line)
{
    char buf[512];
    size_t len;

    /* Formatting as per suggestion in C99 spec 7.2.1.1 */
    len = snprintf(buf, sizeof(buf), "Assertion failed on core %d in %.*s: %s,"
                   " function %s, file %s, line %d.\n",
                   disp_get_core_id(), DISP_NAME_LEN,
                   disp_name(), expression, function, file, line);
    sys_print(buf, len < sizeof(buf) ? len : sizeof(buf));
}

static size_t syscall_terminal_write(const char *buf, size_t len)
{
    if (len) {
        return sys_print(buf, len);
    }
    return 0;
}

static size_t dummy_terminal_read(char *buf, size_t len)
{
    debug_printf("terminal read NYI! returning %d characters read\n", len);
    return len;
}

/* Set libc function pointers */
void barrelfish_libc_glue_init(void)
{
    // XXX: FIXME: Check whether we can use the proper kernel serial, and
    // what we need for that
    // TODO: change these to use the user-space serial driver if possible
    _libc_terminal_read_func = dummy_terminal_read;
    _libc_terminal_write_func = syscall_terminal_write;
    _libc_exit_func = libc_exit;
    _libc_assert_func = libc_assert;
    /* morecore func is setup by morecore_init() */

    // XXX: set a static buffer for stdout
    // this avoids an implicit call to malloc() on the first printf
    static char buf[BUFSIZ];
    setvbuf(stdout, buf, _IOLBF, sizeof(buf));
    static char ebuf[BUFSIZ];
    setvbuf(stderr, ebuf, _IOLBF, sizeof(buf));
}

/** \brief Initialise libbarrelfish.
 *
 * This runs on a thread in every domain, after the dispatcher is setup but
 * before main() runs.
 */
errval_t barrelfish_init_onthread(struct spawn_domain_params *params)
{
    errval_t err;

    // do we have an environment?
    if (params != NULL && params->envp[0] != NULL) {
        extern char **environ;
        environ = params->envp;
    }

    // Init default waitset for this dispatcher
    struct waitset *default_ws = get_default_waitset();
    waitset_init(default_ws);

    // Initialize ram_alloc state
    ram_alloc_init();
    /* All domains use smallcn to initialize */
    err = ram_alloc_set(NULL);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_RAM_ALLOC_SET);
    }

    err = paging_init();
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_VSPACE_INIT);
    }

    err = slot_alloc_init();
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_SLOT_ALLOC_INIT);
    }

    err = morecore_init();
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_MORECORE_INIT);
    }

    lmp_endpoint_init();

    // init domains only get partial init
    if (init_domain) {
        return SYS_ERR_OK;
    }

    struct aos_rpc init_client;
    aos_rpc_init(&init_client);
    set_init_rpc(&init_client);

    // // create an lmp_chan structure for communicating with init
    // struct lmp_chan init_chan;
    // lmp_chan_init(&init_chan);

    // // create local endpoint
    // err = endpoint_create(DEFAULT_LMP_BUF_WORDS, &(init_chan.local_cap), &(init_chan.endpoint));
    // if (err_is_fail(err)) {
    //     return err_push(err, LIB_ERR_ENDPOINT_CREATE);
    // }

    // // set the remote endpoint
    // init_chan.remote_cap = cap_initep;

    // // allocate a receive capability slot
    // err = lmp_chan_alloc_recv_slot(&init_chan);
    // if (err_is_fail(err)) {
    //     return err_push(err, LIB_ERR_LMP_ALLOC_RECV_SLOT);
    // }

    // // register a callback for send events
    // err = lmp_chan_register_send(&init_chan, default_ws, MKCLOSURE(handshake_send_handler, &init_chan));
    // if (err_is_fail(err)) {
    //     return err_push(err, LIB_ERR_CHAN_REGISTER_SEND);
    // }

    // // register a callabck for receive events
    // err = lmp_chan_register_recv(&init_chan, default_ws, MKCLOSURE(acknowledgement_recv_handler, &init_chan));
    // if (err_is_fail(err)) {
    //     return err_push(err, LIB_ERR_CHAN_REGISTER_RECV);
    // }

    // // wait for init to acknowledge receiving the endpoint
    // err = event_dispatch(default_ws);
    // if (err_is_fail(err)) {
    //     return err_push(err, LIB_ERR_EVENT_DISPATCH);
    // }
    
    // initialize init RPC client with lmp channel 
    

    // TODO MILESTONE 3: register ourselves with init
    /* allocate lmp channel structure */
    /* create local endpoint */
    /* set remote endpoint to init's endpoint */
    /* set receive handler */
    /* send local ep to init */
    /* wait for init to acknowledge receiving the endpoint */
    /* initialize init RPC client with lmp channel */
    /* set init RPC client in our program state */

    /* TODO MILESTONE 3: now we should have a channel with init set up and can
     * use it for the ram allocator */

    // right now we don't have the nameservice & don't need the terminal
    // and domain spanning, so we return here
    return SYS_ERR_OK;
}

// void handshake_send_handler(void *args) {
//     struct lmp_chan *init_chan = (struct lmp_chan *) args;
    
//     errval_t err;
//     // create a local ep copy for init
//     struct capref init_copy;
//     slot_alloc(&init_copy);
//     err = cap_copy(init_copy, init_chan->local_cap);
//     if (err_is_fail(err)) {
//         printf("Error copying local cap\n");
//     }

//     printf("IN HANDSHAKE SEND\n");
//     err = lmp_chan_send1(init_chan, LMP_FLAG_SYNC, init_copy, RPC_HANDSHAKE);
//     if (err_is_fail(err)) {
//         printf("Error sending handshake %s\n", err_getstring(err));
//     }
//     // wait for receive
//     event_dispatch(get_default_waitset());
// }

// void acknowledgement_recv_handler(void *args) {
//     errval_t err;
//     struct lmp_chan *lc = args;
//     struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
//     err = lmp_chan_recv(lc, &msg, NULL);
//     if (msg.buf.msglen > 0 && msg.words[0] == RPC_OK) {
//         // received proper acknowledgement, now initialize RPC client
//         printf("SUCCESSFUL\n");
//         struct aos_rpc rpc_client;
//         err = aos_rpc_init(&rpc_client, lc);
//         set_init_rpc(&rpc_client);

//         // allocate a receive capability slot
//         err = lmp_chan_alloc_recv_slot(lc);
//         if (err_is_fail(err)) {
//             printf("Unable to allocate new receive slot");
//         }
//     }
//     printf("IN ACKNOWLEDGEMENT RECEIVE\n");
// }


/**
 *  \brief Initialise libbarrelfish, while disabled.
 *
 * This runs on the dispatcher's stack, while disabled, before the dispatcher is
 * setup. We can't call anything that needs to be enabled (ie. cap invocations)
 * or uses threads. This is called from crt0.
 */
void barrelfish_init_disabled(dispatcher_handle_t handle, bool init_dom_arg);
void barrelfish_init_disabled(dispatcher_handle_t handle, bool init_dom_arg)
{
    init_domain = init_dom_arg;
    disp_init_disabled(handle);
    thread_init_disabled(handle, init_dom_arg);
}

