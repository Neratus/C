#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10 
#define M 10 
#define ERROR_SIZE_INPUT 1  

typedef int matrix [N][M];

int input_matrix_size(size_t *arr_n, size_t *arr_m);

void output_matrix(matrix matrix, size_t arr_n, size_t arr_m);

#endif
