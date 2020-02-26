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
    debug_printf("paging_init_state\n");
    // TODO (M2): implement state struct initialization
    // TODO (M4): Implement page fault handler that installs frames when a page fault
    // occurs and keeps track of the virtual address space.

    st->l1_pt = pdir;
    st->slot_alloc = ca;
    for ( int i = 0; i < ARM_L1_MAX_ENTRIES; i++ ) {
        st->l2_pts[i].initialized = false;
    }
    /*
    VASU
    // initialze v_space_list
    // need slab alloc to create enough space for this node or not keep a pointer in the first place
    st->v_space_list.base = start_vaddr;
    st->v_space_list.size = size;
    st->v_space_list.v_region_nodetype = NodeType_Free;
    */
    slab_init(&st->slabs, sizeof(struct v_region_metadata), slab_default_refill);
    struct v_region_metadata *head = slab_alloc(&st->slabs);
    head->type = Nodetype_Free;
    head->base = start_vaddr;
    // TODO (M2):
    // get addresses from the lecture slides
    // head->size = max_vaddr - start_vaddr;
    head->next = NULL;
    st->v_space_list = head;
    return SYS_ERR_OK;
}

/**
 * \brief This function initializes the paging for this domain
 * It is called once before main.
 */
errval_t paging_init(void)
{
    debug_printf("paging_init\n");
    // TODO (M2): Call paging_init_state for &current
    // TODO (M4): initialize self-paging handler
    // TIP: use thread_set_exception_handler() to setup a page fault handler
    // TIP: Think about the fact that later on, you'll have to make sure that
    // you can handle page faults in any thread of a domain.
    // TIP: it might be a good idea to call paging_init_state() from here to
    // avoid code duplication.
    set_current_paging_state(&current);

    struct capref l1_pt = {
        .cnode = cnode_page,
        .slot = 0,
    };

    struct slot_allocator *default_allocator = get_default_slot_allocator();
    // TODO (M2): Set start_vaddr to the appropriate address
    paging_init_state(&current, 0, l1_pt, default_allocator); 
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
    // XXX: should free up some space in paging region, however need to track
    //      holes for non-trivial case
    return SYS_ERR_OK;
}

/**
<<<<<<< HEAD
 *
=======
 * TODO(M2): Implement this function
>>>>>>> 20d68a2be105e2405b60d5354556aa090bdbab49
 * \brief Find a bit of free virtual address space that is large enough to
 *        accomodate a buffer of size `bytes`.
 */
errval_t paging_alloc(struct paging_state *st, void **buf, size_t bytes)
{
    struct v_region_metadata *node = st->v_space_list; 
    while (node) {
        if (node->type == Nodetype_Free && node->size >= bytes) {
            *buf = (void*) node->base;
            // TODO(M2): Should rounding be moved outside of the loop?
            node->base += bytes + (BASE_PAGE_SIZE - bytes % BASE_PAGE_SIZE);
            node->size -= (bytes + (BASE_PAGE_SIZE - bytes % BASE_PAGE_SIZE));
            return SYS_ERR_OK;
        }
        node = node->next;
    }
    *buf = NULL;
    // TODO(M2): Is this correct? Or should we return something indicating an error - no more
    // free space in the virtual address space?
    // probably should be an error - but which macro?
    return SYS_ERR_OK;
}

/**
 * \brief map a user provided frame, and return the VA of the mapped
 *        frame in `buf`.
 */
errval_t paging_map_frame_attr(struct paging_state *st, void **buf,
                               size_t bytes, struct capref frame,
                               int flags, void *arg1, void *arg2)
{
    errval_t err = paging_alloc(st, buf, bytes);
    if (err_is_fail(err)) {
        return err;
    }
    return paging_map_fixed_attr(st, (lvaddr_t)(*buf), frame, bytes, flags);
}

errval_t
slab_refill_no_pagefault(struct slab_allocator *slabs, struct capref frame, size_t minbytes)
{
    // Refill the two-level slot allocator without causing a page-fault
    return SYS_ERR_OK;
}

/**
 * \brief map a user provided frame at user provided VA.
 * TODO(M1): Map a frame assuming all mappings will fit into one L2 pt
 * TODO(M2): General case 
 * TODO(M2): Handle keeping track of the mapping - create a node to indicate it's been allocated
 */
