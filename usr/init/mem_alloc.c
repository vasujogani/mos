/**
 * \file
 * \brief Local memory allocator for init till mem_serv is ready to use
 */

#include "mem_alloc.h"
#include <mm/mm.h>
#include <aos/paging.h>

/// MM allocator instance data
struct mm aos_mm;

void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);


static errval_t aos_ram_alloc_aligned(struct capref *ret, size_t size, size_t alignment)
{
    return mm_alloc_aligned(&aos_mm, size, alignment, ret);
}

errval_t aos_ram_free(struct capref cap, size_t bytes)
{
    errval_t err;
    struct frame_identity fi;
    err = frame_identify(cap, &fi);
    if (bytes > fi.bytes) {
        bytes = fi.bytes;
    }
    return mm_free(&aos_mm, cap, fi.base, bytes);
}

/**
 * \brief Setups a local memory allocator for init to use till the memory server
 * is ready to be used.
 */
errval_t initialize_ram_alloc(void)
{
    printf("in initialize_ram_alloc from mem_alloc.c\n");
    errval_t err;

    // Init slot allocator
    static struct slot_prealloc init_slot_alloc;
    struct capref cnode_cap = {
        .cnode = {
            .croot = CPTR_ROOTCN,
            .cnode = ROOTCN_SLOT_ADDR(ROOTCN_SLOT_SLOT_ALLOC0),
            .level = CNODE_TYPE_OTHER,
        },
        .slot = 0,
    };
    err = slot_prealloc_init(&init_slot_alloc, cnode_cap, L2_CNODE_SLOTS, &aos_mm);
    if (err_is_fail(err)) {
        return err_push(err, MM_ERR_SLOT_ALLOC_INIT);
    }

    // Initialize aos_mm
    err = mm_init(&aos_mm, ObjType_RAM, NULL,
                  slot_alloc_prealloc, slot_prealloc_refill,
                  &init_slot_alloc);

    if (err_is_fail(err)) {
        USER_PANIC_ERR(err, "Can't initalize the memory manager.");
    }

    // Give aos_mm a bit of memory for the initialization
    static char nodebuf[sizeof(struct mmnode)*64];
    slab_grow(&aos_mm.slabs, nodebuf, sizeof(nodebuf));

    // Walk bootinfo and add all RAM caps to allocator handed to us by the kernel
    uint64_t mem_avail = 0;
    struct capref mem_cap = {
        .cnode = cnode_super,
        .slot = 0,
    };


    for (int i = 0; i < bi->regions_length; i++) {
        if (bi->regions[i].mr_type == RegionType_Empty) {
            err = mm_add(&aos_mm, mem_cap, bi->regions[i].mr_base, bi->regions[i].mr_bytes);
            if (err_is_ok(err)) {
                mem_avail += bi->regions[i].mr_bytes;
            } else {
                DEBUG_ERR(err, "Warning: adding RAM region %d (%p/%zu) FAILED", i, bi->regions[i].mr_base, bi->regions[i].mr_bytes);
            }

            err = slot_prealloc_refill(aos_mm.slot_alloc_inst);
            if (err_is_fail(err) && err_no(err) != MM_ERR_SLOT_MM_ALLOC) {
                DEBUG_ERR(err, "in slot_prealloc_refill() while initialising"
                        " memory allocator");
                abort();
            }

            mem_cap.slot++;
        }
    }
    debug_printf("Added %"PRIu64" MB of physical memory.\n", mem_avail / 1024 / 1024);

    // Finally, we can initialize the generic RAM allocator to use our local allocator
    err = ram_alloc_set(aos_ram_alloc_aligned);
    if (err_is_fail(err)) {
        return err_push(err, LIB_ERR_RAM_ALLOC_SET);
    }

    // test1();
    // test2();
    // test3();
    // test4();
    // test5();

    return SYS_ERR_OK;
}

void test1(void) {
    // test1 large alloc
    debug_printf("****Start Test 1 ====== allocating 3000 times\n");
    errval_t err;
    int i;
    for (i=0; i < 3000; i++) {
        printf("On iteration %i\n", i);
        struct capref cr;
        err = mm_alloc(&aos_mm, BASE_PAGE_SIZE * 500, &cr);
    }
    mm_print(&aos_mm);
    debug_printf("****Done with Test 1\n");
}

