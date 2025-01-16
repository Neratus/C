#include <string.h>
#include "matrix.h"

#define ERROR_WRONG_ARG_CNT 1
#define ERROR_WRONG_ARG 2

int main(int argc, char **argv)
{
    int rc;

    matrix_t *first = NULL;
    matrix_t *second = NULL;
    matrix_t *res = NULL;

    if ((argc == 4) && (strcmp(argv[1], "o") == 0))
    {
        rc = input_matrix(&first, argv[2]);
        if (rc != OK)
            return rc;

        double num;
        rc = calc_gauss_deter(&num, first);
        free_matrix(first);
        if (rc != OK)
            return rc;

        FILE *f = fopen(argv[3], "w");
        if (f == NULL)
            return ERROR_FILE;
        fprintf(f, "%lf \n", num);
        fclose(f);

        return OK;
    }
    else if (argc == 5)
    {
        rc = input_matrix(&first, argv[2]);
        if (rc != OK)
            return rc;

        rc = input_matrix(&second, argv[3]);
        if (rc != OK)
        {
            free(first->data);
            free(first);
            return rc;
        }

        if (strcmp(argv[1], "a") == 0)
            rc = add_matrix(&res, first, second);
        else if (strcmp(argv[1], "m") == 0)
            rc = mult_matrix(&res, first, second);
        else
            rc = ERROR_WRONG_ARG;

        if (rc != OK)
        {
            free_matrix(first);
            free_matrix(second);
            return rc;
        }

        rc = print_matrix_coord(argv[4], res);

        free_matrix(first);
        free_matrix(second);
        free_matrix(res);

        return rc;
    }

    return ERROR_WRONG_ARG_CNT;
}
