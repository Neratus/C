#include "matrix_io.h"


void reverse_array(int array[], size_t size_of_array)
{
    int tmp;
    for (size_t i = 0; i < size_of_array / 2; ++i)
    {
        tmp = array[i];
        array[i] = array[size_of_array - 1 - i];
        array[size_of_array - 1 - i] = tmp;
    }
}


int is_prime(int num)
{
    if (num <= 1)
    {
        return 1; 
    }
    for (int cur = 2; cur * cur <= num; cur++)
    {
        if (num % cur == 0)
        {
            return 1;
        }
    }
    return 0;
}


void replace_prime_nums(matrix matrix, size_t arr_n, size_t arr_m, int res[N * M], size_t size_of_res)
{
    size_t i = 0;
    size_t j = 0;
    size_t insert = 0;
    while ((i < arr_n) && (insert < size_of_res))
    {
        if (is_prime(matrix[i][j]) == 0)
        {
            matrix[i][j] = res[insert];
            insert++;
        }
        if (j >= arr_m - 1)
        {
            j = 0;
            i++;
        }
        else
        {
            j++;
        }
    } 
}


int find_prime_nums(matrix matrix, size_t arr_n, size_t arr_m, int res[N * M])
{
    size_t size_of_res = 0;
    for (size_t i = 0; i < arr_n; i++)
    {
        for (size_t j = 0; j < arr_m; j++)
        {
            if (is_prime(matrix[i][j]) == 0)
            {
                res[size_of_res] = matrix[i][j];
                size_of_res++;
            }
        }
    }
    return size_of_res;
}
