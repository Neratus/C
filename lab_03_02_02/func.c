#include "func.h"

int sum_digits(int number)
{
    number = abs(number);
    int digit_sum = 0;
    while (number > 0)
    {
        digit_sum += number % 10;
        number /= 10; 
    }
    return digit_sum;
}


int is_sum_digits_of_array_el_odd(int array[M], size_t array_size) 
{
    int count = 0;
    size_t cur = 0;
    while ((cur < array_size) && (count < 2))
    {
        if (sum_digits(array[cur]) % 2 == 1)
            count++;
        cur++;
    }
    if (count >= 2)
        return 1;
    return 0;
}


void add_rows_before_odd_num_sum(matrix matrix, size_t *arr_n, size_t arr_m)
{
    size_t iter_c = *arr_n;
    for (size_t i = 0; i < iter_c; i++)
    {
        if (is_sum_digits_of_array_el_odd(matrix[i], arr_m))
        {
            size_t i_insert = i;
            (*arr_n)++;
            for (size_t j = *arr_n - 1; j > i_insert; --j)
            {
                for (size_t g = 0; g < arr_m; ++g)
                    matrix[j][g] = matrix[j - 1][g];
            }
            for (size_t g = 0; g < arr_m; ++g)
                matrix[i_insert][g] = -1;
            i++;
            iter_c++;
        }
    }
}
