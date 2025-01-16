#include "func.h"
#include "matrix_io.h"


int main(void) 
{
    matrix matrix;
    size_t size_n, size_m;
    int rc;
    printf("Enter the size of the matrix and its elements: ");
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
    if (rc == ERROR_MATRIX_IS_NOT_SQUARE) 
    {
        printf("ERROR:Matrix must be square\n");
        return ERROR_MATRIX_IS_NOT_SQUARE;
    }
    rc = find_num_below_side_diagonal(matrix, size_n);
    if (rc == ERROR_NO_ACCEPTABLE_NUM)
    {
        printf("ERROR:No required number in matrix\n");
        return ERROR_NO_ACCEPTABLE_NUM;
    }
    printf("The required number is : %d\n", rc);
    return 0;
}
