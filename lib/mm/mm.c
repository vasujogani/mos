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
	debug_printf("libmm: Initializing...\n");
	assert(mm != NULL);

	mm->slot_alloc = slot_alloc_func;
	mm->slot_refill = slot_refill_func;
	mm->objtype = objtype;
	mm->slot_alloc_inst = slot_alloc_inst;
	mm->head = NULL;

	if(slab_refill_func == NULL){
	        slab_refill_func = slab_default_refill;
	}
	
	slab_init(&mm->slabs, sizeof(struct mmnode), slab_refill_func);
	struct slot_prealloc *sp = (struct slot_prealloc*) mm->slot_alloc_inst;
	sp->mm = mm;			

	debug_printf("initialized\n");
	return SYS_ERR_OK;


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
	errval_t err;
	debug_printf("Adding a capability of size %i B at %zx \n", size , base);
	struct mmnode *node = (struct mmnode*) slab_alloc(&mm->slabs);
       	assert(node != NULL);
	node->cap.base = base;
	node->cap.size = size;

	node->base = base;
	node->size = size;
	node->type = NodeType_Free;

		
	struct mmnode *curr = mm->head;
	if (curr == NULL) {
		mm->head = node;
	} else {
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = node;
		node->prev = curr;
		node->next = NULL;
	}

	mm->initial_size = size;
	mm->initial_base = base;
	mm->initial_cap = cap;

	mm->slot_alloc(mm->slot_alloc_inst, 1, &(node->cap.cap));
	err = cap_retype(node->cap.cap, mm->initial_cap, 0, mm->objtype, (gensize_t) size, 1);

	// mm->slot_alloc(mm->slot_alloc_inst, 1, &(mm->initial_cap));
	// err = cap_retype(mm->initial_cap, cap, 0, mm->objtype, (gensize_t) size, 1);

	assert(err_is_ok(err));

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
    if (slab_freecount(&mm->slabs) <= 5) {
        slab_default_refill(&mm->slabs);
    }
	if (alignment < BASE_PAGE_SIZE) {
		alignment = BASE_PAGE_SIZE;
	}
	if (size % alignment != 0) {
		size += alignment - (size % alignment);
	}

	struct mmnode *curr = mm->head;
	while(curr) {
		if (curr->type == NodeType_Free) {
			if (curr->size >= size) {
				size_t remaining = curr->size - size;
				struct mmnode *new_node = (struct mmnode*) slab_alloc(&mm->slabs);

				assert(new_node != NULL);
				new_node->type = NodeType_Allocated;

				new_node->prev = curr->prev;
				if (curr->prev != NULL) {
					curr->prev->next = new_node;
				}
				new_node->next = curr;
				curr->prev = new_node;
				
				if (curr == mm->head) {
					mm->head = new_node;
				}
						
				struct slot_prealloc *sp = (struct slot_prealloc*) mm->slot_alloc_inst;
				if (sp->meta[0].free < 3 && sp->meta[1].free < 3 && !sp->refilling) {
					sp->refilling = true;
					errval_t err = mm->slot_refill(mm->slot_alloc_inst);
					sp->refilling = false;
					assert(err_is_ok(err));

				}

				errval_t err = mm->slot_alloc(mm->slot_alloc_inst, 1, &(new_node->cap.cap));
				assert(err_is_ok(err));

				err = cap_retype(new_node->cap.cap, mm->initial_cap, curr->base - mm->initial_base, mm->objtype, size, 1);
				assert(err_is_ok(err));

				new_node->base = curr->base;
				new_node->size = size;
				curr->base += size;
				curr->size = remaining;

				*retcap = new_node->cap.cap;
				break;
			}
		}
		curr = curr->next;
	}
	return SYS_ERR_OK;

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
	struct mmnode *curr = mm->head;
	while (curr) {
		if (curr->base == base && curr->size == size) {
			curr->type = NodeType_Free;
							
			cap_destroy(curr->cap.cap);
						
			if (curr->next && curr->next->type == NodeType_Free) {
				curr->size += curr->next->size;
				struct mmnode *del_node = curr->next;
				curr->next = curr->next->next;
				if (curr->next) {
					curr->next->prev = curr;
				}
				slab_free(&mm->slabs, del_node);
			}
			if (curr->prev && curr->prev->type == NodeType_Free) {
				curr->prev->size += curr->size;
				struct mmnode *del_node = curr;
				curr->prev->next = curr->next;
				if (curr->next) {
					curr->next->prev = curr->prev;
				}
				slab_free(&mm->slabs, del_node);
			}
			break;
		}
		curr = curr->next;
	}
	return SYS_ERR_OK;

}


void mm_print(struct mm *mm) {
	struct mmnode *n = mm->head;
	int idx = 0;

	while (n) {
		struct frame_identity f;
		frame_identify(n->cap.cap, &f);
		printf("    Node %d: start: %zx, size: %"PRIu64" KB - Cap says: base: %zx size: %"PRIu64" KB - ", idx, n->base, n->size / 1024 , f.base, f.bytes / 1024);
		if (n->type == NodeType_Free) {
			printf("Node F\n");
		} else {
			printf("Node A \n");
		}
		n = n->next;
		idx++;
	}
}
