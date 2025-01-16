#include "func.h"
#include "matrix_io.h"

int main(void) 
{
    matrix matrix;
    size_t size_n, size_m;
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
    sort_array_by_row_mult(matrix, size_n, size_m);
    output_matrix(matrix, size_n, size_m);
    return 0;
}
