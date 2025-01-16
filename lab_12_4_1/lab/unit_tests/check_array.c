#include "check_array.h"

START_TEST(test_cnt_file_nums_normal)
{
    FILE *f = fopen("test", "w");
    int array[] = {472, 72, 64, 372, 462};
    int len = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < len; i++)
        fprintf(f, "%d ", array[i]);
    fclose(f);
    int result = cnt_file_nums("test");
    ck_assert_int_eq(result, len);
}
END_TEST

START_TEST(test_cnt_file_nums_empty)
{
    FILE *f = fopen("test","w");
    fclose(f);
    int result = cnt_file_nums("test");
    ck_assert_int_eq(result, ERROR_EMPTY);
}
END_TEST

START_TEST(test_cnt_file_nums_no_nums)
{
    FILE *f = fopen("test","w");
    fprintf(f, "hello");
    fclose(f);
    int result = cnt_file_nums("test");
    ck_assert_int_eq(result, ERROR_NOT_NUM);
}
END_TEST

START_TEST(test_cnt_file_nums_alpha)
{
    FILE *f = fopen("test","w");
    fprintf(f, "472 72 guten tag");
    fclose(f);
    int result = cnt_file_nums("test");
    ck_assert_int_eq(result, ERROR_NOT_NUM);
}
END_TEST

START_TEST(test_cnt_file_nums_wrong_file)
{
    FILE *f = fopen("test","w");
    fprintf(f, "472 72 guten tag");
    fclose(f);
    int result = cnt_file_nums("te");
    ck_assert_int_eq(result, ERROR_FILE);
}
END_TEST

Suite *cnt_file_nums_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("cnt_file_nums");

    neg = tcase_create("negative");
    tcase_add_test(neg,test_cnt_file_nums_wrong_file);
    tcase_add_test(neg,test_cnt_file_nums_no_nums);
    tcase_add_test(neg,test_cnt_file_nums_empty);
    tcase_add_test(neg,test_cnt_file_nums_alpha);

    suite_add_tcase(s,neg);

    pos = tcase_create("positive");
    tcase_add_test(pos,test_cnt_file_nums_normal);

    suite_add_tcase(s,pos);

    return s;
}

START_TEST(get_int_array_several_nums)
{

    FILE *f = fopen("test","w");

    int array[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(array) / sizeof(array[0]);
    for (size_t i = 0; i < len; i++)
        fprintf(f, "%d ", array[i]);

    fclose(f);

    int expected[] = {1, 2, 3, 4, 5};

    int *pb = NULL;
    int *pe = NULL;
    int result = get_int_array("test", &pb, &pe);

    ck_assert_int_eq(result, OK);
    ck_assert_ptr_nonnull(pb);
    ck_assert_ptr_nonnull(pe);
    for (int i = 0; i < pe - pb; ++i)
        ck_assert_int_eq(pb[i], expected[i]);
    if (pb)
        free(pb);
}
END_TEST

START_TEST(get_int_array_one_num)
{

    FILE *f = fopen("test","w");
    
    int array[] = {1};
    size_t len = sizeof(array) / sizeof(array[0]);
    for (size_t i = 0; i < len; i++)
        fprintf(f, "%d ", array[i]);

    fclose(f);

    int expected[] = {1};

    int *pb = NULL;
    int *pe = NULL;
    int result = get_int_array("test", &pb, &pe);

    ck_assert_int_eq(result, OK);
    ck_assert_ptr_nonnull(pb);
    ck_assert_ptr_nonnull(pe);
    for (int i = 0; i < pe - pb; ++i)
        ck_assert_int_eq(pb[i], expected[i]);
    if (pb)
        free(pb);
}
END_TEST

START_TEST(get_int_array_several_equal_nums)
{

    FILE *f = fopen("test","w");

    int array[] = {1, 7, 18, 4, 7, 1, 1};
    size_t len = sizeof(array) / sizeof(array[0]);
    for (size_t i = 0; i < len; i++)
        fprintf(f, "%d ", array[i]);

    fclose(f);

    int expected[] = {1,7,18,4,7,1,1};

    int *pb = NULL;
    int *pe = NULL;
    int result = get_int_array("test", &pb, &pe);

    ck_assert_int_eq(result, OK);
    ck_assert_ptr_nonnull(pb);
    ck_assert_ptr_nonnull(pe);
    for (int i = 0; i < pe - pb; ++i)
        ck_assert_int_eq(pb[i], expected[i]);
    if (pb)
        free(pb);
}
END_TEST

START_TEST(get_int_array_several_nums_with_text)
{

    FILE *f = fopen("test","w");
    fprintf(f, "1 7 18 4 7 hello");
    fclose(f);

    int *pb = NULL;
    int *pe = NULL;
    int result = get_int_array("test", &pb, &pe);

    ck_assert_int_eq(result, ERROR_NOT_NUM);
    ck_assert_ptr_null(pb);
    ck_assert_ptr_null(pe);
    if (pb)
        free(pb);
}
END_TEST

START_TEST(get_int_array_empty_file)
{
    FILE *f = fopen("test","w");
    fclose(f);

    int *pb = NULL;
    int *pe = NULL;
    int result = get_int_array("test", &pb, &pe);

    ck_assert_int_eq(result, -2);
    ck_assert_ptr_null(pb);
    ck_assert_ptr_null(pe);
    if (pb)
        free(pb);

}
END_TEST

START_TEST(get_int_array_non_exist)
{
    int *pb = NULL;
    int *pe = NULL;
    int result = get_int_array("test", &pb, &pe);

    ck_assert_int_eq(result, -2);
    ck_assert_ptr_null(pb);
    ck_assert_ptr_null(pe);
    if (pb)
        free(pb);

}
END_TEST

Suite *get_int_array_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("get_int_array");

    neg = tcase_create("negative");
    tcase_add_test(neg,get_int_array_empty_file);
    tcase_add_test(neg,get_int_array_non_exist);
    tcase_add_test(neg,get_int_array_several_nums_with_text);

    suite_add_tcase(s,neg);

    pos = tcase_create("positive");
    tcase_add_test(pos,get_int_array_several_nums);
    tcase_add_test(pos,get_int_array_one_num);
    tcase_add_test(pos,get_int_array_several_equal_nums);

    suite_add_tcase(s,pos);

    return s;
}

