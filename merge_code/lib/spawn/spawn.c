#include <aos/aos.h>
#include <spawn/spawn.h>
<<<<<<< HEAD

=======
>>>>>>> week5
#include <elf/elf.h>
#include <aos/dispatcher_arch.h>
#include <barrelfish_kpi/paging_arm_v7.h>
#include <barrelfish_kpi/domain_params.h>
#include <spawn/multiboot.h>
<<<<<<< HEAD

extern struct bootinfo *bi;

// TODO(M2): Implement this function such that it starts a new process
// TODO(M4): Build and pass a messaging channel to your child process
errval_t spawn_load_by_name(void * binary_name, struct spawninfo * si) {
    printf("spawn start_child: starting: %s\n", binary_name);

    errval_t err;

    // Init spawninfo
    memset(si, 0, sizeof(*si));
    si->binary_name = binary_name;

    // TODO: Implement me
    // - Get the binary from multiboot image
    // - Map multiboot module in your address space
    // - Setup childs cspace
    // - Setup childs vspace
    // - Load the ELF binary
    // - Setup dispatcher
    // - Setup environment
    // - Make dispatcher runnable

=======
 
extern struct bootinfo *bi;
 
static errval_t elf_alloc_sect_func(void *si, genvaddr_t base, size_t size,
                                    uint32_t flags, void **ret)
{
    errval_t err;
    size_t off = BASE_PAGE_OFFSET(base);
    struct capref frame;
    size_t alloc_size;
    base -= off;
    size = ROUND_UP(size + off, BASE_PAGE_SIZE);

    err = frame_alloc(&frame, size, &alloc_size);
    err = paging_map_fixed_attr(&((struct spawninfo *)si)->ps, base, frame, alloc_size, flags);
    err = paging_map_frame(get_current_paging_state(), ret, alloc_size, frame, NULL, NULL);
 
    *ret += off;
    return SYS_ERR_OK;
}

 
// TODO(M4): Build and pass a messaging channel to your child process
errval_t spawn_load_by_name(void * binary_name, struct spawninfo * si)
{
    errval_t err;
    memset(si, 0, sizeof(*si));
    si->binary_name = binary_name;
 
    struct mem_region *module = multiboot_find_module(bi, binary_name);
    if (module == NULL) {
        return SPAWN_ERR_FIND_MODULE;
    }
 
    struct capref child_frame = {
        .cnode = cnode_module,
        .slot = module->mrmod_slot
    };
 
    struct frame_identity frame_id;
    err = frame_identify(child_frame, &frame_id);
 
    lvaddr_t elf_addr;
    err = paging_map_frame(get_current_paging_state(), (void **)&elf_addr, frame_id.bytes, child_frame, NULL, NULL);

    char *binary_start = (char *)elf_addr;
    // printf("%c %c %c %c\n", *binary_start, *(binary_start + 1), *(binary_start + 2), *(binary_start + 3));
    
    assert(*binary_start == 0x7f);
    assert(*(binary_start + 1) == 'E');
    assert(*(binary_start + 2) == 'L');
    assert(*(binary_start + 3) == 'F');

 
    // cspace
    struct cnoderef l1_cnode;
    err = cnode_create_l1(&si->l1_cnode, &l1_cnode);
    assert(err_is_ok(err));

    // Go over all root-CNode slots
    for (int i = 0; i <= ROOTCN_SLOTS_USER; i++) {
        err = cnode_create_foreign_l2(si->l1_cnode, i, &si->l2_cnodes[i]);
        assert(err_is_ok(err));
    }
 
    struct capref task_slot = {
        .cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN],
        .slot = TASKCN_SLOT_ROOTCN
    };
    err = cap_copy(task_slot, si->l1_cnode);
    assert(err_is_ok(err));
 
    struct capref base_page_slot = {
        .cnode = si->l2_cnodes[ROOTCN_SLOT_BASE_PAGE_CN],
        .slot = 0
    };
    int i;
    for (i = 0; i < L2_CNODE_SLOTS; i++) {
        struct capref temp;
 
        err = ram_alloc(&temp, BASE_PAGE_SIZE);
        err = cap_copy(base_page_slot, temp);
        err = cap_destroy(temp);
        base_page_slot.slot = i+1;
    }
 
    // vspace
    struct capref l1_pt;
    err = slot_alloc(&l1_pt);
    err = vnode_create(l1_pt, ObjType_VNode_ARM_l1);
 
    si->l1_pt.cnode = si->l2_cnodes[ROOTCN_SLOT_PAGECN];
    si->l1_pt.slot  = PAGECN_SLOT_VROOT;
 
    err = cap_copy(si->l1_pt, l1_pt);
    err = paging_init_state(&si->ps, (1<<25), l1_pt, get_default_slot_allocator());
 
 
    err = elf_load(EM_ARM, elf_alloc_sect_func, (void *)si, elf_addr, frame_id.bytes, &si->entry_addr);
 
    struct Elf32_Shdr *global_offset_table = elf32_find_section_header_name(elf_addr, frame_id.bytes, ".got");
    si->got = global_offset_table->sh_addr;
 
 
    struct capref dispatch;
    struct capref temp;
    struct capref dis_frame;
    size_t retsize;
    void* parent_addr;
    void* child_addr;

    err = slot_alloc(&si->dispatcher); 
    err = dispatcher_create(si->dispatcher);
 

    err = slot_alloc(&dispatch);
    err = cap_retype(dispatch, si->dispatcher, 0, ObjType_EndPoint, 0, 1);
    err = frame_alloc(&dis_frame, DISPATCHER_SIZE, &retsize);
 
    temp.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    temp.slot = TASKCN_SLOT_DISPATCHER;
    err = cap_copy(temp, si->dispatcher);
 
    temp.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    temp.slot = TASKCN_SLOT_SELFEP;
    err = cap_copy(temp, dispatch);

    // copy init endpoint from parent to child
    temp.slot = TASKCN_SLOT_INITEP;
    err = cap_copy(temp, cap_initep);
 
    si->dis_frame.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    si->dis_frame.slot = TASKCN_SLOT_DISPFRAME;
    err = cap_copy(si->dis_frame, dis_frame);
 
    err = paging_map_frame(get_current_paging_state(), &parent_addr, DISPATCHER_SIZE, dis_frame, NULL, NULL);
    err = paging_map_frame(&si->ps, &child_addr, DISPATCHER_SIZE,dis_frame, NULL, NULL);
 
    struct dispatcher_shared_generic *disp = get_dispatcher_shared_generic((dispatcher_handle_t)parent_addr);
    struct dispatcher_generic *disp_gen = get_dispatcher_generic((dispatcher_handle_t)parent_addr);
    struct dispatcher_shared_arm *disp_arm = get_dispatcher_shared_arm((dispatcher_handle_t)parent_addr);
    
    disp_gen->core_id = 0;
    disp->disabled = 1;
    disp->fpu_trap = 1;
    disp->udisp = (lvaddr_t) child_addr;
    strncpy(disp->name, si->binary_name, DISP_NAME_LEN);

    disp_gen->eh_frame = 0;
    disp_gen->eh_frame_size = 0;
    disp_gen->eh_frame_hdr = 0;
    disp_gen->eh_frame_hdr_size = 0;
    disp_arm->got_base = si->got;
 
 
    arch_registers_state_t *enabled_area = dispatcher_get_enabled_save_area((dispatcher_handle_t)parent_addr);
    arch_registers_state_t *disabled_area = dispatcher_get_disabled_save_area((dispatcher_handle_t)parent_addr);
    enabled_area->regs[REG_OFFSET(PIC_REGISTER)] = si->got;
    disabled_area->regs[REG_OFFSET(PIC_REGISTER)] = si->got;
    disabled_area->named.pc = si->entry_addr;
    enabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;
    disabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;
 
 
    // args
    const char *args = multiboot_module_opts(module);
    size_t arg_size = ROUND_UP(sizeof(struct spawn_domain_params) + strlen(args) + 1, BASE_PAGE_SIZE);
    struct capref arg_framee;
    // struct capref temp;
    size_t alloc_size;
    void* args_addr;
    void* child_arg_addr;

    err = frame_alloc(&arg_framee, arg_size, &alloc_size);
    err = paging_map_frame(get_current_paging_state(), &args_addr, alloc_size, arg_framee, NULL, NULL);
 
    temp.cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN];
    temp.slot = TASKCN_SLOT_ARGSPAGE;
    err = cap_copy(temp, arg_framee);
 
    err = paging_map_frame(&si->ps, &child_arg_addr, alloc_size, arg_framee, NULL, NULL);
 
    struct spawn_domain_params *params = (struct spawn_domain_params *)args_addr;
 
    char *bp = (char *) params + sizeof(struct spawn_domain_params);
    lvaddr_t base_p = (lvaddr_t) child_arg_addr + sizeof(struct spawn_domain_params);
    strcpy(bp, args);
 
    char *it = bp;
    char *param_last = bp;
    while (*it != 0) {
        if (*it == ' ') {
            params->argv[params->argc] = (void *)base_p + (param_last - bp);
            *it = 0;
            it += 1; 
            param_last = it;
            params->argc += 1;
        }
        it += 1;
    }
    params->argv[params->argc++] = (void *)base_p + (param_last - bp);
    enabled_area->named.r0 = (uint32_t) child_arg_addr;
 
    params->vspace_buf = NULL;
    params->vspace_buf_len = 0;
    params->tls_init_base = NULL;
    params->tls_init_len = 0;
    params->tls_total_len = 0;
    params->pagesize = 0;

    err = invoke_dispatcher(si->dispatcher, cap_dispatcher, si->l1_cnode, si->l1_pt, si->dis_frame, true);
    
    assert(err_is_ok(err));
>>>>>>> week5
    return SYS_ERR_OK;
}
