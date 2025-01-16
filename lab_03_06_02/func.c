#include "func.h"


void fill_matrix_reverse_bull(matrix matrix, size_t arr_n, size_t arr_m)
{
    int cur = 1;
    size_t i = arr_n;
    size_t j = arr_m;
    while (j > 0)
    {
        if (i == 0)
        { 
            while (i < arr_n)
            {
                matrix[i][j - 1] = cur;
                cur++;
                i++;
            }
        }
        else
        {
            while (i > 0)
            {
                matrix[i - 1][j - 1] = cur;
                cur++;
                i--;
            }
        }
        j--;
    }
}
