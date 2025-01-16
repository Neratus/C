#ifndef ARR_H
#define ARR_H

#include <stdlib.h>

#define IS_PRIME 1
#define IS_COMPL 0

#define ERROR_ARGS -1
#define ERROR_BUF_SIZE -2
#define OK 0

int is_prime(int num);

void fill_prime(int *arr, size_t size);

int cnt_nums_for_add_odd(int *arr, size_t size);

int add_odd_nums(int *arr, size_t arr_size, int *dest, size_t buf_size, size_t *dest_size, int num);

#endif
