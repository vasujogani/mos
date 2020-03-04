
 
/**
 * \file
 * \brief AOS paging helpers.
 */
 
/*
 * Copyright (c) 2012, 2013, 2016, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Universitaetstr. 6, CH-8092 Zurich. Attn: Systems Group.
 */
 
#include <aos/aos.h>
#include <aos/paging.h>
#include <aos/except.h>
#include <aos/slab.h>
#include "threads_priv.h"
 
#include <spawn/spawn.h>
 
#include <stdio.h>
#include <string.h>
 
static struct paging_state current;
 
/**
 * \brief Helper function that allocates a slot and
 *        creates a ARM l2 page table capability
 */
__attribute__((unused))
static errval_t arml2_alloc(struct paging_state * st, struct capref *ret)
{
    errval_t err;
    err = st->slot_alloc->alloc(st->slot_alloc, ret);
    if (err_is_fail(err)) {
        debug_printf("slot_alloc failed: %s\n", err_getstring(err));
        return err;
    }
    err = vnode_create(*ret, ObjType_VNode_ARM_l2);
    if (err_is_fail(err)) {
        debug_printf("vnode_create failed: %s\n", err_getstring(err));
        return err;
    }
    return SYS_ERR_OK;
}
 
 
errval_t paging_init_state(struct paging_state *st, lvaddr_t start_vaddr,
        struct capref pdir, struct slot_allocator * ca)
{
    st->slot_alloc = ca;
 
    st->l1_page_table = pdir;
 
    for (int i = 0; i < ARM_L1_MAX_ENTRIES; ++i) {
        st->l2_page_tables[i].init = false;
    }
    st->free_node.base_addr = start_vaddr;
    st->free_node.size = 0xFFFFFFFF - start_vaddr;
    st->free_node.next = NULL;
 
    slab_init(&st->slab_alloc,sizeof(struct paging_frame_node) * 64,slab_default_refill);
 
    return SYS_ERR_OK;
}
 
/**
 * \brief This function initializes the paging for this domain
 * It is called once before main.
 */
errval_t paging_init(void)
{
    // DBG(VERBOSE, "paging_init\n");
 
    // TODO (M4): initialize self-paging handler
    // TIP: use thread_set_exception_handler() to setup a page fault handler
    // TIP: Think about the fact that later on, you'll have to make sure that
    // you can handle page faults in any thread of a domain.
 
    set_current_paging_state(&current);
 
    // According to the book, the L1 page table is at the following address.
    struct capref l1_pagetable = {
        .cnode = cnode_page,
        .slot = 0,
    };
 
    paging_init_state(&current, (1<<25), l1_pagetable, get_default_slot_allocator());
    return SYS_ERR_OK;
}
 
/**
 * \brief Initialize per-thread paging state
 */
void paging_init_onthread(struct thread *t)
{
    // TODO (M4): setup exception handler for thread `t'.
}
 
/**
 * \brief return a pointer to a bit of the paging region `pr`.
 * This function gets used in some of the code that is responsible
 * for allocating Frame (and other) capabilities.
 */
errval_t paging_region_init(struct paging_state *st, struct paging_region *pr,
                            size_t size)
{
    void *base;
    errval_t err = paging_alloc(st, &base, size);
    if (err_is_fail(err)) {
        debug_printf("paging_region_init: paging_alloc failed\n");
        return err_push(err, LIB_ERR_VSPACE_MMU_AWARE_INIT);
    }
    pr->base_addr    = (lvaddr_t)base;
    pr->current_addr = pr->base_addr;
    pr->region_size  = size;

    // TODO: maybe add paging regions to paging state?
    return SYS_ERR_OK;
}

/**
 * \brief return a pointer to a bit of the paging region `pr`.
 * This function gets used in some of the code that is responsible
 * for allocating Frame (and other) capabilities.
 */
errval_t paging_region_map(struct paging_region *pr, size_t req_size,
                           void **retbuf, size_t *ret_size)
{
    //TODO: allow it to use holes for mapping
    lvaddr_t end_addr = pr->base_addr + pr->region_size;
    size_t rem = end_addr - pr->current_addr;
    if (rem > req_size) {
        // ok
        *retbuf = (void*)pr->current_addr;
        *ret_size = req_size;
        pr->current_addr += req_size;
    } else if (rem > 0) {
        *retbuf = (void*)pr->current_addr;
        *ret_size = rem;
        pr->current_addr += rem;
        debug_printf("exhausted paging region, "
                "expect badness on next allocation\n");
    } else {
        return LIB_ERR_VSPACE_MMU_AWARE_NO_SPACE;
    }
    return SYS_ERR_OK;
}
 
/**
 * \brief free a bit of the paging region `pr`.
 * This function gets used in some of the code that is responsible
 * for allocating Frame (and other) capabilities.
 * NOTE: Implementing this function is optional.
 */
errval_t paging_region_unmap(struct paging_region *pr, lvaddr_t base,
                             size_t bytes)
{
    return SYS_ERR_OK;
}
 
/**
 * TODO(M2): Implement this function
 * \brief Find a bit of free virtual address space that is large enough to
 *        accomodate a buffer of size `bytes`.
 */
 