errval_t paging_map_fixed_attr(struct paging_state *st, lvaddr_t vaddr,
        struct capref frame, size_t bytes, int flags)
{
    // TODO(M2): Should we get rid of this? probably won't do anything - will already be aligned
    // if they went through paging_alloc. Don't go through - their problem. 
    // align the vaddr
    if (vaddr % BASE_PAGE_SIZE != 0) {
        vaddr -= vaddr % BASE_PAGE_SIZE;
    }
    
    errval_t err;

    struct capref l2;
    
    // round bytes up to page size to get the number of ptes needed to be mapped
    if (bytes % BASE_PAGE_SIZE != 0) {
        bytes += (size_t) BASE_PAGE_SIZE - (bytes % BASE_PAGE_SIZE);
    }

    int pte_count = bytes / BASE_PAGE_SIZE;
    int remaining_ptes, frame_offset;
    frame_offset = 0;

    // TODO(M2): Create a node to keep track of allocated space
    // Should this be here, or in paging_alloc?
    struct v_region_metadata *allocated = slab_alloc(&st->slabs);
    allocated->type = Nodetype_Allocated;
    allocated->base = vaddr;
    allocated->size = bytes;
    // insert in the list st keeps track of
    // TODO(M2): Verify that this is correct

    // Use 1 list - make coalescing easier 
    struct v_region_metadata *node = st->v_space_list;
    while (node->next && node->base < vaddr) {
        node = node->next;
    }
    allocated->next = node->next;
    node->next = allocated;
  
    /* 
    // or use 2 lists - fewer checks when allocating 
    if (st->allocated_list) {
        // insert, sorted by address
        struct v_region_metadata *current = st->allocated_list;
        while (current->next && current->base < vaddr) {
            current = current->next;
        }
        allocated->next = current->next;
        current->next = allocated;
    }
    else {
        st->allocated_list = allocated;
    }
    */

    while ( pte_count > 0 )
    {
        // check if l2 pt already exists
        if (st->l2_pts[ARM_L1_OFFSET(vaddr)].initialized == true) {
            l2 = st->l2_pts[ARM_L1_OFFSET(vaddr)].cap;
        }
        // otherwise, allocate the l2 pt
        else {
            err = arml2_alloc(st, &l2);
            if (err_is_fail(err)) {
                debug_printf("arml2_alloc failed: %s\n", err_getstring(err));
                return err;
            }
            // update the l1 pt
            // need to call vnode_map
            struct capref l1mapping;
            err = st->slot_alloc->alloc(st->slot_alloc, &l1mapping);
            if (err_is_fail(err)) {
                debug_printf("slot_alloc failed: %s\n", err_getstring(err));
                return err;
            }

            err = vnode_map(st->l1_pt, l2, ARM_L1_OFFSET(vaddr), VREGION_FLAGS_READ_WRITE, 0, 1, l1mapping);
            if (err_is_fail(err)) {
                debug_printf("vnode_map failed: %s\n", err_getstring(err));
                return err;
            }
            
            // update the page_info struct to include the new l2 pt
            st->l2_pts[ARM_L1_OFFSET(vaddr)].initialized = true;
            st->l2_pts[ARM_L1_OFFSET(vaddr)].cap = l2;
        }
   
        // need to determine the pte_count based on the size of the frame
        // also, what do you pass for the offset? 
        // struct frame_identity fi;
        // err = frame_identify(frame, &fi);
        // if (err_is_fail(err)) {
        //     debug_printf("frame_identify failed: %s\n", err_getstring(err));
        // } 
        
        // determine pte_count based on size of frame
        // call slot_alloc to get a capref for mapping ???
        struct capref mapping;
        
        err = st->slot_alloc->alloc(st->slot_alloc, &mapping);
        if (err_is_fail(err)) {
            debug_printf("slot_alloc failed: %s\n", err_getstring(err));
            return err;
        }

        // get the ptes available in this table past the offset
        remaining_ptes = ARM_L2_MAX_ENTRIES - ARM_L2_OFFSET(vaddr);
        
        if (remaining_ptes < pte_count) {
            err = vnode_map(l2, frame, ARM_L2_OFFSET(vaddr), flags, frame_offset, remaining_ptes, mapping);
            pte_count -= remaining_ptes;
            vaddr += remaining_ptes * BASE_PAGE_SIZE;
            frame_offset += remaining_ptes * BASE_PAGE_SIZE;
        } 
        else {
            err = vnode_map(l2, frame, ARM_L2_OFFSET(vaddr), flags, frame_offset, pte_count, mapping);
            pte_count = 0;
        }
        if (err_is_fail(err)) {
            debug_printf("vnode_map failed: %s\n", err_getstring(err));
            return err;
        }
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
