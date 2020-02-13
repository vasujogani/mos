
void test_refill (struct mm *mm) {

    struct capref *retcaps[600];
    for (int i = 0; i < 600; ++i)
    {
        err = mm_alloc(mm, BASE_PAGE_SIZE, retcaps[i]);
        assert(err_is_ok(err));
    }

    for (int i = 0; i < 600; ++i)
    {
        struct frame_identity f;
        err = frame_identify(retcaps[i], &f);
        assert(err_is_ok(err));
        err = mm_free(mm, retcaps[i], f.base, f.bytes);
        assert(err_is_ok(err));
    }

    mm_print(mm);
}

void test_free_coalesce (struct mm *mm) {

    printf("START OF test_free_coalesce\n");

    //allocate 4
    errval_t err;
    struct capref *retcap1;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap1);
    assert(err_is_ok(err));

    struct capref *retcap2;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap2);
    assert(err_is_ok(err));

    struct capref *retcap3;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap3);
    assert(err_is_ok(err));

    struct capref *retcap4;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap4);
    assert(err_is_ok(err));

    //free middle 2
    struct frame_identity f2;
    err = frame_identify(retcap2, &f2);
    assert(err_is_ok(err));
    err = mm_free(mm, retcap2, f2.base, f2.bytes);
    assert(err_is_ok(err));

    struct frame_identity f3;
    err = frame_identify(retcap3, &f3);
    assert(err_is_ok(err));
    err = mm_free(mm, retcap3, f3.base, f3.bytes);
    assert(err_is_ok(err));

    //allocate a big one
    struct capref *retcap5;
    err = mm_alloc(mm, BASE_PAGE_SIZE * 2, retcap5);
    assert(err_is_ok(err));

    mm_print(mm);

    struct frame_identity f1;
    err = frame_identify(retcap1, &f1);
    assert(err_is_ok(err));

    struct frame_identity f5;
    err = frame_identify(retcap5, &f5);
    assert(err_is_ok(err));

    assert(f1.base + f1.bytes == f5.base);

    printf("END OF test_free_coalesce\n");
}

void test_big_alignment (struct mm *mm) {
    errval_t err;
    struct capref *retcap1;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap1);
    assert(err_is_ok(err));

    struct capref *retcap2;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap2);
    assert(err_is_ok(err));

    struct capref *retcap3;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap3);
    assert(err_is_ok(err));

    struct capref *retcap4;
    err = mm_alloc(mm, BASE_PAGE_SIZE, retcap4);
    assert(err_is_ok(err));

    mm_free(mm, retcap2, base, size);
    mm_free(mm, retcap3, base, size);

    struct capref *retcap5;
    err = mm_alloc(mm, BASE_PAGE_SIZE * 2, retcap5);
    assert(err_is_ok(err));

    mm_print(mm);
}