START_TEST(test_key_one_element_above_average)
{
    int src[] = {1, 1, 1, 1, 1, 1, 10};
    int expected[] = {10};
    int *pb_dst = malloc(sizeof(int) * (sizeof(src) / sizeof(src[0])));
    int *pe_dst = NULL;
    size_t len = 7;
    int rc = key(src, src + len, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, 1);
    for (int i = 0; i < pe_dst - pb_dst; ++i)
        ck_assert_int_eq(*(pb_dst + i), expected[i]);
    if (pb_dst)
        free(pb_dst);
}
END_TEST

START_TEST(test_key_two_element_above_average)
{
    int src[] = {1, 1, 1, 1, 1, 10, 10};
    int expected[] = {10,10};
    int *pb_dst = malloc(sizeof(int) * (sizeof(src) / sizeof(src[0])));
    int *pe_dst = NULL;
    size_t len = 7;
    int rc = key(src, src + len, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, 2);
    for (int i = 0; i < pe_dst - pb_dst; ++i)
        ck_assert_int_eq(*(pb_dst + i), expected[i]);
    if (pb_dst)
        free(pb_dst);
}
END_TEST

START_TEST(test_key_several_elements_above_average)
{
    int src[] = {1, 1, 1, 1, 10, 10, 10};
    int expected[] = {10,10,10};
    int *pb_dst = malloc(sizeof(int) * (sizeof(src) / sizeof(src[0])));
    int *pe_dst = NULL;
    size_t len = 7;
    int rc = key(src, src + len, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(pb_dst);
    ck_assert_ptr_nonnull(pe_dst);
    ck_assert_int_eq(pe_dst - pb_dst, 3);
    for (int i = 0; i < pe_dst - pb_dst; ++i)
        ck_assert_int_eq(*(pb_dst + i), expected[i]);
    if (pb_dst)
        free(pb_dst);
}
END_TEST

START_TEST(test_key_all_elements_equal)
{
    int src[] = {1, 1, 1, 1, 1};
    int *pb_dst = malloc(sizeof(int) * (sizeof(src) / sizeof(src[0])));
    int *pe_dst = NULL;
    size_t len = 5;
    int rc = key(src, src + len, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, ERROR_NO_ACCEPTABLE_NUMS);
    ck_assert_ptr_null(pe_dst);
    if (pb_dst)
        free(pb_dst);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *pos, *neg;

    s = suite_create("key");

    neg = tcase_create("negative");
    tcase_add_test(neg,test_key_all_elements_equal);

    suite_add_tcase(s,neg);

    pos = tcase_create("positive");
    tcase_add_test(pos,test_key_one_element_above_average);
    tcase_add_test(pos,test_key_two_element_above_average);
    tcase_add_test(pos,test_key_several_elements_above_average);

    suite_add_tcase(s,pos);

    return s;
}

int compare_char(const void *arg1, const void *arg2)
{
   const char *first = arg1;
   const char *second = arg2;
   return *first - *second;
}

int compare_double(const void *arg1, const void *arg2)
{
   const double *first = arg1;
   const double *second = arg2;
   return (*first > *second) - (*first < *second);
}

START_TEST(test_mysort_int_single_elem)
{
    int arr[] = {1};
    int exp[] = {1};
    size_t len = 1;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_int_two_elem)
{
    int arr[] = {2,1};
    int exp[] = {1,2};
    size_t len = 2;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_int_two_elem_sorted)
{
    int arr[] = {1,2};
    int exp[] = {1,2};
    size_t len = 2;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_int_three_elem_sorted)
{
    int arr[] = {1,2,3};
    int exp[] = {1,2,3};
    size_t len = 3;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_int_three_elem)
{
    int arr[] = {56,111,3};
    int exp[] = {3,56,111};
    size_t len = 3;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_int_reversed)
{
    int arr[] = {9,8,7,6,5,4,3,2,1};
    int exp[] = {1,2,3,4,5,6,7,8,9};
    size_t len = 9;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST
START_TEST(test_mysort_int_sorted)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int exp[] = {1,2,3,4,5,6,7,8,9};
    size_t len = 9;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_int_random_no_equal)
{
    int arr[] = {43,6,5436,34,765,13};
    int exp[] = {6,13,34,43,765,5436};
    size_t len = 6;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_int_random__equal)
{
    int arr[] = {43,6,13,34,13,13};
    int exp[] = {6,13,13,13,34,43};
    size_t len = 6;
    mysort(arr,len,sizeof(int),compare_int);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

START_TEST(test_mysort_double_random)
{
    double arr[] = {5.34, 2.2, 3.0, 4.4, 4.3};
    double exp[] = {2.2, 3.0, 4.3, 4.4, 5.34};
    size_t len = 5;
    mysort(arr,len,sizeof(double),compare_double);
    for (size_t i = 0; i < len; i++)
        ck_assert_double_eq_tol(arr[i], exp[i],1e-8);
}
END_TEST

START_TEST(test_mysort_char_random_no_equal)
{
    char arr[] = {43,6,100,34,76,13};
    char exp[] = {6,13,34,43,76,100};
    size_t len = 6;
    mysort(arr,len,sizeof(char),compare_char);
    for (size_t i = 0; i < len; i++)
    {
        ck_assert_int_eq(arr[i], exp[i]);
    }
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *int_sort;
    TCase *double_sort;
    TCase *char_sort;

    s = suite_create("mysort");

    int_sort = tcase_create("tests_int");
    tcase_add_test(int_sort,test_mysort_int_single_elem);
    tcase_add_test(int_sort,test_mysort_int_two_elem);
    tcase_add_test(int_sort,test_mysort_int_two_elem_sorted);
    tcase_add_test(int_sort,test_mysort_int_three_elem_sorted);
    tcase_add_test(int_sort,test_mysort_int_three_elem);
    tcase_add_test(int_sort,test_mysort_int_reversed);
    tcase_add_test(int_sort,test_mysort_int_sorted);
    tcase_add_test(int_sort,test_mysort_int_random_no_equal);
    tcase_add_test(int_sort,test_mysort_int_random__equal);
 
    suite_add_tcase(s,int_sort);

    double_sort = tcase_create("tests_double");
    tcase_add_test(double_sort,test_mysort_double_random);

    suite_add_tcase(s,double_sort);

    char_sort = tcase_create("tests_char");
    tcase_add_test(char_sort,test_mysort_char_random_no_equal);

    suite_add_tcase(s,char_sort);

    return s;
}
