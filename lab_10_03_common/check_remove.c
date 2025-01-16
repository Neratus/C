#include "check_remove.h"
#include "associative_array.h"
#include "test_pair.h"

START_TEST(test_remove_exists)
{
    test_pair_t tests[] =
    {
        {"Hello", 1},
        {"It is supposed to be this way", 2},
        {"But it it isnt over", 3},
        {"Are you litering?", 4},
        {"Dont be late!", 5},
    };
    size_t cnt = sizeof(tests) / sizeof(test_pair_t);
    assoc_array_error_t rc;

    assoc_array_t arr= assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < cnt; i++)
    {
        rc = assoc_array_insert(arr, tests[i].key, tests[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }
    int *tmp;
    rc = assoc_array_remove(arr,"Hello");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(arr, "Hello", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}  
END_TEST

START_TEST(test_remove_empty)
{
    test_pair_t tests[] =
    {
        {"Hello", 1},
        {"It is supposed to be this way", 2},
        {"But it it isnt over", 3},
        {"Are you litering?", 4},
        {"Dont be late!", 5},
    };
    size_t cnt = sizeof(tests) / sizeof(test_pair_t);
    assoc_array_error_t rc;

    assoc_array_t arr= assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < cnt; i++)
    {
        rc = assoc_array_insert(arr, tests[i].key, tests[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }
    rc = assoc_array_remove(arr,"");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}  
END_TEST

START_TEST(test_remove_doesnt_exist)
{
    test_pair_t tests[] =
    {
        {"Hello", 1},
        {"It is supposed to be this way", 2},
        {"But it it isnt over", 3},
        {"Are you litering?", 4},
        {"Dont be late!", 5},
    };
    size_t cnt = sizeof(tests) / sizeof(test_pair_t);
    assoc_array_error_t rc;

    assoc_array_t arr= assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < cnt; i++)
    {
        rc = assoc_array_insert(arr, tests[i].key, tests[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }
    rc = assoc_array_remove(arr,"Bye");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}  
END_TEST

Suite* remove_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("remove");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_remove_exists);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_remove_empty);
    tcase_add_test(tc_neg, test_remove_doesnt_exist);

    suite_add_tcase(s, tc_neg);

    return s;
}
