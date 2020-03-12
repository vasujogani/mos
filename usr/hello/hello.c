/**
 * \file
 * \brief Hello world application
 */

/*
 * Copyright (c) 2016 ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, CAB F.78, Universitaetstr. 6, CH-8092 Zurich,
 * Attn: Systems Group.
 */


#include <stdio.h>
#include <aos/aos_rpc.h>

static struct aos_rpc init_rpc;
int main(int argc, char *argv[])
{
    printf("Hello, world! from userspace\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    errval_t err;
    err = aos_rpc_init(&init_rpc);
    err = aos_rpc_send_string(&init_rpc, "hello there");
    return 0;
}
