#include "func.h"
#include "matrix_io.h"


int main(void) 
{
    matrix matrix;
    size_t size_n, size_m, size_res;
    int rc;
    int res[N * M];
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
    size_res = find_prime_nums(matrix, size_n, size_m, res);
    if (size_res == 0)
    {
        printf("ERROR:no prime numbers in matrix\n");
        return ERROR_NO_PRIME_NUM;
    }
    reverse_array(res, size_res);
    replace_prime_nums(matrix, size_n, size_m, res, size_res);
    output_matrix(matrix, size_n, size_m);
    return 0;
}
