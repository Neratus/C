#include <limits.h>
#include <stdio.h>
#include "check_my_snprintf.h"
#include "my_snprintf.h"

#define BUFF_LEN 50

START_TEST(test_my_snprintf_str_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    cnt1 = my_snprintf(buf1, size, "%s", "Guten tag!");
    cnt2 = snprintf(buf2, size, "%s", "Guten tag!");
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_str_several_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    cnt1 = my_snprintf(buf1, size, "%s %s %s", "Say", "My", "Name");
    cnt2 = snprintf(buf2, size, "%s %s %s",  "Say", "My", "Name");
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_num_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    int num = 0123;
    cnt1 = my_snprintf(buf1, size, "%d", num);
    cnt2 = snprintf(buf2, size, "%d", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_negative_num_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    int num = -123;
    cnt1 = my_snprintf(buf1, size, "%d", num);
    cnt2 = snprintf(buf2, size, "%d", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_max_num_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    int num = INT_MAX;
    cnt1 = my_snprintf(buf1, size, "%d", num);
    cnt2 = snprintf(buf2, size, "%d", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_min_num_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    int num = INT_MIN;
    cnt1 = my_snprintf(buf1, size, "%d", num);
    cnt2 = snprintf(buf2, size, "%d", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_hex_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    unsigned short num = 123;
    cnt1 = my_snprintf(buf1, size, "%hx", num);
    cnt2 = snprintf(buf2, size, "%hx", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_hex_neg_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    short num = -123;
    cnt1 = my_snprintf(buf1, size, "%hx", num);
    cnt2 = snprintf(buf2, size, "%hx", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_hex_max_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    unsigned short num = 65535;
    cnt1 = my_snprintf(buf1, size, "%hx", num);
    cnt2 = snprintf(buf2, size, "%hx", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_hex_min_test)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    unsigned short num = 0;
    cnt1 = my_snprintf(buf1, size, "%hx", num);
    cnt2 = snprintf(buf2, size, "%hx", num);
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_len_le_size)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 10;
    int cnt1, cnt2;
    int num = 0123;
    cnt1 = my_snprintf(buf1, size, "%hx %s", num, "Hello");
    cnt2 = snprintf(buf2, size, "%hx %s", num, "Hello");
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_snprintf_len_gt_size)
{
    char buf1[BUFF_LEN], buf2[BUFF_LEN];
    size_t size = 5;
    int cnt1, cnt2;
    int num = 0123;
    cnt1 = my_snprintf(buf1, size, "%hx %s", num, "Hello");
    cnt2 = snprintf(buf2, size, "%hx %s", num, "Hello");
    ck_assert_int_eq(cnt1, cnt2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_str, *tc_int, *tc_hex, *tc_len;

    s = suite_create("my_snprintf");

    tc_str = tcase_create("String");
    tcase_add_test(tc_str, test_my_snprintf_str_test);
    tcase_add_test(tc_str, test_my_snprintf_str_several_test);
    suite_add_tcase(s, tc_str);

    tc_int = tcase_create("Int");
    tcase_add_test(tc_int, test_my_snprintf_num_test);
    tcase_add_test(tc_int, test_my_snprintf_negative_num_test);
    tcase_add_test(tc_int, test_my_snprintf_max_num_test);
    tcase_add_test(tc_int, test_my_snprintf_min_num_test);
    suite_add_tcase(s, tc_int);

    tc_hex = tcase_create("Hex");
    tcase_add_test(tc_hex, test_my_snprintf_hex_test);
    tcase_add_test(tc_hex, test_my_snprintf_hex_neg_test);
    tcase_add_test(tc_hex, test_my_snprintf_hex_max_test);
    tcase_add_test(tc_hex, test_my_snprintf_hex_min_test);
    suite_add_tcase(s, tc_hex);

    tc_len = tcase_create("length");
    tcase_add_test(tc_len, test_my_snprintf_len_le_size);
    tcase_add_test(tc_len, test_my_snprintf_len_gt_size);
    suite_add_tcase(s, tc_len);

    return s;
}
