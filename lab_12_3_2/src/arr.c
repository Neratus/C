#include "arr.h"
#include <math.h>

int is_prime(int num)
{
    if (num <= 1)
        return IS_COMPL;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return IS_COMPL;
    return IS_PRIME;
}

void fill_prime(int *arr, size_t size)
{
    int cur = 2;
    for (size_t i = 0; i < size; cur++)
       if (is_prime(cur) == IS_PRIME)
            arr[i++] = cur;
}

int cnt_nums_for_add_odd(int *arr, size_t size)
{
    int res_size = 0;
    for (size_t i = 0; i < size; i++)
    {
        res_size++;
        if (arr[i] % 2 == 0)
            res_size++;
    }
    return res_size;
}

int add_odd_nums(int *arr, size_t arr_size, int *dest, size_t buf_size, size_t *dest_size, int num)
{
    if ((arr == NULL) || ((dest == NULL) && (buf_size != 0)) || ((arr == NULL) && (arr_size != 0)))
        return ERROR_ARGS;
    size_t cur_size = 0;
    for (size_t i = 0; i < arr_size; i++)
    {
        if (cur_size >= buf_size)
            return ERROR_BUF_SIZE;
        int elem = arr[i];
        dest[cur_size++] = elem;
        if (elem % 2 == 0)
        {
            if (cur_size < buf_size)
                dest[cur_size++] = num;
        }
    }
    *dest_size = cur_size;
    return OK;
}
