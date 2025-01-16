#include "func.h"
#include "matrix_io.h"


int is_col_alternate_pos_neg(matrix matrix, size_t col_num, size_t arr_n)
{
    if (arr_n == 1) 
    {
        return 0;
    }
    for (size_t i = 1; i < arr_n; i++)
    {
        if (matrix[i - 1][col_num] * matrix[i][col_num] >= 0)
        {
            return 0;
        }
    }
    return 1;
}


void matrix_alternate_pos_neg(matrix matrix, size_t arr_n, size_t arr_m, int res[M])
{
    for (size_t i = 0; i < arr_m; i++) 
    {
        res[i] = is_col_alternate_pos_neg(matrix, i, arr_n);
    }
}

