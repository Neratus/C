#include "check_each.h"
#include "associative_array.h"
#include "test_pair.h"

void mult_by_two(const char *key, int *num, void *param)
{
    (void) key;
    (void) param;
    *num *= 2;
}

void mult_by_param(const char *key, int *num, void *param)
{
    (void) key;
    int *x = param;
    *num *= *x;
}

void do_nothing(const char *key, int *num, void *param)
{
    (void) key;
    (void) param;
    (void) num;
}

START_TEST(test_each_mult_by_two)
{
    test_pair_t tests[] =
    {
        {"Hello", 1},
        {"It is supposed to be this way", 2},
        {"But it it isnt over", 3},
        {"Are you litering?", 4},
        {"Dont be late!", 5},
    };
    int exp[] = {2, 4, 6, 8, 10};
    size_t cnt = sizeof(tests) / sizeof(test_pair_t);
    assoc_array_error_t rc;

    assoc_array_t arr= assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < cnt; i++)
    {
        rc = assoc_array_insert(arr, tests[i].key, tests[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }
    rc = assoc_array_each(arr, mult_by_two, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    for (size_t i = 0; i < cnt; ++i)
    {
        rc = assoc_array_find(arr, tests[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*tmp, exp[i]);
    }

    assoc_array_destroy(&arr);
}  
END_TEST

START_TEST(test_each_mult_by_param)
{
    test_pair_t tests[] =
    {
        {"Hello", 1},
        {"It is supposed to be this way", 2},
        {"But it it isnt over", 3},
        {"Are you litering?", 4},
        {"Dont be late!", 5},
    };
    int exp[] = {3, 6, 9, 12, 15};
    size_t cnt = sizeof(tests) / sizeof(test_pair_t);
    assoc_array_error_t rc;

    assoc_array_t arr= assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < cnt; i++)
    {
        rc = assoc_array_insert(arr, tests[i].key, tests[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }

    int x = 3;
    rc = assoc_array_each(arr, mult_by_param, &x);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    for (size_t i = 0; i < cnt; ++i)
    {
        rc = assoc_array_find(arr, tests[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*tmp, exp[i]);
    }

    assoc_array_destroy(&arr);
}  
END_TEST


START_TEST(test_each_do_nothing)
{
    test_pair_t tests[] =
    {
        {"Hello", 1},
        {"It is supposed to be this way", 2},
        {"But it it isnt over", 3},
        {"Are you litering?", 4},
        {"Dont be late!", 5},
    };
    int exp[] = {1, 2, 3, 4, 5};
    size_t cnt = sizeof(tests) / sizeof(test_pair_t);
    assoc_array_error_t rc;

    assoc_array_t arr= assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    for (size_t i = 0; i < cnt; i++)
    {
        rc = assoc_array_insert(arr, tests[i].key, tests[i].val);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }
    rc = assoc_array_each(arr, do_nothing, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *tmp;
    for (size_t i = 0; i < cnt; ++i)
    {
        rc = assoc_array_find(arr, tests[i].key, &tmp);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*tmp, exp[i]);
    }

    assoc_array_destroy(&arr);
}  
END_TEST


Suite* each_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("each");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_each_mult_by_two);
    tcase_add_test(tc_pos, test_each_mult_by_param);
    tcase_add_test(tc_pos, test_each_do_nothing);

    suite_add_tcase(s, tc_pos);

    return s;
}
