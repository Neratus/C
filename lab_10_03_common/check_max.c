#include "check_max.h"
#include "associative_array.h"
#include "test_pair.h"

START_TEST(test_max_one_pair)
{
    test_pair_t tests[] =
    {
        {"Hello", 1}
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
    rc = assoc_array_max(arr, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*tmp, 1);

    assoc_array_destroy(&arr);
}  
END_TEST

START_TEST(test_max_several_pairs)
{
    test_pair_t tests[] =
    {
        {"Hello", 1},
        {"I didnt see you there!", 2},
        {"How are you?", 3},
        {"I hope your day goes as good as mine", 4},
        {"Just dont forget to have a good sleep!", 5}
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
    rc = assoc_array_max(arr, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*tmp, 5);

    assoc_array_destroy(&arr);
}  
END_TEST

START_TEST(test_max_null)
{
    assoc_array_error_t rc;

    assoc_array_t arr= NULL;

    int *tmp;
    rc = assoc_array_max(arr, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}  
END_TEST

Suite* max_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("max");
    
    tc_pos = tcase_create("pos");
    tcase_add_test(tc_pos, test_max_one_pair);
    tcase_add_test(tc_pos, test_max_several_pairs);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("neg");
    tcase_add_test(tc_neg, test_max_null);

    suite_add_tcase(s, tc_neg);

    return s;
}
