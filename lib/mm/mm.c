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
    assert(baseptr != NULL);

    struct mmnode *node = (struct mmnode*) baseptr;

    node->type = NodeType_Free;
    node->base = base;
    node->size = size;

    // create capinfo object
    struct capinfo info;
    info.cap = cap;
    info.base = base;
    info.size = size;
    node->cap = info;

    printf("\tbefore adding to list\n");
    // Add to the end of the list
    struct mmnode *curr = mm->head;
    if (curr == NULL) {
        mm->head = node;
        node->next = NULL;
        node->prev = NULL;
    } else {
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
        node->prev = curr;
        node->next = NULL;
    }
    printf("\tsize of added ram cap is%d\n", size );
    printf("\taddress of addded ram cap is %llx\n", base);
    printf("\tafter adding to list\n");


    // Allocate a slot for new capability
    // errval_t err = mm->slot_alloc(&(mm->slot_alloc_inst), 1, &(node->cap.cap));
    // assert(err_is_ok(err));
    
    // Initialize the original base and size
    // mm->initial_base = base;
    // mm->initial_size = size;

    // @TODO: initial_cap assign it with cap
    mm->initial_cap = cap;

    // return err;
    
    // @TODO: add it to the end
    // REVERSE list?
    // node->next = mm->head;
    // node->prev = NULL;
    // mm->head->prev = node;
    // node->left = NULL;
    // node->right = NULL;
    // mm->head = node;
    // node->free =  true;

    printf("/tleaving mm_add\n");
    return SYS_ERR_OK;
}

// struct mmnode *mm_add_inspot(struct mm *mm, struct capref cap, struct mmnode *parent, genpaddr_t base, size_t size) {
    
//     assert(prev);
//     struct mmnode *node = (struct mmnode *)slab_alloc(&mm->slabs);
//     assert(!node);
//     node->type = NodeType_Free;
//     node->free_children = 0;
//     node->parent = NULL;

//     // create capinfo object
//     struct capinfo info;
//     info.cap = cap;
//     info.base = base;
//     info.size = size;
//     node->cap = info;

//     node->prev = parent;
//     node->next = parent->next;
//     parent->next->prev = node;
//     parent->next = node;
    

//     node->base = base;
//     node->size = size;

//     return node;
// }

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
    errval_t err;
    // make size page size aligned
    if (size % alignment != 0) {
        size += (size_t) alignment - (size % alignment);
    }
    

    //finding a free slot
    struct mmnode *curr = mm->head;
    size_t curr_size = (size_t)curr->size;
    genpaddr_t align_base = alignment;
    int offset = 0;
    while(curr) {
        if (curr->type == NodeType_Free && size <= curr_size) {
            offset = 0;
            if (curr->base < align_base) {
                offset = align_base - curr->base;
            } else {
                offset = curr->base % align_base;
            }
 //           if (offset + size <= curr_size) {
     //           break;
   //         }
  		    break;
        }
        curr = curr->next;
        curr_size = (size_t)curr->size;
    }
    assert(curr);
    genpaddr_t original_addr = curr->base;
	
    struct mmnode *new_node = (struct mmnode*) slab_alloc(&mm->slabs) ;

    curr->size -= size;
    curr->base += (genpaddr_t) size;


    new_node->base = original_addr;
    new_node->size = size;

    if (curr->prev == NULL) {
	mm->head = new_node;
	new_node->next = curr;
	curr->prev = new_node;
    } else if (curr->next == NULL) {
	new_node->next = curr;
	curr->prev = new_node;
    }
    new_node->cap.base = original_addr;
    new_node->cap.size = size;
    curr->cap.size -= size;
    curr->cap.base += size;

    mm_slot_alloc(mm, 1, &(new_node->cap.cap));
    cap_retype(new_node->cap.cap, mm->initial_cap, new_node->base - mm->initial_base, mm->objtype, (gensize_t) size, 1);
    new_node->type = NodeType_Allocated;
    *retcap = new_node->cap.cap;
    return SYS_ERR_OK;
   // if (curr_size == size) {
   //     curr->type = NodeType_Allocated;
//       curr->cap.size = size;
 //      curr->cap.base += size;
 //      err = mm->slot_alloc(&(mm->slot_alloc_inst), 1, &(curr->cap.cap));
 //      assert(err_is_ok(err));
//
 //      cap_retype(curr->cap.cap, mm->initial_cap, curr->base, mm->objtype, size, 1);
//
 //      *retcap = curr->cap.cap;
 //  }
 //  else {
  //     if  (offset > 0) {
   //        // insert new free node earlier
  //         struct mmnode *new_node = slab_alloc(&mm->slabs);
 //          new_node->base = original_addr;
 //          new_node->cap.base = original_addr;
 //          new_node->size = offset - curr->base;
 //          new_node->cap.size = offset - curr->base;
 //          new_node->type = NodeType_Free;
//
//           new_node->next = curr;
//           struct mmnode *prev = curr->prev;
//           new_node->prev = prev;
 //          curr->prev = new_node;
 //          if (prev) {
 //              prev->next = new_node;
 //          }
 //      }

       // create new node with capref to return to user
  //       struct mmnode *new_node = slab_alloc(&mm->slabs);
    //     new_node->base = original_addr + offset;
   //      new_node->cap.base = original_addr + offset;
     //    new_node->size = size;
     //    new_node->cap.size = size;
       //  new_node->type = NodeType_Allocated;

       //  new_node->next = curr;
        // struct mmnode *prev = curr->prev;
        // new_node->prev = prev;
        // if 
        // if (prev) {
          //   prev->next = new_node;
        // }
        // curr->prev = new_node;

        // curr->cap.size -= size;
        // curr->cap.base += size;

        // err = mm->slot_alloc(&(mm->slot_alloc_inst), 1, &(new_node->cap.cap));
        // new_node->cap.cap.cnode.level = 1;

        // assert(err_is_ok(err));

        // cap_retype(new_node->cap.cap, mm->initial_cap, new_node->base, mm->objtype, size, 1);
        // *retcap = new_node->cap.cap;
    // }
     // return SYS_ERR_OK;
}

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
        if (base >= curr->base && (base + size) <= (curr->base + curr->size)) {
            //free
            cap_destroy(curr->cap.cap);
            // curr->cap = NULL;
            //coalesce
            struct mmnode *left = curr->prev;
            struct mmnode *right = curr->next;
            if (left && left->type == NodeType_Free) {
                curr->base = left->base;
                curr->size += left->size;
                curr->prev = left->prev;
                slab_free(&(mm->slabs), left);
            }
            if (right && right->type == NodeType_Free) {
                curr->size += right->size;
                curr->next = right->next;
                slab_free(&(mm->slabs), right);
            }

        }
    }
    return SYS_ERR_OK;
}

void mm_print(struct mm *mm) {
    struct mmnode *curr = mm->head;
    while (curr) {
        printf("I go from %llx to %llx\n", curr->base, curr->base + curr->size);
        curr = curr->next;
    }
}
