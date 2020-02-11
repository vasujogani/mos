/**
 * \file
 * \brief A library for managing physical memory (i.e., caps)
 */

#include <mm/mm.h>
#include <aos/debug.h>


/**
 * Initialize the memory manager.
 *
 * \param  mm               The mm struct to initialize.
 * \param  objtype          The cap type this manager should deal with.
 * \param  slab_refill_func Custom function for refilling the slab allocator.
 * \param  slot_alloc_func  Function for allocating capability slots.
 * \param  slot_refill_func Function for refilling (making) new slots.
 * \param  slot_alloc_inst  Pointer to a slot allocator instance (typically passed to the alloc and refill functions).
 */
errval_t mm_init(struct mm *mm, enum objtype objtype,
                 slab_refill_func_t slab_refill_func,
                 slot_alloc_t slot_alloc_func,
                 slot_refill_t slot_refill_func,
                 void *slot_alloc_inst)
{
    assert(mm != NULL);
    mm->slot_alloc = slot_alloc_func;
    mm->objtype = objtype;
    mm->slot_refill = slot_refill_func;
    mm->slot_alloc_inst = slot_alloc_inst;
    mm->objtype = objtype;
    mm->head = NULL;

    // create slab allocator
    struct slab_allocator slab_alloc;
    slab_alloc.slabs = NULL;
    slab_alloc.blocksize = sizeof(struct mmnode);
    slab_alloc.refill_func = slab_refill_func;
    mm->slabs = slab_alloc;

    return SYS_ERR_OK; //TODO add validation
}

/**
 * Destroys the memory allocator.
 */
void mm_destroy(struct mm *mm)
{
}

/**
 * Adds a capability to the memory manager.
 *
 * \param  cap  Capability to add
 * \param  base Physical base address of the capability
 * \param  size Size of the capability (in bytes)
 */
errval_t mm_add(struct mm *mm, struct capref cap, genpaddr_t base, size_t size)
{
    printf("inside mm_add\n");
    struct mmnode *node = slab_alloc(&mm->slabs);
    if (!node) {
        return -1;
    }
    node->type = NodeType_Free;

    // create capinfo object
    struct capinfo info;
    info.cap = cap;
    info.base = base;
    info.size = size;
    node->cap = info;

    node->next = mm->head;
    node->prev = NULL;
    mm->head->prev = node;
    // node->left = NULL;
    // node->right = NULL;
    mm->head = node;
    node->free =  true;

    node->base = base;
    node->size = size;

    return SYS_ERR_OK;
}

errval_t mm_add_inspot(struct mm *mm, struct capref cap, struct mmnode *parent, genpaddr_t base, size_t size) {
    
    assert(prev);
    struct mmnode *node = slab_alloc(&mm->slabs);
    if (!node) {
        return -1;
    }
    node->type = NodeType_Free;

    // create capinfo object
    struct capinfo info;
    info.cap = cap;
    info.base = base;
    info.size = size;
    node->cap = info;

    node->prev = parent;
    node->next = parent->next;
    parent->next = node;

    node->base = base;
    node->size = size;

    return SYS_ERR_OK;
}

/**
 * Allocate aligned physical memory.
 *
 * \param       mm        The memory manager.
 * \param       size      How much memory to allocate.
 * \param       alignment The alignment requirement of the base address for your memory.
 * \param[out]  retcap    Capability for the allocated region.
 */
errval_t mm_alloc_aligned(struct mm *mm, size_t size, size_t alignment, struct capref *retcap)
{
    // TODO: Implement
    return LIB_ERR_NOT_IMPLEMENTED;
}

// static bool can_allocate_in_list(struct mmnode *current_root, size_t size) {
//     // go down the list while the child is != null
//     while (current_root && (!current_root->free || current_root->size < size)) {
//         current_root = current_root->n;
//     }
//     if (current_root && current_root->free && current_root->size >= size) {
//         // retype
//         // errval_t cap_retype(dest, src, offset, ObjType_RAM, size, 1);
//         // create new mmnode, set references accordingly
//         // may need to consider errval cap_retype returns, but for now don't worry
//         // also consider effects this has on the cnode
//         return true;
//     }
//     else {
//         return false;
//     }
// }

/**
 * Allocate physical memory.
 *
 * \param       mm        The memory manager.
 * \param       size      How much memory to allocate.
 * \param[out]  retcap    Capability for the allocated region.
 */
errval_t mm_alloc(struct mm *mm, size_t size, struct capref *retcap)
{
    struct mmnode *curr = mm->head;
    while (curr && (curr->type == NodeType_Allocated || curr->size < size)) {
        curr = curr->next;
    }

    if (!curr) {
        // couldn't find a free region
        //TODO: add correct error code
        return -1;
    }
    errval_t err = cap_retype(retcap, (curr->cap).cap, 0, ObjType_RAM, size, 1);
    if (err != SYS_ERR_OK) {
        return err;
    }
    if (curr->size > size) {
        struct capref remainder;
        err = slot_alloc(&remainder);
        if (err != SYS_ERR_OK) {
            return err;
        }
        err = cap_retype(&remainder, (curr->cap).cap, size, ObjType_RAM, curr->size - size, 1);
        if (err != SYS_ERR_OK) {
            return err;
        }
        err = mm_add_inspot(mm, &remainder, curr, curr->base + size, curr->size - size);
        curr->type = NodeType_Allocated;
    }
    return err;

    // bool allocated = false;
    // struct mmnode *current_root = mm->head;
    // while (current_root->next && !allocated) {
    //     //can we allocate in this list?
    //     can_allocate_in_list(current_root, size);
    //     current_root = current_root->next;
    // }
    // if (!allocated)
    // {
    //     //error
    // }  
}

/**
 * Free a certain region (for later re-use).
 *
 * \param       mm        The memory manager.
 * \param       cap       The capability to free.
 * \param       base      The physical base address of the region.
 * \param       size      The size of the region.
 */
errval_t mm_free(struct mm *mm, struct capref cap, genpaddr_t base, gensize_t size)
{
    // iterate through and find the position in the list, and then coalesce recursively
    //
}
