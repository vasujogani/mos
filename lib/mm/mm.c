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
    mm->head = NULL;

    if (slab_refill_func==NULL) {
        slab_refill_func = slab_default_refill;
    }

    slab_init(&mm->slabs, sizeof(struct mmnode), slab_refill_func);

    return SYS_ERR_OK; //TODO add validation
}

/**
 * Destroys the memory allocator.
 */
void mm_destroy(struct mm *mm)
{
    struct mmnode *curr = mm->head;
    while(curr) {
        cap_destroy(curr->cap.cap);
        curr->type = NodeType_Free;
        slab_free(&mm->slabs, &curr);
    }
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
    void *baseptr = slab_alloc(&mm->slabs);
    if (baseptr == NULL) {
        // @TODO: return some error
    }
    struct mmnode *node = (struct mmnode*) baseptr;

    node->type = NodeType_Free;
    node->base = base;
    node->size = size;
    node->free_children = 0;
    node->parent = NULL;

    // create capinfo object
    struct capinfo info;
    info.cap = cap;
    info.base = base;
    info.size = size;
    node->cap = info;

    // Add to the end of the list
    struct mmnode *curr = mm->head;
    if (curr == NULL) {
        mm->head = node;
        node->next = NULL:
        node->prev = NULL;
    } else {
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
        node->prev = curr;
        node->next = NULL;
    }


    // Allocate a slot for new capability
    err = mm_slot_alloc(mm, 1, &(node->cap.cap));
    assert(!err_is_fail(err));
    
    // Initialize the original base and size
    mm->initial_base = base;
    mm->initial_size = size;

    return err;

    
    // @TODO: add it to the end
    // REVERSE list?
    // node->next = mm->head;
    // node->prev = NULL;
    // mm->head->prev = node;
    // node->left = NULL;
    // node->right = NULL;
    // mm->head = node;
    // node->free =  true;

    
    return SYS_ERR_OK;
}

struct mmnode *mm_add_inspot(struct mm *mm, struct capref cap, struct mmnode *parent, genpaddr_t base, size_t size) {
    
    assert(prev);
    struct mmnode *node = (struct mmnode *)slab_alloc(&mm->slabs);
    assert(!node);
    node->type = NodeType_Free;
    node->free_children = 0;
    node->parent = NULL;

    // create capinfo object
    struct capinfo info;
    info.cap = cap;
    info.base = base;
    info.size = size;
    node->cap = info;

    node->prev = parent;
    node->next = parent->next;
    parent->next->prev = node;
    parent->next = node;
    

    node->base = base;
    node->size = size;

    return node;
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
    if (size < alignment) {
        size = alignment;
    } else {
        size = size + (alignment - (size % alignment));
    }
    struct mmnode *curr = mm->head;
    size_t offset = 0;
    while (curr) {
        if (!(curr->type == NodeType_Allocated || curr->size < size)) {
            offset = alignment - (curr->base % alignment);
            if (offset + size <= curr->size) {
                break;
            }
        }
        curr = curr->next;
    }

    assert(curr);
    if (!curr) {
        // couldn't find a free region
        //TODO: add correct error code
        return -1;
    }
    // create a capability and mmnode for allocated memory going to user
    errval_t err = mm->slot_alloc(mm->slot_alloc_inst, 1, retcap);
    assert(err_is_ok(err));
    struct capinfo cap = curr->cap;
    err = cap_retype(retcap, cap.cap, offset, ObjType_RAM, size, 1);
    struct mmnode *allocated_space_node = mm_add_inspot(mm, &retcap, curr, offset, size);
    allocated_space_node->parent = curr;
    allocated_space_node->type = NodeType_Allocated;
    assert(err_is_ok(err));
    
    curr->type = NodeType_Allocated;

    // add capability for remaining space (after)
    if (offset + size < curr->size) {
        struct capref remainder;
        err = mm->slot_alloc(mm->slot_alloc_inst, 1, &remainder);
        assert(err_is_ok(err));
        err = cap_retype(&remainder, cap.cap, offset + size, ObjType_RAM, curr->size - (offset + size), 1);
        struct mmnode *next = mm_add_inspot(mm, &remainder, allocated_space_node, offset + size, curr->size - (offset + size));
        next->type = NodeType_Free;
        next->parent = curr;
    }
    // @NOTE: not needed 
    // if (curr->parent != NULL) {
    //     (curr->parent)->children--; 
    // }
    curr->free_children = 1;
    return err;
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
    return mm_alloc_aligned(mm, size, BASE_PAGE_SIZE, retcap);
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
    // if any node is equal to prev, remove curr node
    struct mmnode *curr = mm->head;
    while (curr) {
        if(curr->base == base && curr->size == size) {
            curr->parent->type = NodeType_Free;
            curr->parent->free_children = 2;
            
            cap_destroy(curr->cap.cap);

            curr->parent->next = curr->next;

            if (curr->parent->next) {
                cap_destroy(curr->parent->next->cap.cap)

                curr->parent->next = curr->parent->next->next;
                curr->parent->next->next->prev = curr->parent;
            }
        }
    }

    return SYS_ERR_OK;
}
