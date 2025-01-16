#ifndef MATRIX_H
#define MATRIX_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10  
#define M 10  
#define ERROR_SIZE_INPUT -1  
#define ERROR_MATRIX_INPUT -2  
#define ERROR_MATRIX_IS_NOT_SQUARE -3 

typedef int matrix [N][M];

int input_matrix(matrix matrix, size_t *arr_n, size_t *arr_m);


#endif
