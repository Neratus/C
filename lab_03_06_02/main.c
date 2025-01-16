#include "func.h"
#include "matrix_io.h"



int main(void) 
{
    matrix matrix;
    size_t size_n, size_m;
    int rc;
    printf("Enter the size of the matrix and its elements: ");
    rc = input_matrix_size(&size_n, &size_m);
    if (rc == ERROR_SIZE_INPUT) 
    {
        printf("ERROR:Invalid matrix size\n");
        return ERROR_SIZE_INPUT;
    }
    fill_matrix_reverse_bull(matrix, size_n, size_m);
    output_matrix(matrix, size_n, size_m);
    return 0;
}
