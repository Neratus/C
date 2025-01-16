#ifndef FUNC_H
#define FUNC_H
#include "matrix_io.h"

int calc_mult_of_array_elem(int array[M], size_t array_size);

void swap_array_el(int first[M], int second[M], size_t array_size);

int compare_array_by_el_value(int first[M], int second[M], size_t array_size);

void sort_array_by_row_mult(matrix matrix, size_t arr_n, size_t arr_m);

#endif
