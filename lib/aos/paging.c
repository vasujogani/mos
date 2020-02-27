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
#include <mm.h>

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
        struct capref pdir, struct slot_allocator *ca)
{
    debug_printf("paging_init_state %p\n", st);

    st->slot_alloc = ca;

    // Slab allocator. 64 nodes should be enough, as we'll have the Memory
    // Manager up and running before we really start mapping vaddresses.
    slab_init(&st->slabs, sizeof(struct v_region_metadata), slab_default_refill);
    static char paging_buf[sizeof(struct v_region_metadata) * 64];

    slab_grow(&st->slabs, paging_buf, sizeof(paging_buf));

    // We don't have any L2 pagetables yet, thus make sure the flags are unset.
    for (int i = 0; i < L1_PAGETABLE_ENTRIES; ++i) {
        st->l2_pt2[i].initialized = false;
    }

    st->v_space_list = (struct v_region_metadata*) slab_alloc(&st->slabs);
    st->v_space_list->base = start_vaddr;
    st->v_space_list->size = (size_t) (0xFFFFFFFF - start_vaddr);;
    st->v_space_list->type = NodeType_Free;
    st->v_space_list->next = NULL;

    // Default L1 pagetable.
    st->l1_pt = pdir;

    // TODO (M4): Implement page fault handler that installs frames when a page fault
    // occurs and keeps track of the virtual address space.
    return SYS_ERR_OK;
}

/**
 * \brief This function initializes the paging for this domain
 * It is called once before main.
 */