void test2(void) {
    // test2 alloc + free
    debug_printf("****Start Test 2 ====== allocating and freeing 50,000 times\n");
    errval_t err;
    int i;
    for (i=0; i < 50000; i++) {
        printf("On iteration %i\n", i);
        struct capref cr;
        err = mm_alloc_aligned(&aos_mm, BASE_PAGE_SIZE, BASE_PAGE_SIZE * 16, &cr);
        assert(err_is_ok(err));

        struct frame_identity f;
        err = frame_identify(cr, &f);
        assert(err_is_ok(err));

        err = mm_free(&aos_mm, cr, f.base, f.bytes);
        assert(err_is_ok(err));
    }
    mm_print(&aos_mm);
    debug_printf("****Done with Test 2\n");
}

void test3(void) {
    // test3 free coalesce
    //allocate 4
    debug_printf("****Start Test 3 ====== Allocate 4 times, and remove middle to test coalesce\n");
    errval_t err;
    struct capref retcap1;
    err = mm_alloc(&aos_mm, BASE_PAGE_SIZE, &retcap1);
    assert(err_is_ok(err));

    struct capref retcap2;
    err = mm_alloc(&aos_mm, BASE_PAGE_SIZE, &retcap2);
    assert(err_is_ok(err));

    struct capref retcap3;
    err = mm_alloc(&aos_mm, BASE_PAGE_SIZE, &retcap3);
    assert(err_is_ok(err));

    struct capref retcap4;
    err = mm_alloc(&aos_mm, BASE_PAGE_SIZE, &retcap4);
    assert(err_is_ok(err));

    mm_print(&aos_mm);

    //free middle 2
    struct frame_identity f2;
    err = frame_identify(retcap2, &f2);
    assert(err_is_ok(err));
    err = mm_free(&aos_mm, retcap2, f2.base, f2.bytes);
    assert(err_is_ok(err));

    struct frame_identity f3;
    err = frame_identify(retcap3, &f3);
    assert(err_is_ok(err));
    err = mm_free(&aos_mm, retcap3, f3.base, f3.bytes);
    assert(err_is_ok(err));

    mm_print(&aos_mm);

    //allocate a big one
    struct capref retcap5;
    err = mm_alloc(&aos_mm, BASE_PAGE_SIZE * 2, &retcap5);
    assert(err_is_ok(err));

    mm_print(&aos_mm);

    struct frame_identity f1;
    err = frame_identify(retcap1, &f1);
    assert(err_is_ok(err));

    struct frame_identity f5;
    err = frame_identify(retcap5, &f5);
    assert(err_is_ok(err));

    assert(f1.base + f1.bytes == f5.base);    
    debug_printf("****Done with Test 3\n");
}

void test4(void) {
    // test4 alloc + free
    debug_printf("****Start Test 4 ====== allocating 5 times\n");
    errval_t err;
    int i;
    mm_print(&aos_mm);
    for (i=0; i < 5; i++) {
        printf("On iteration %i\n", i);
        struct capref cr;
        if (i % 2 == 0) {
            err = mm_alloc_aligned(&aos_mm, BASE_PAGE_SIZE, BASE_PAGE_SIZE * 16, &cr);
            assert(err_is_ok(err));
        } else {
            err = mm_alloc_aligned(&aos_mm, BASE_PAGE_SIZE, BASE_PAGE_SIZE, &cr);
            assert(err_is_ok(err));
        }

        mm_print(&aos_mm);

        // struct frame_identity f;
        // err = frame_identify(cr, &f);
        // assert(err_is_ok(err));

        // err = mm_free(&aos_mm, cr, f.base, f.bytes);
        // assert(err_is_ok(err));
    }
    debug_printf("****Done with Test 4\n");
}

void test5(void) {
    // test4 alloc + free
    debug_printf("****Start Test 5 ====== larger frame allocation\n");
    errval_t err;
    for (int i = 0; i < 260; i++) {
        void *buf;
        struct capref frame_ref;
        size_t returned_bytes;
        err = frame_alloc(&frame_ref, BASE_PAGE_SIZE * 260, &returned_bytes);
        printf("alloc done\n");
        err = paging_map_frame(get_current_paging_state(), (void *)&buf,
                                returned_bytes, frame_ref,
                                    NULL, NULL);
        char *start = (char *)buf;
        *(start + (BASE_PAGE_SIZE * i)) = 'B';
        printf("On iteration %i, value of address is %c\n", i, *(start + (BASE_PAGE_SIZE * i)));    
    }
    debug_printf("****Done with Test 5\n");
}