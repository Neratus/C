#include "check_operations.h"
#include <math.h>
#include <check.h>
#include <stdlib.h>

int compare_matrixes(double **first, size_t first_n, size_t first_m, double **second, size_t second_n, size_t second_m)
{
    if ((first_n != second_n) || (first_m != second_m))
        return -2;
    for (size_t i = 0; i < first_n; i++)
        for (size_t j = 0; j < first_m; j++)
            if (fabs(first[i][j] - second[i][j]) > 1e-8)
                return -1;
    return OK;
}

START_TEST(test_add_matrix_3x3_on_3x3)
{
    size_t first_n = 3, first_m = 3;
    size_t second_n = 3, second_m = 3;
    size_t exp_n = 3, exp_m = 3;

    double pfirst[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    double *first[3] = {pfirst[0], pfirst[1], pfirst[2]};
    
    double psecond[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double *second[3] = {psecond[0], psecond[1], psecond[2]};

    double pexp[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
    double *exp[3] = {pexp[0], pexp[1], pexp[2]};

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    matrix_t *second_matr = malloc(sizeof(matrix_t));
    matrix_t *res = NULL;

    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    second_matr->data = second;
    second_matr->n = second_n;
    second_matr->m = second_m;

    int rc = add_matrix(&res, first_matr, second_matr);

    ck_assert_int_eq(rc, OK);  

    ck_assert_int_eq(compare_matrixes(res->data, res->n, res->m, exp, exp_n, exp_m), OK);
    
    free_matrix(res);
    free(first_matr);
    free(second_matr);
}
END_TEST

START_TEST(test_add_matrix_1x3_on_1x3)
{
    size_t first_n = 1, first_m = 3;
    size_t second_n = 1, second_m = 3;
    size_t exp_n = 1, exp_m = 3;

    double pfirst[1][3] = {{1, 2, 3}};
    double *first[1] = {pfirst[0]};
    
    double psecond[1][3] = {{4, 5, 6}};
    double *second[1] = {psecond[0]}; 

    double pexp[1][3] = {{5, 7, 9}};
    double *exp[1] = {pexp[0]};

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    matrix_t *second_matr = malloc(sizeof(matrix_t));
    matrix_t *res = NULL;

    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    second_matr->data = second;
    second_matr->n = second_n;
    second_matr->m = second_m;

    int rc = add_matrix(&res, first_matr, second_matr);

    ck_assert_int_eq(rc, OK); 

    ck_assert_int_eq(compare_matrixes(res->data, res->n, res->m, exp, exp_n, exp_m), OK);
    
    free_matrix(res);
    free(first_matr);
    free(second_matr);
}
END_TEST

START_TEST(test_add_matrix_size)
{
    size_t first_n = 1, first_m = 3;
    size_t second_n = 3, second_m = 3;

    double pfirst[1][3] = {{1, 1, 1}};
    double *first[1] = {pfirst[0]};
    
    double psecond[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double *second[3] = {psecond[0], psecond[1], psecond[2]};

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    matrix_t *second_matr = malloc(sizeof(matrix_t));
    matrix_t *res = NULL;

    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    second_matr->data = second;
    second_matr->n = second_n;
    second_matr->m = second_m;

    int rc = add_matrix(&res, first_matr, second_matr);

    ck_assert_int_eq(rc, ERROR_WRONG_MATR_SIZE); 

    free(res);
    free(first_matr);
    free(second_matr);
}
END_TEST

Suite *add_matrix_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("add_matrix");

    test = tcase_create("test");
    tcase_add_test(test, test_add_matrix_3x3_on_3x3);
    tcase_add_test(test, test_add_matrix_1x3_on_1x3);
    tcase_add_test(test, test_add_matrix_size);

    suite_add_tcase(s,test);

    return s;
}

START_TEST(test_mult_matrix_3x3_on_3x3)
{
    size_t first_n = 3, first_m = 3;
    size_t second_n = 3, second_m = 3;
    size_t exp_n = 3, exp_m = 3;

    double pfirst[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    double *first[3] = {pfirst[0], pfirst[1], pfirst[2]};
    
    double psecond[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double *second[3] = {psecond[0], psecond[1], psecond[2]};

    double pexp[3][3] = {{12, 15, 18}, {12, 15, 18}, {12, 15, 18}};
    double *exp[3] = {pexp[0], pexp[1], pexp[2]};

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    matrix_t *second_matr = malloc(sizeof(matrix_t));
    matrix_t *res = NULL;

    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    second_matr->data = second;
    second_matr->n = second_n;
    second_matr->m = second_m;

    int rc = mult_matrix(&res, first_matr, second_matr);

    ck_assert_int_eq(rc, OK);  
    ck_assert_int_eq(compare_matrixes(res->data, res->n, res->m, exp, exp_n, exp_m), OK);
    
    free_matrix(res);
    free(first_matr);
    free(second_matr);
}
END_TEST

START_TEST(test_mult_matrix_1x3_on_3x1)
{
    size_t first_n = 1, first_m = 3;
    size_t second_n = 3, second_m = 1;
    size_t exp_n = 1, exp_m = 1;

    double pfirst[1][3] = {{1, 2, 3}};
    double *first[1] = {pfirst[0]};
    
    double psecond[3][1] = {{1}, {2}, {3}};
    double *second[3] = {psecond[0], psecond[1], psecond[2]};

    double pexp[1][1] = {{14}};
    double *exp[1] = {pexp[0]};

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    matrix_t *second_matr = malloc(sizeof(matrix_t));
    matrix_t *res = NULL;

    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    second_matr->data = second;
    second_matr->n = second_n;
    second_matr->m = second_m;

    int rc = mult_matrix(&res, first_matr, second_matr);

    ck_assert_int_eq(rc, OK); 
    ck_assert_int_eq(compare_matrixes(res->data, res->n, res->m, exp, exp_n, exp_m), OK);
    
    free_matrix(res);
    free(first_matr);
    free(second_matr);
}
END_TEST

START_TEST(test_mult_matrix_size)
{
    size_t first_n = 1, first_m = 4;
    size_t second_n = 3, second_m = 3;

    double pfirst[1][4] = {{1, 1, 1, 4}};
    double *first[1] = {pfirst[0]};
    
    double psecond[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double *second[3] = {psecond[0], psecond[1], psecond[2]};

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    matrix_t *second_matr = malloc(sizeof(matrix_t));

    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    second_matr->data = second;
    second_matr->n = second_n;
    second_matr->m = second_m;

    matrix_t *res = NULL;
    int rc = mult_matrix(&res, first_matr, second_matr);

    ck_assert_int_eq(rc, ERROR_WRONG_MATR_SIZE);

    free(first_matr);
    free(second_matr);
}
END_TEST

Suite *mult_matrix_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("mult_matrix");

    test = tcase_create("test");
    tcase_add_test(test, test_mult_matrix_3x3_on_3x3);
    tcase_add_test(test, test_mult_matrix_1x3_on_3x1);
    tcase_add_test(test, test_mult_matrix_size);

    suite_add_tcase(s, test);

    return s;
}

START_TEST(test_find_deter_3x3)
{
    size_t first_n = 3, first_m = 3;

    double pfirst[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    double *first[3] = {pfirst[0], pfirst[1], pfirst[2]};
    
    double exp = 0;
    double res;

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    int rc = calc_gauss_deter(&res, first_matr);

    ck_assert_int_eq(rc, OK);
    ck_assert_double_eq_tol(res, exp, 1e-8);

    free(first_matr);
}
END_TEST

START_TEST(test_find_deter_4x4)
{
    size_t first_n = 4, first_m = 4;

    double pfirst[4][4] = {{12, 72, 24, 77}, {49, 45, 82, 32}, {84, 27, 33, 31}, {32, 97, 98, 15}};
    double *first[4] = {pfirst[0], pfirst[1], pfirst[2], pfirst[3]};
    
    double exp = -21793101;
    double res;

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    int rc = calc_gauss_deter(&res, first_matr);

    ck_assert_int_eq(rc, OK);
    ck_assert_double_eq_tol(res, exp, 1e-8);

    free(first_matr);
}
END_TEST

START_TEST(test_find_deter_4x2)
{
    size_t first_n = 4, first_m = 2;

    double pfirst[4][2] = {{12, 72}, {49, 45}, {84, 27}, {32, 97}};
    double *first[4] = {pfirst[0], pfirst[1], pfirst[2], pfirst[3]};
    
    double res;

    matrix_t *first_matr = malloc(sizeof(matrix_t));
    first_matr->data = first;
    first_matr->n = first_n;
    first_matr->m = first_m;

    int rc = calc_gauss_deter(&res, first_matr);

    ck_assert_int_eq(rc, ERROR_WRONG_MATR_SIZE);

    free(first_matr);
}
END_TEST

Suite *find_deter_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("calc_gauss_deter");

    test = tcase_create("test");
    tcase_add_test(test, test_find_deter_4x4);
    tcase_add_test(test, test_find_deter_3x3);
    tcase_add_test(test, test_find_deter_4x2);

    suite_add_tcase(s, test);

    return s;
}