errval_t paging_init(void)
{
    debug_printf("paging_init\n");

    // M2:
    // TODO: Where should the pdir capref come from?
    struct capref l1_cap = {
        .cnode = cnode_page,
        .slot = 0
    };
    paging_init_state(&current, VADDR_OFFSET, l1_cap,
            get_default_slot_allocator());
    set_current_paging_state(&current);

    // TODO (M4): initialize self-paging handler
    // TIP: use thread_set_exception_handler() to setup a page fault handler
    // TIP: Think about the fact that later on, you'll have to make sure that
    // you can handle page faults in any thread of a domain.
    // TIP: it might be a good idea to call paging_init_state() from here to
    // avoid code duplication.

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
errval_t paging_region_init(struct paging_state *st, struct paging_region *pr, size_t size)
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
    lvaddr_t end_addr = pr->base_addr + pr->region_size;
    ssize_t rem = end_addr - pr->current_addr;
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
errval_t paging_region_unmap(struct paging_region *pr, lvaddr_t base, size_t bytes)
{
    // TIP: you will need to keep track of possible holes in the region
    return SYS_ERR_OK;
}

/**
 *
 * \brief Find a bit of free virtual address space that is large enough to
 *        accomodate a buffer of size `bytes`.
 */
errval_t paging_alloc(struct paging_state *st, void **buf, size_t bytes)
{
    // TODO: M2 Implement this function
    struct v_region_metadata *node = st->v_space_list;
    while (node != NULL) {
        if (node->type == NodeType_Free && node->size >= bytes) {
            *buf = (void*) node->base;
            return SYS_ERR_OK;
        }
        node = node->next;
    }
    *buf = NULL;
    return LIB_ERR_VREGION_NOT_FOUND;
}

/**
 * \brief map a user provided frame, and return the VA of the mapped
 *        frame in `buf`.
 */
errval_t paging_map_frame_attr(struct paging_state *st, void **buf,
                               size_t bytes, struct capref frame,
                               int flags, void *arg1, void *arg2)
{
    if (slab_freecount(&st->slabs) < 4 && !st->slab_refilling) {
        st->slab_refilling = true;
        errval_t err = st->slabs.refill_func(&st->slabs);
        if (err_is_fail(err)) {
            DEBUG_ERR(err, "slab refill_func failed");
            return LIB_ERR_VREGION_MAP;
        }
        st->slab_refilling = false;
    }
    errval_t err = paging_alloc(st, buf, bytes);
    if (err_is_fail(err)) {
        return err;
    }
    return paging_map_fixed_attr(st, (lvaddr_t)(*buf), frame, bytes, flags);
}

errval_t
slab_refill_no_pagefault(struct slab_allocator *slabs, struct capref frame, size_t minbytes)
{
    return SYS_ERR_OK;
}

/**
 * \brief map a user provided frame at user provided VA.
 * TODO(M1): Map a frame assuming all mappings will fit into one L2 pt
 * TODO(M2): General case
 */
errval_t paging_map_fixed_attr(struct paging_state *st, lvaddr_t vaddr,
        struct capref frame, size_t bytes, int flags)
{
    /* Step 1: Check if the virtual memory area wanted by the user is in fact
               free (check corresponding page_node). */
    struct v_region_metadata *node = st->v_space_list;
    while (bytes > 0) {
        if (node == NULL) {
            // Couldn't find node, err out.
            return LIB_ERR_VREGION_MAP;
        }
        if (node->type == NodeType_Free && node->base =< vaddr && node->base + node->size >= vaddr + bytes) {
            node->type = NodeType_Allocated;
            if (node->base + node->size > vaddr + bytes) {
                // Need new (free) node to the right;
                struct v_region_metadata *n = (struct v_region_metadata*) slab_alloc(&st->slabs);
                n->type = NodeType_Free;
                n->base = vaddr + bytes;
                n->size = node->size - (vaddr - node->base) - bytes;
                n->next = node->next;
                node->next = n;
                node->size -= n->size;
            }

            if (vaddr > node->base) {
                // Need new (free) node to the left.
                struct v_region_metadata *n = (struct v_region_metadata*) slab_alloc(&st->slabs);
                n->type = NodeType_Free;
                n->base = node->base;
                n->size = vaddr - node->base;
                n->next = node;
                if (st->v_space_list == node) {
                    st->v_space_list = left;
                }
                node->base = vaddr;
                node->size -= n->size;
            }

            uint32_t amt_mapped = 0;
            errval_t err;
            while (bytes > 0) {
                struct capref l2;

                if (st->l2_pt2[ARM_L1_OFFSET(vaddr)].initialized) {
                    l2 = st->l2_pt2[ARM_L1_OFFSET(vaddr)].cap;
                } else {
                    // Need to allocate a new L2 pagetable.
                    err = arml2_alloc(st, &l2);
                    if (err_is_fail(err)) {
                        return err;
                    }

                    struct capref l1mapping;
                    st->slot_alloc->alloc(st->slot_alloc, &l1mapping);
                    err = vnode_map(st->l1_pt, l2, ARM_L1_OFFSET(vaddr),
                            VREGION_FLAGS_READ_WRITE, 0, 1, l1mapping);
                    if (err_is_fail(err)) {
                        // DEBUG_ERR(err, "Mapping L2 to L1");
                        return err;
                    }

                    st->l2_pt2[ARM_L1_OFFSET(vaddr)].cap = l2;
                    st->l2_pt2[ARM_L1_OFFSET(vaddr)].initialized = true;
                }

                // Get index frame should start at in current L2 table.
                uint16_t remaining_ptes = ARM_L2_MAX_ENTRIES - ARM_L2_OFFSET(vaddr);
                size_t map = (bytes < remaining_ptes * BASE_PAGE_SIZE)
                        ? bytes : remaining_ptes * BASE_PAGE_SIZE;

                /* Step 3: Perform mapping. */
                struct capref copy;
                st->slot_alloc->alloc(st->slot_alloc, &copy);
                err = vnode_map(l2,
                        frame/*cap_to_map*/,
                        ARM_L2_OFFSET(vaddr),
                        flags,
                        amt_mapped,
                        map / BASE_PAGE_SIZE,
                        copy);
                if (err_is_fail(err)) {
                    return err;
                }

                mapped_size += map;
                bytes -= map;
                vaddr += map;
            }
            if (bytes > 0) {
                node = node->next;
            }
        }

        /* Step 2: Mark node as allocated & split t. */
        // TODO: If further steps fail and this function returns without success
        //       we should free the node & merge it back.
        
    }

    return SYS_ERR_OK;
}

/**
 * \brief unmap a user provided frame, and return the VA of the mapped
 *        frame in `buf`.
 * NOTE: Implementing this function is optional.
 */
errval_t paging_unmap(struct paging_state *st, const void *region)
{
    return SYS_ERR_OK;
}