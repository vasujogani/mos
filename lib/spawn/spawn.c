#include <aos/aos.h>
#include <spawn/spawn.h>

#include <elf/elf.h>
#include <aos/dispatcher_arch.h>
#include <barrelfish_kpi/paging_arm_v7.h>
#include <barrelfish_kpi/domain_params.h>
#include <spawn/multiboot.h>

extern struct bootinfo *bi;

// extern struct mm aos_mm; TODO ask about this!!!!
errval_t elf_alloc_func(void *state, genvaddr_t base, size_t size, uint32_t flags, void **ret); 
errval_t spawn_setup_dispatcher(struct spawninfo * si);

// TODO(M2): Implement this function such that it starts a new process
// TODO(M4): Build and pass a messaging channel to your child process
errval_t spawn_load_by_name(void * binary_name, struct spawninfo * si) {
    printf("spawn start_child: starting: %s\n", binary_name);

//    errval_t err;

    // Init spawninfo
    printf("AA\n");
    memset(si, 0, sizeof(*si));
    printf("BB\n");
    si->binary_name = binary_name;
    printf("CC\n");
    // - Get the binary from multiboot image
    struct mem_region *mem_region = multiboot_find_module(bi, (const char *)binary_name);
    printf("A\n");
    struct capref child_frame_cap = {
        .cnode = cnode_module,
        .slot = mem_region->mrmod_slot,
    };
    printf("B\n");
    // map child_frame into new process virtual address space
    struct frame_identity frame;
    frame_identify(child_frame_cap, &frame);
    printf("C\n");
    lvaddr_t elf_addr;
    printf("A\n");
    paging_map_frame(get_current_paging_state(), (void *)&elf_addr, frame.bytes, child_frame_cap, NULL, NULL);
    printf("B\n");
    // verify
    char *binary_start = (char *)elf_addr;
    assert(*binary_start == 0x7f);
    assert(*(binary_start + 1) == 'E');
    assert(*(binary_start + 2) == 'L');
    assert(*(binary_start + 3) == 'F');

//     // - Setup childs cspace
//     struct cnoderef l1_cnode_ref;
//     err = cnode_create_l1(&si->l1_cnode, l1_cnode_ref);
//     if (err_is_fail(err)) {
//         debug_printf("Unable to create initial L1 CNode\n");
//         return err_push(err, LIB_ERR_CNODE_CREATE);
//     }

//     for (int i = 0; i < ROOTCN_FREE_SLOT; i++) {
//         err = cnode_create_foreign_l2(si->l1_cnode, i, si->l2_cnodes[i]);
//         if (err_is_fail(err)) {
//             debug_printf("Unable to create L2 CNode\n");
//             return err_push(err, LIB_ERR_CNODE_CREATE);
//         }
//     } 

    
//     // copy L1 root capability
//     struct capref curr_ref;
//     curr_ref.slot = TASKCN_SLOT_ROOTCN;
//     curr_ref.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
//     err = cap_copy(curr_ref, si->l1_cnode);
//     if (err_is_fail(err)) {
//         return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
//     }

//     //SLOT_DISPFRAME: See the next section for an explanation of this.
//     //SLOT_ARGSPG: A page containing a list of command line arguments.




// //    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_SLOT_ALLOC0, NULL);
// //    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_SLOT_ALLOC1, NULL);
// //    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_SLOT_ALLOC2, NULL);

//     //allocate memory for process
// //    struct cnoderef base_page_cn_ref;
// //    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_BASE_PAGE_CN, base_page_cn_ref);
//     struct capref ram_ref = {
//             .cnode = si->l2_cnodes[ROOTCN_SLOT_BASE_PAGE_CN],
//             .slot = 0,
//     };
//     for (int i=0; i<L2_CNODE_SLOTS; i++) {
//         struct capref temp_cap;
//         err = ram_alloc_aligned(&temp_cap, BASE_PAGE_SIZE, BASE_PAGE_SIZE);
//         if (err_is_fail(err)) {
//             return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
//         }
//         err = cap_copy(ram_ref, temp_cap);
//         if (err_is_fail(err)) {
//             return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
//         }
//         ram_ref.slot = i;
//         cap_destroy(temp_cap);
//     }
    
//     // vspace
// //    struct cnoderef page_table_cn_ref;
// //    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_PAGECN, page_table_cn_ref);
// //  create a new l1 pt in the current vspace and copy it to the child's since child does not have vspace for pt
    
//     si->l1_pagetable.cnode = si->l2_cnodes[ROOTCN_SLOT_PAGECN];
//     si->l1_pagetable.slot = PAGECN_SLOT_VROOT;

//     struct capref l1_pt_parent;
//     slot_alloc(&l1_pt_parent);
//     vnode_create(l1_pt_parent, ObjType_VNode_ARM_l1);
    
//     err = cap_copy(si->l1_pagetable, l1_pt_parent);
//     if (err_is_fail(err)) {
// 	    // Error
// 	    //
//     }

// //    struct capref l1_ref = {
// //        .cnode = page_table_cn_ref,
// //        .slot = 0,
// //    };
// //    err = vnode_create(l1_ref, s ObjType_VNode_ARM_l1);
//     err = paging_init_state(&si->ps, 0, l1_pt_parent, get_default_slot_allocator());

//     // load elf
//     err = elf_load(EM_ARM, elf_alloc_func, (void *)si, elf_addr, frame.bytes, &(si->entry_addr));
    
//     struct Elf32_Shdr *got = elf32_find_section_header_name(elf_addr, frame.bytes, ".got");
//     si->got = got;

//     // init dispatcher
//     //

//     struct capref endpoint;
//     err = slot_alloc(&si->dispatcher);
//     // check if err fail
//     dispatcher_create(&si->dispatcher);
//     cap_retype(endpoint, &si->dispatcher, 0, ObjType_EndPoint, 0, 1);

//     size_t allocted_amount;
//     struct capref dispatcher_frame;
//     err = frame_alloc(&si->dispatcher_frame, DISPATCHER_SIZE, &allocated_amount);
//     // check if err fail

//     struct capref dispatcher_cnode;
//     dispatcher_cnode.cnode = si->l2_cnodes[ROOTCN_SLOT_TASK];
//     dispatcher_cnode.slot = TASKCN_SLOT_SELFEP;

//     cap_copy(dispatcher_cnode, si->dispatcher);
    
//     dispatcher_cnode.cnode = si->l2_cnode_list[ROOTCN_SLOT_TASKCN];
//     dispatcher_cnode.slot = TASKCN_SLOT_SELFEP;

//     cap_copy(dispatcher_cnode, endpoint);

//     dispatcher_cnode.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
//     dispatcher_cnode.slot = TASKCN_SLOT_DISPFRAME;

//     cap_copy(dispatcher_cnode, dispatcher_frame);

//     err = paging_map_frame(&si->ps, (void *)child_vaddr, DISPATCHER_SIZE, dispatcher_frame, NULL, NULL);
//     // check if err  

//     err = pagin_map_frame(get_current_paging_state(), (void *) parent_vaddr, DISPATCHER_SIZE, dispatcher_frame, NULL, NULL);
   
//     // check if err
//     struct dispatcher_shared_generic *disp = get_dispatcher_shared_generic((dispatcher_handle_t) parent_vaddr);
//     struct dispatcher_generic *disp_gen = get_dispatcher_generic((dispatcher_handle_t) parent_vaddr);
//     struct dispatcher_shared_arm *disp_arm = get_dispatcher_shared_arm((dispatcher_handle_t) parent_vaddr);
//     arch_registers_state_t *enabled_area = dispatcher_get_enabled_save_area((dispatcher_handle_t) parent_vaddr);

//     arch_registers_state_t *disabled_area = dispatcher_get_disabled_save_area((dispatcher_handle_t) parent_vaddr);

//     disp->udisp = child_vaddr;
//     disp->disabled = 1;
//     disp->fpu_trap = 1;
    
//     disp_gen->core_id = 0;
//     disp_gen->eh_frame = 0;	
//     disp_gen->eh_frame_size = 0;
//     disp_gen->eh_frame_hdr = 0;	
//     disp_gen->eh_frame_hdr_size = 0;
    
//     strncpy(disp->name, si->binary_name, DISP_NAME_LEN);

//     disp_arm->got_base = si->got;
//     enabled_area->regs[REG_OFFSET(PIC_REGISTER)] = si->got;
//     disabled_area->regs[REG_OFFSET(PIC_REGISTER)] = si->got;
    
//     enabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;
//     disabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;

//     si->enabled_area = enabled_area;

    // dispatcher done

    // setup env

    // size_t args_frame_size;
    // struct capref args_frame;
    // void *args_vadr;
    // err = frame_alloc(&args_frame, DISPATCHER_SIZE, &args_frame_size);
    // err = paging_map_frame(&si->ps, (void *)child_vaddr, ARGS_SIZE, args_frame, NULL, NULL);
    // err = paging_map_frame(get_current_paging_state(), (void *)parent_vaddr, ARGS_SIZE, args_frame, NULL, NULL);
    // struct capref args_ref = {
    //     .cnode = si->l2_cnode_list[ROOTCN_SLOT_TASKCN],
    //     .slot = TASKCN_SLOT_ARGSPAGE,
    // };
    // cap_copy(args_ref, args_frame);


    //
    // invoke_dispatcher()



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
    errval_t err;

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

    return SYS_ERR_OK;
}

errval_t elf_alloc_func(void *state, genvaddr_t base, size_t size, uint32_t flags, void **ret) {
    errval_t err;
    
    base -= base % BASE_PAGE_SIZE;
    size += size % BASE_PAGE_SIZE;
    struct capref frame_ref;
    size_t returned_bytes;
    err = frame_alloc(&frame_ref, size, &returned_bytes);
    if (err_is_fail(err)) {
        debug_printf("Unable to create frame");
        return err_push(err, LIB_ERR_FRAME_CREATE);
    }
    err = paging_map_fixed_attr(&(((struct spawninfo *)state)->ps), base, frame_ref, size, flags);
    if (err_is_fail(err)) {
        debug_printf("Unable to map frame");
        return err_push(err, LIB_ERR_PMAP_MAP);
    }
    err = paging_map_frame_attr(get_current_paging_state(), ret, size, frame_ref, flags, NULL, NULL);
    if (err_is_fail(err)) {
        debug_printf("Unable to map frame");
        return err_push(err, LIB_ERR_PMAP_MAP);
    }
    return SYS_ERR_OK;
}
