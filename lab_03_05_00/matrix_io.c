#include "matrix_io.h"


int input_matrix(matrix matrix, size_t *arr_n, size_t *arr_m) 
{
    printf("Enter the size of the matrix and its elements: ");
    if ((scanf("%zu%zu", arr_n, arr_m) != 2)) 
        return ERROR_SIZE_INPUT;
    if (((*arr_n > N) || (*arr_n <= 0)) || ((*arr_m > N) || (*arr_m <= 0)))
        return ERROR_SIZE_INPUT;
    for (size_t i = 0; i < *arr_n; i++) 
    {
        for (size_t j = 0; j < *arr_m; j++) 
        {
            if (scanf("%d", &matrix[i][j]) != 1) 
                return ERROR_MATRIX_INPUT;
        }
    }
    printf("\n");
    return 0;
}


void output_matrix(matrix matrix, size_t arr_n, size_t arr_m) 
{
    for (size_t i = 0; i < arr_n; i++)
    {
        for (size_t j = 0; j < arr_m; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");   
    }
}
