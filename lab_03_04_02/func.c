#include "func.h"


int find_num_below_side_diagonal(matrix matrix, size_t array_size)
{
    int a = 0;
    for (size_t i = 1; i < array_size; i++)
    {
        for (size_t j = array_size - 1; j > array_size - i - 1; j--)
        {
            if ((abs(matrix[i][j]) % 10 == 5) && (a == 0 || matrix[i][j] > a))
            {
                a = matrix[i][j];
            }
        }    
    }
    if (a == 0)
    {
    return ERROR_NO_ACCEPTABLE_NUM;
    }
    return a;
}
