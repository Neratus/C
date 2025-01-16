#ifndef FUNC_H
#define FUNC_H
#include "matrix_io.h"

#define ERROR_NO_PRIME_NUM -3 

void reverse_array(int array[], size_t size_of_array);

int is_prime(int num);

void replace_prime_nums(matrix matrix, size_t arr_n, size_t arr_m, int res[N * M], size_t size_of_res);

int find_prime_nums(matrix matrix, size_t arr_n, size_t arr_m, int res[N * M]);

#endif
