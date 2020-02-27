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
    printf("*spawn start_child: starting: %s\n", binary_name);

   errval_t err;

    // Init spawninfo
    memset(si, 0, sizeof(*si));
    si->binary_name = binary_name;
    // - Get the binary from multiboot image
    struct mem_region *mem_region = multiboot_find_module(bi, (const char *)binary_name);
    struct capref child_frame_cap = {
        .cnode = cnode_module,
        .slot = mem_region->mrmod_slot,
    };
    // map child_frame into new process virtual address space
    struct frame_identity frame;
    frame_identify(child_frame_cap, &frame);
    lvaddr_t elf_addr;
    err = paging_map_frame(get_current_paging_state(), (void *)&elf_addr, frame.bytes, child_frame_cap, NULL, NULL);
    printf("*********************************MADE IT THIS FAR %s\n", err_getstring(err));
    // verify
    char *binary_start = (char *)elf_addr;
    assert(*binary_start == 0x7f);
    assert(*(binary_start + 1) == 'E');
    assert(*(binary_start + 2) == 'L');
    assert(*(binary_start + 3) == 'F');


    // - Setup childs cspace
    struct cnoderef l1_cnode_ref;
    err = cnode_create_l1(&si->l1_cnode, &l1_cnode_ref);
    if (err_is_fail(err)) {
        debug_printf("Unable to create initial L1 CNode\n");
        return err_push(err, LIB_ERR_CNODE_CREATE);
    }

    for (int i = 0; i < ROOTCN_FREE_SLOTS; i++) {
        err = cnode_create_foreign_l2(si->l1_cnode, i, &si->l2_cnodes[i]);
        if (err_is_fail(err)) {
            debug_printf("Unable to create L2 CNode\n");
            return err_push(err, LIB_ERR_CNODE_CREATE);
        }
    } 

    // copy L1 root capability
    struct capref curr_ref;
    curr_ref.slot = TASKCN_SLOT_ROOTCN;
    curr_ref.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    err = cap_copy(curr_ref, si->l1_cnode);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
    }
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@HERE1\n");


    //SLOT_DISPFRAME: See the next section for an explanation of this.
    //SLOT_ARGSPG: A page containing a list of command line arguments.

    //allocate memory for process
//    struct cnoderef base_page_cn_ref;
//    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_BASE_PAGE_CN, base_page_cn_ref);
    struct capref ram_ref = {
            .cnode = si->l2_cnodes[ROOTCN_SLOT_BASE_PAGE_CN],
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

        ram_ref.slot = i+1;
        cap_destroy(temp_cap);

    }
        printf("errrrrrrrrrrrrrrrrrrrrrrrrrr: \n");


    
    // vspace
//    struct cnoderef page_table_cn_ref;
//    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_PAGECN, page_table_cn_ref);
//  create a new l1 pt in the current vspace and copy it to the child's since child does not have vspace for pt
    
    si->l1_pagetable.cnode = si->l2_cnodes[ROOTCN_SLOT_PAGECN];
    si->l1_pagetable.slot = PAGECN_SLOT_VROOT;

    struct capref l1_pt_parent;
    slot_alloc(&l1_pt_parent);
    vnode_create(l1_pt_parent, ObjType_VNode_ARM_l1);
    err = cap_copy(si->l1_pagetable, l1_pt_parent);
    if (err_is_fail(err)) {
	    // Error
	    //
        printf("errrrrrrrrrrrrrrrrrrrrrrrrrr: %s\n", err_getstring(err));
    }

