
/**
 * \file
 * \brief create child process library
 */
 
/*
 * Copyright (c) 2016, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Universitaetsstrasse 6, CH-8092 Zurich. Attn: Systems Group.
 */
 
#ifndef _INIT_PID_H_
#define _INIT_PID_H_

struct pid_node {
    char *name;
    domainid_t pid;
    coreid_t core;
    struct pid_node *next; 
};

// domainid_t find_pid(char *name);
char *find_name(domainid_t pid);
domainid_t add_pid(char *name, coreid_t core);

#endif /* _INIT_PID_H_ */
