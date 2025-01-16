#include "check_io.h"
#include <check.h>

START_TEST(allocate_matrix_3x3)
{
    matrix_t *matrix;
    size_t n = 3;
    size_t m = 3;
    matrix = allocate_matrix(n, m);
    ck_assert_ptr_nonnull(matrix->data);
    matrix->data[0][0] = 2;
    matrix->data[2][2] = 2;
    matrix->data[1][0] = 2;
    free_matrix(matrix);
}
END_TEST

START_TEST(allocate_matrix_1x3)
{
    size_t n = 1;
    size_t m = 3;
    matrix_t *matrix = allocate_matrix(n, m);
    ck_assert_ptr_nonnull(matrix->data);
    matrix->data[0][0] = 2;
    matrix->data[0][1] = 2;
    matrix->data[0][2] = 2;
    free_matrix(matrix);
}
END_TEST

START_TEST(allocate_matrix_1x1)
{
    size_t n = 1;
    size_t m = 1;
    matrix_t *matrix = allocate_matrix(n, m);
    ck_assert_ptr_nonnull(matrix->data);
    matrix->data[0][0] = 2;
    free_matrix(matrix);
}
END_TEST

START_TEST(allocate_matrix_3x1)
{
    size_t n = 3;
    size_t m = 1;
    matrix_t *matrix = allocate_matrix(n, m);
    ck_assert_ptr_nonnull(matrix->data);
    matrix->data[0][0] = 2;
    matrix->data[2][0] = 3;
    free_matrix(matrix);
}
END_TEST

Suite *allocate_matrix_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("allocate_matrix");

    test = tcase_create("test");
    tcase_add_test(test,allocate_matrix_3x3);
    tcase_add_test(test,allocate_matrix_1x3);
    tcase_add_test(test,allocate_matrix_3x1);
    tcase_add_test(test,allocate_matrix_1x1);

    suite_add_tcase(s,test);

    return s;
}
