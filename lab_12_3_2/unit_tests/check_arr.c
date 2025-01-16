#include "check_arr.h"
#include "arr.h"

START_TEST(test_is_prime_prime)
{
    int num = 23;
    int rc = is_prime(num);
    ck_assert_int_eq(rc, IS_PRIME);
}

START_TEST(test_is_prime_simple)
{
    int num = 4;
    int rc = is_prime(num);
    ck_assert_int_eq(rc, IS_COMPL);
}

START_TEST(test_is_prime_sqrt)
{
    int num = 49;
    int rc = is_prime(num);
    ck_assert_int_eq(rc, IS_COMPL);
}

START_TEST(test_is_prime_zero)
{
    int num = 0;
    int rc = is_prime(num);
    ck_assert_int_eq(rc, IS_COMPL);
}

START_TEST(test_is_prime_neg)
{
    int num = -1;
    int rc = is_prime(num);
    ck_assert_int_eq(rc, IS_COMPL);
}

Suite *prime_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("is_prime");

    tc = tcase_create("basic test");
    tcase_add_test(tc, test_is_prime_prime);
    tcase_add_test(tc, test_is_prime_simple);
    tcase_add_test(tc, test_is_prime_sqrt);
    tcase_add_test(tc, test_is_prime_zero);
    tcase_add_test(tc, test_is_prime_neg);

    suite_add_tcase(s, tc);

    return s;
}

START_TEST(test_fill_primes_one)
{
    int arr[10];
    int exp[] = {2};
    size_t n = 1;
    fill_prime(arr, n);
    for (size_t i = 0; i < n; ++i)
        ck_assert_int_eq(arr[i], exp[i]);
}
END_TEST

START_TEST(test_fill_primes_three)
{
    int arr[10];
    int exp[] = {2,3,5};
    size_t n = 3;
    fill_prime(arr, n);
    for (size_t i = 0; i < n; ++i)
        ck_assert_int_eq(arr[i], exp[i]);
}
END_TEST

START_TEST(test_fill_primes_several)
{
    int arr[10];
    int exp[] = {2,3,5,7,11};
    size_t n = 5;
    fill_prime(arr, n);
    for (size_t i = 0; i < n; ++i)
        ck_assert_int_eq(arr[i], exp[i]);
}
END_TEST

Suite *fill_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("fill_array");

    tc = tcase_create("basic test");
    tcase_add_test(tc, test_fill_primes_one);
    tcase_add_test(tc, test_fill_primes_three);
    tcase_add_test(tc, test_fill_primes_several);

    suite_add_tcase(s, tc);

    return s;
}

START_TEST(test_add_odd_nums_no_even)
{
    int arr[] = {1, 3, 5, 7};
    size_t n_arr = sizeof(arr) / sizeof(arr[0]);
    int exp[] = {1, 3, 5, 7};
    size_t n_exp = sizeof(exp) / sizeof(exp[0]);

    int res[10];
    size_t n_res;
    int rc = add_odd_nums(arr, n_arr, res, 10, &n_res, 42);

    ck_assert_int_eq(rc, OK);

    ck_assert_uint_eq(n_res, n_exp);
    for (size_t i = 0; i < n_res; ++i)
        ck_assert_int_eq(arr[i], exp[i]);
}
END_TEST

START_TEST(test_add_odd_nums_one_even)
{
    int arr[] = {1, 3, 5, 6, 7};
    size_t n_arr = sizeof(arr) / sizeof(arr[0]);
    int exp[] = {1, 3, 5, 6, 42, 7};
    size_t n_exp = sizeof(exp) / sizeof(exp[0]);

    int res[10];
    size_t n_res;
    int rc = add_odd_nums(arr, n_arr, res, 10, &n_res, 42);

    ck_assert_int_eq(rc, OK);

    ck_assert_uint_eq(n_res, n_exp);
    for (size_t i = 0; i < n_res; ++i)
        ck_assert_int_eq(res[i], exp[i]);
}
END_TEST

START_TEST(test_add_odd_nums_all_even)
{
    int arr[] = {2, 4, 6, 8};
    size_t n_arr = sizeof(arr) / sizeof(arr[0]);
    int exp[] = {2, 0, 4, 0, 6, 0, 8, 0};
    size_t n_exp = sizeof(exp) / sizeof(exp[0]);

    int res[10];
    size_t n_res;
    int rc = add_odd_nums(arr, n_arr, res, 10, &n_res, 0);

    ck_assert_int_eq(rc, OK);

    ck_assert_uint_eq(n_res, n_exp);
    for (size_t i = 0; i < n_res; ++i)
        ck_assert_int_eq(res[i], exp[i]);
}
END_TEST

START_TEST(test_add_odd_nums_buf_size)
{
    int arr[] = {2, 4, 6, 8};
    size_t n_arr = sizeof(arr) / sizeof(arr[0]);

    int res[10];
    size_t n_res;
    int rc = add_odd_nums(arr, n_arr, res, 2, &n_res, 0);

    ck_assert_int_eq(rc, ERROR_BUF_SIZE);
}
END_TEST

START_TEST(test_add_odd_nums_null_ptr)
{
    int arr[] = {2, 4, 6, 8};
    size_t n_arr = sizeof(arr) / sizeof(arr[0]);

    size_t n_res;
    int rc = add_odd_nums(arr, n_arr, NULL, 2, &n_res, 0);

    ck_assert_int_eq(rc, ERROR_ARGS);
}
END_TEST

Suite *add_odd_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("add_odd");

    pos = tcase_create("pos");
    tcase_add_test(pos, test_add_odd_nums_no_even);
    tcase_add_test(pos, test_add_odd_nums_one_even);
    tcase_add_test(pos, test_add_odd_nums_all_even);
    suite_add_tcase(s, pos);

    neg = tcase_create("pos");
    tcase_add_test(neg, test_add_odd_nums_buf_size);
    tcase_add_test(neg, test_add_odd_nums_null_ptr);
    suite_add_tcase(s, neg);

    return s;
}
