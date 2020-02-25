#include <aos/aos.h>
#include <spawn/spawn.h>

#include <elf/elf.h>
#include <aos/dispatcher_arch.h>
#include <barrelfish_kpi/paging_arm_v7.h>
#include <barrelfish_kpi/domain_params.h>
#include <spawn/multiboot.h>

extern struct bootinfo *bi;
// extern struct mm aos_mm; TODO ask about this!!!!

// TODO(M2): Implement this function such that it starts a new process
// TODO(M4): Build and pass a messaging channel to your child process
errval_t spawn_load_by_name(void * binary_name, struct spawninfo * si) {
    printf("spawn start_child: starting: %s\n", binary_name);

    errval_t err;

    // Init spawninfo
    memset(si, 0, sizeof(*si));
    si->binary_name = binary_name;

    // - Get the binary from multiboot image
    struct mem_region *mem_region = multiboot_find_module(bi, (const char *)binary_name);

    struct capref child_frame = {
        .cnode = cnode_module,
        .slot = mem_region−>mrmod_slot,
    };

    // map child_frame into new process virtual address space
    // vaddr will be return address, vsize return size

    // wiill be used for verification later
    char *binary_start = (char *)mem_region->mr_base;
    assert(*binary_start == 0x7f);
    assert(*(binary_start + 1) == 'E');
    assert(*(binary_start + 2) == 'L');
    assert(*(binary_start + 3) == 'F');


    // - Setup childs cspace
    struct capref l1_cnode;
    err = cnode_create_l1(&l1_cnode, NULL);
    if (err_is_fail(err)) {
        debug_printf("Unable to create initial L1 CNode\n");
        return err_push(err, LIB_ERR_CNODE_CREATE);
    }
    si->l1_cnode = &l1_cnode;

    for (int i = 0; i < ROOTCN_FREE_SLOT; i++) {
        struct cnoderef cnode_ref;
        err = cnode_create_foreign_l2(l1_cnode, i, cnode_ref);
        if (err_is_fail(err)) {
            debug_printf("Unable to create L2 CNode\n");
            return err_push(err, LIB_ERR_CNODE_CREATE);
        }
        si->l2_cnodes[i] = cnode_ref;
    } 

    
    // copy L1 root capability
    curr_ref.slot = TASKCN_SLOT_ROOTCN;
    err = cap_copy(curr_ref, l1_cnode);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
    }

    //SLOT_DISPFRAME: See the next section for an explanation of this.
    //SLOT_ARGSPG: A page containing a list of command line arguments.




    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_SLOT_ALLOC0, NULL);
    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_SLOT_ALLOC1, NULL);
    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_SLOT_ALLOC2, NULL);

    //allocate memory for process
    struct cnoderef base_page_cn_ref;
    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_BASE_PAGE_CN, base_page_cn_ref);
    struct capref ram_ref = {
            .cnode = base_page_cn_ref,
            .slot = 0,
    };
    for (int i=0; i<L2_CNODE_SLOTS; i++) {
        struct capref temp_cap;
        err = ram_alloc_aligned(&temp_cap, BASE_PAGE_SIZE, BASE_PAGE_SIZE);
        if (err_is_fail(err)) {
            return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
        }
        err = cap_copy(ram_ref, temp_cap);
        if (err_is_fail(err)) {
            return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
        }
        ram_ref.slot = i;
        cap_destroy(temp_cap);
    }
    
    struct cnoderef page_table_cn_ref;
    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_PAGECN, page_table_cn_ref);
    struct capref l1_ref = {
        .cnode = page_table_cn_ref,
        .slot = 0,
    };
    err = vnode_create(l1_ref, s ObjType_VNode_ARM_l1);
    err = paging_init_state(&ps, 0, l1_ref, get_default_slot_allocator());

    err = elf_load(EM_ARM, elf_alloc_func, (void *)si, vaddr, vsize, &(si->entry_addr));



    // TODO: Implement me
    // - Map multiboot module in your address space
    // - Setup childs vspace
    // - Load the ELF binary
    // - Setup dispatcher
    // - Setup environment
    // - Make dispatcher runnable

    return SYS_ERR_OK;
}

errval_t spawn_setup_dispatcher(struct spawninfo * si) {
    struct capref curr_ref = {
        .cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN],
        .slot = TASKCN_SLOT_DISPATCHER,
    };
    // capability for dispatcher
    err = dispatcher_create(curr_ref);
    if (err_is_fail(err)) {
        debug_printf("Unable to create dispatcher capref\n");
        return err;
    }
    // capability for endpoint
    struct capref dispatcher_ref = curr_ref;
    curr_ref.slot = TASKCN_SLOT_SELFEP;
    err = cap_retype(curr_ref, dispatcher_ref, 0,
                    ObjType_EndPoint, OBJSIZE_DISPATCHER, 1);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
    }

}

errval_t elf_alloc_func(void *state, genvaddr_t base, size_t size, uint32_t flags, void **ret) {
    base -= base % BASE_PAGE_SIZE;
    size += size % BASE_PAGE_SIZE;
    struct capref frame_ref;
    size_t returned_bytes;
    frame_alloc(&frame_ref, size, &returned_bytes);
    paging_map_fixed_attr(state->ps, base, frame_ref, size, flags);
    paging_map_fixed_attr(get_current_paging_state(), base, frame_ref,f size, flags);
    *ret = (void *)base;
}