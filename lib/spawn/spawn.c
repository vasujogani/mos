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

    // don't know if we need this yet
    struct capref child_frame = {
        .cnode = cnode_module,
        .slot = mem_regioin−>mrmod_slot,
    };

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

    // create TASKCN L2 Cnode and add appropriate capabilities
    struct cnoderef taskcn_ref;
    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_TASKCN, taskcn_ref);
    if (err_is_fail(err)) {
        debug_printf("Unable to create initial L1 CNode\n");
        return err_push(err, LIB_ERR_CNODE_CREATE);
    }
    struct capref dispatcher_ref = {
        .cnode = taskcn_ref,
        .slot = TASKCN_SLOT_DISPATCHER,
    };
    // capability for dispatcher
    err = dispatcher_create(dispatcher_ref);
    if (err_is_fail(err)) {
        debug_printf("Unable to create dispatcher capref\n");
        return err;
    }
    // capability for endpoint
    struct capref endpoint_ref = {
        .cnode = taskcn_ref,
        .slot = TASKCN_SLOT_SELFEP,
    };
    err = cap_retype(endpoint_ref, dispatcher_ref, 0,
                    ObjType_EndPoint, OBJSIZE_DISPATCHER, 1);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
    }
    // copy L1 root capability
    struct capref root_ref = {
        .cnode = taskcn_ref,
        .slot = TASKCN_SLOT_ROOTCN,
    };
    err = cap_copy(root_ref, l1_cnode);
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
    for (int i=0; i<L2_CNODE_SLOTS; i++) {
        struct capref ram_ref = {
            .cnode = base_page_cn_ref,
            .slot = i,
        };
        err = mm_alloc(&aos_mm, BASE_PAGE_SIZE, &ram_ref);
        if (err_is_fail(err)) {
            return err_push(err, LIB_ERR_CNODE_CREATE_FROM_MEM);
        }
    }
    
    err = cnode_create_foreign_l2(l1_cnode, ROOTCN_SLOT_PAGECN, NULL);


    // TODO: Implement me
    // - Map multiboot module in your address space
    // - Setup childs vspace
    // - Load the ELF binary
    // - Setup dispatcher
    // - Setup environment
    // - Make dispatcher runnable

    return SYS_ERR_OK;
}
