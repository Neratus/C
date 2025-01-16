#include "func.h"
#include "matrix_io.h"


void print_array(int array[], size_t size_of_array)
{
    for (size_t i = 0; i < size_of_array; i++)
    {
        printf("%d ", array[i]);
    }
}

int main(void) 
{
    matrix matrix;
    size_t size_n, size_m;
    int res[M];
    int rc;
    printf("Enter the size of the matrix and it's elements: ");
    rc = input_matrix(matrix, &size_n, &size_m);
    if (rc == ERROR_SIZE_INPUT) 
    {
        printf("ERROR:Invalid matrix size\n");
        return ERROR_SIZE_INPUT;
    }
    if (rc == ERROR_MATRIX_INPUT) 
    {
        printf("ERROR:Invalid value of an matrix element\n");
        return ERROR_MATRIX_INPUT;
    }    
    matrix_alternate_pos_neg(matrix, size_n, size_m, res);
    printf("The resulting array : ");
    print_array(res, size_m);
    printf("\n");
    return 0;
}
