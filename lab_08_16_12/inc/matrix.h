#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-7

#define OK 0
#define ERROR_FILE -1
#define ERROR_INPUT_SIZE -2
#define ERROR_INPUT_SIZE_VAL -3
#define ERROR_MALLOC -4
#define ERROR_INPUT -5
#define ERROR_WRONG_MATR_SIZE -6

typedef struct
{
    double **data;
    size_t n;
    size_t m;
}matrix_t;

matrix_t *allocate_matrix(size_t n, size_t m);

void free_matrix(matrix_t *matrix);

int input_matrix(matrix_t **matrix, char *path);

int print_matrix_coord(char *path, matrix_t *matrix);

int add_matrix(matrix_t **result, matrix_t *first, matrix_t *second);

int mult_matrix(matrix_t **result, matrix_t *first, matrix_t *second);

int calc_gauss_deter(double *res, matrix_t *matrix);

#endif