errval_t paging_alloc(struct paging_state *st, void **buf, size_t bytes)
{
    struct paging_frame_node *node = &st->free_node;
    while(node != NULL) {
        if(node->size >= bytes) {
            *buf = (void*)node->base_addr;
 
            lvaddr_t temp = ROUND_UP(node->base_addr + bytes, BASE_PAGE_SIZE);
            node->size -= (temp-node->base_addr);
            node->base_addr = temp;
            return SYS_ERR_OK;
        }
        node = node->next;
    }
    return LIB_ERR_OUT_OF_VIRTUAL_ADDR;
}
 
/**
 * \brief map a user provided frame, and return the VA of the mapped
 *        frame in `buf`.
 */
errval_t paging_map_frame_attr(struct paging_state *st, void **buf,
                               size_t bytes, struct capref frame,
                               int flags, void *arg1, void *arg2)
{
    errval_t err;
    err = paging_alloc(st, buf, bytes);
    assert(err_is_ok(err));
    return paging_map_fixed_attr(st, (lvaddr_t)(*buf), frame, bytes, flags);
}
 
errval_t
slab_refill_no_pagefault(struct slab_allocator *slabs, struct capref frame,
                         size_t minbytes)
{
    errval_t err;
    void *buf = NULL;
    size_t frame_size;
    size_t mapped_bytes = 0;
    int flags = VREGION_FLAGS_READ_WRITE;
    struct paging_state* st = get_current_paging_state();

    err = frame_alloc(&frame, minbytes, &frame_size);
    size_t bytes = frame_size;
    err = paging_alloc(st, &buf, bytes);

    lvaddr_t vaddr = (lvaddr_t)buf;
    while(bytes > 0) {
        struct capref l2_pt;
        if (st->l2_page_tables[ARM_L1_OFFSET(vaddr)].init) {
            l2_pt = st->l2_page_tables[ARM_L1_OFFSET(vaddr)].cap;
        } else {
            err = arml2_alloc(st, &l2_pt);
            struct capref l2_map;
            err = st->slot_alloc->alloc(st->slot_alloc, &l2_map);
 
            err = vnode_map(st->l1_page_table, l2_pt, ARM_L1_OFFSET(vaddr), VREGION_FLAGS_READ_WRITE, 0, 1, l2_map);

            st->l2_page_tables[ARM_L1_OFFSET(vaddr)].cap = l2_pt;
            st->l2_page_tables[ARM_L1_OFFSET(vaddr)].init = true; 
        }
        size_t leftover = MIN(bytes, (ARM_L2_MAX_ENTRIES - ARM_L2_OFFSET(vaddr)) * BASE_PAGE_SIZE);
 
        struct capref l2_frame;
        err = st->slot_alloc->alloc(st->slot_alloc, &l2_frame);
        err = vnode_map(l2_pt, frame, ARM_L2_OFFSET(vaddr), flags, mapped_bytes, leftover/BASE_PAGE_SIZE, l2_frame);
 
        mapped_bytes += leftover;
        bytes -= leftover;
        vaddr += leftover;
    }
    slab_grow(slabs, buf, frame_size);
 
    return SYS_ERR_OK;
}
 
/**
 * \brief map a user provided frame at user provided VA.
 */
errval_t paging_map_fixed_attr(struct paging_state *st, lvaddr_t vaddr,
        struct capref frame, size_t bytes, int flags)
{
    errval_t err;
    size_t mapped_bytes = 0;
    if(slab_freecount(&st->slab_alloc) == 0) {
        struct capref slabframe;
        st->slot_alloc->alloc(st->slot_alloc,&slabframe);
        slab_refill_no_pagefault(&st->slab_alloc,slabframe,BASE_PAGE_SIZE);
    }
    struct paging_allocated_node *used_node = (struct paging_allocated_node *)slab_alloc(&st->slab_alloc);

    used_node->addr = vaddr;
    used_node->size = bytes;
    used_node->next = st->used_node_list;
    st->used_node_list = used_node;

    while(bytes > 0) {
        struct capref l2_pt;
        if (st->l2_page_tables[ARM_L1_OFFSET(vaddr)].init) {
            l2_pt = st->l2_page_tables[ARM_L1_OFFSET(vaddr)].cap;
        } else {
            err = arml2_alloc(st, &l2_pt);
            struct capref l2_map;
            err = st->slot_alloc->alloc(st->slot_alloc, &l2_map);
 
            err = vnode_map(st->l1_page_table, l2_pt, ARM_L1_OFFSET(vaddr), VREGION_FLAGS_READ_WRITE, 0, 1, l2_map);
 
            st->l2_page_tables[ARM_L1_OFFSET(vaddr)].cap = l2_pt;
            st->l2_page_tables[ARM_L1_OFFSET(vaddr)].init = true;
 
        }
 
        size_t leftover = MIN(bytes, (ARM_L2_MAX_ENTRIES - ARM_L2_OFFSET(vaddr)) * BASE_PAGE_SIZE);
 
        struct capref l2_frame;
        err = st->slot_alloc->alloc(st->slot_alloc, &l2_frame);
        err = vnode_map(l2_pt, frame, ARM_L2_OFFSET(vaddr), flags, mapped_bytes, leftover/BASE_PAGE_SIZE, l2_frame);
 
        mapped_bytes += leftover;
        bytes -= leftover;
        vaddr += leftover;
        
    }
    return SYS_ERR_OK;
}
 
/**
 * \brief unmap region starting at address `region`.
 * NOTE: Implementing this function is optional.
 */
errval_t paging_unmap(struct paging_state *st, const void *region)
{
    return SYS_ERR_OK;
}
 
 