//    struct capref l1_ref = {
//        .cnode = page_table_cn_ref,
//        .slot = 0,
//    };
//    err = vnode_create(l1_ref, s ObjType_VNode_ARM_l1);
printf("***************%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%******************\n");
    err = paging_init_state(&si->ps, (1 << 25), l1_pt_parent, get_default_slot_allocator());
    // err = paging_init(&si->ps);

    // load elf
    err = elf_load(EM_ARM, elf_alloc_func, (void *)si, elf_addr, frame.bytes, &(si->entry_addr));
    printf("******************************** %x, %x*\n", elf_addr, frame.bytes);
    printf("%s\n", err_getstring(err));
    
    struct Elf32_Shdr *got = elf32_find_section_header_name(elf_addr, frame.bytes, ".got");
    si->got = got->sh_addr;
        printf("*[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[********************************\n");

    // init dispatcher
    //
    printf("\n\n\n\n\n\n&^*&*^(*&^&*(^*(&Z\n");
    struct capref endpoint;
    err = slot_alloc(&endpoint);
    err = slot_alloc(&si->dispatcher);
    // check if err fail
    dispatcher_create(si->dispatcher);
    printf("A\n");
    err = cap_retype(endpoint, si->dispatcher, 0, ObjType_EndPoint, 0, 1);
    printf("%s\n", err_getstring(err));
    size_t allocated_amount;
    struct capref dispatcher_frame;
    err = frame_alloc(&dispatcher_frame, DISPATCHER_SIZE, &allocated_amount);
    // check if err fail

    printf("Allocated amoutn %zx\n", allocated_amount);

    struct capref dispatcher_cnode;
    dispatcher_cnode.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    dispatcher_cnode.slot = TASKCN_SLOT_SELFEP;

    cap_copy(dispatcher_cnode, si->dispatcher);
    
    dispatcher_cnode.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    dispatcher_cnode.slot = TASKCN_SLOT_SELFEP;

    cap_copy(dispatcher_cnode, endpoint);

    dispatcher_cnode.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    dispatcher_cnode.slot = TASKCN_SLOT_DISPFRAME;

    cap_copy(dispatcher_cnode, dispatcher_frame);

    void *child_vaddr;
    void *parent_vaddr;
     err = paging_map_frame(get_current_paging_state(), &parent_vaddr, DISPATCHER_SIZE, dispatcher_frame, NULL, NULL);
    err = paging_map_frame(&si->ps, &child_vaddr, DISPATCHER_SIZE, dispatcher_frame, NULL, NULL);
    // check if err  

   
   
    // check if err
    struct dispatcher_shared_generic *disp = get_dispatcher_shared_generic((dispatcher_handle_t) parent_vaddr);
    struct dispatcher_generic *disp_gen = get_dispatcher_generic((dispatcher_handle_t) parent_vaddr);
    struct dispatcher_shared_arm *disp_arm = get_dispatcher_shared_arm((dispatcher_handle_t) parent_vaddr);
    arch_registers_state_t *enabled_area = dispatcher_get_enabled_save_area((dispatcher_handle_t) parent_vaddr);

    arch_registers_state_t *disabled_area = dispatcher_get_disabled_save_area((dispatcher_handle_t) parent_vaddr);

    disp->udisp = (lvaddr_t)child_vaddr;
    disp->disabled = 1;
    disp->fpu_trap = 1;
    
    disp_gen->core_id = 0;
    disp_gen->eh_frame = 0;	
    disp_gen->eh_frame_size = 0;
    disp_gen->eh_frame_hdr = 0;	
    disp_gen->eh_frame_hdr_size = 0;
    
    strncpy(disp->name, si->binary_name, DISP_NAME_LEN);

    disp_arm->got_base = si->got;
    enabled_area->regs[REG_OFFSET(PIC_REGISTER)] = si->got;
    disabled_area->regs[REG_OFFSET(PIC_REGISTER)] = si->got;
    
    enabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;
    disabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;

    si->enabled_area = enabled_area;



    // dispatcher done

    const char* args = multiboot_module_opts(mem_region);
    size_t region_size = ROUND_UP(sizeof(struct spawn_domain_params) + strlen(args) + 1, BASE_PAGE_SIZE);
    struct capref mem_frame;
    struct capref args_cap = {
	    .cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN],
	    .slot = TASKCN_SLOT_ARGSPAGE
    };
    void* args_addr;
    size_t framesize;
    frame_alloc(&mem_frame, region_size, &framesize);
    paging_map_frame(get_current_paging_state(), &args_addr, framesize, mem_frame, NULL, NULL);

    cap_copy(args_cap, mem_frame);
    paging_map_frame(&si->ps, &args_addr, framesize, mem_frame, NULL, NULL); 

    struct spawn_domain_params* params = (struct spawn_domain_params*) args_addr;
    // memset(&params->argv[0], 0, sizeof(params->argv));
    // memset(&params->envp[0], 0, sizeof(params->envp));

    char *pb = sizeof(struct spawn_domain_params) + (char *)params;
    lvaddr_t spb = (lvaddr_t)args_addr + sizeof(struct spawn_domain_params); 
    strcpy(pb, args);
    
    size_t n = 0;
    char* it = pb;
    char *temp_pb = pb;
    while (*it) {
	    if (*it == ' ') {
		params->argv[n] = (void*) spb + (temp_pb - pb);
                *it = 0;
		n += 1;
		it += 1;
            	temp_pb = it;	
	    }
	    it += 1;
    }

    params->argv[n] = (void *) spb + (temp_pb - pb);
    params->argc = ++n;
    si->enabled_area->named.r0 = (uint32_t) args_addr;

    // set the rest to 0

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
    size_t off = BASE_PAGE_OFFSET(base);
    base -= off;
    size = ROUND_UP(off + size, BASE_PAGE_SIZE);
    struct capref frame_ref;
    size_t returned_bytes;
    err = frame_alloc(&frame_ref, size, &returned_bytes);
    if (err_is_fail(err)) {
        debug_printf("Unable to create frame");
        return err_push(err, LIB_ERR_FRAME_CREATE);
    }
    printf("For child %"PRIxGENVADDR"\n", base);
    err = paging_map_fixed_attr(&(((struct spawninfo *)state)->ps), base, frame_ref, returned_bytes, flags);
    if (err_is_fail(err)) {
        debug_printf("Unable to map frame");
	printf("this one\n");
        return err_push(err, LIB_ERR_PMAP_MAP);
    }

    printf("For parent\n");
    err = paging_map_frame(get_current_paging_state(), ret, returned_bytes, frame_ref, NULL, NULL);
    if (err_is_fail(err)) {
        debug_printf("Unable to map frame");
	printf("that one\n");
        printf("err is %s\n", err_getstring(err));
        return err_push(err, LIB_ERR_PMAP_MAP);
    }
    printf("done with parent\n");
    *ret += off;
    return SYS_ERR_OK;
}
