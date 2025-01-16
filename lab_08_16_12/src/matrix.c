#include "matrix.h"

matrix_t *allocate_matrix(size_t n, size_t m)
{
    matrix_t *matrix = malloc(sizeof(matrix_t));
    if (matrix == NULL)
    {
        free(matrix);
        matrix->data = NULL; 
        matrix->n = n;
        matrix->m = m;
        return matrix;
    }

    double **data = malloc(n * sizeof(double*) + n * m * sizeof(double));
    if (!data)
    {
        free(matrix);
        matrix->data = NULL; 
        matrix->n = n;
        matrix->m = m;
        return matrix;
    }

    for (size_t i = 0; i < n; i++)
    {
        data[i] = (double*)((char*) data + n * sizeof(double*) + i * m * sizeof(double));
        if (!data[i])
        {
            free(matrix);
            free(data);
            matrix->data = NULL;
            matrix->n = n;
            matrix->m = m;
            return matrix;
        }
    }
    matrix->data = data;
    matrix->n = n;
    matrix->m = m;
    return matrix;
}

void free_matrix(matrix_t *matrix)
{
    free(matrix->data);
    free(matrix);
}

int input_matrix(matrix_t **matrix, char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        return ERROR_FILE;

    size_t input_n, input_m;
    if (fscanf(f, "%zu %zu", &input_n, &input_m) != 2)
    {
        fclose(f);
        return ERROR_INPUT_SIZE;
    }
    if ((input_n == 0) || (input_m == 0))
    {
        fclose(f);
        return ERROR_INPUT_SIZE_VAL;
    }

    *matrix = allocate_matrix(input_n, input_m);
    if ((*matrix) == NULL || (*matrix)->data == NULL)
    {
        fclose(f);
        return ERROR_MALLOC;
    }

    double cur_elem;
    for (size_t i = 0; i < input_n; i++)
        for (size_t j = 0; j < input_m; j++)
        {
            if (fscanf(f, "%lf", &cur_elem) != 1)
            {
                free_matrix(*matrix);
                fclose(f);
                return ERROR_INPUT;
            }
            (*matrix)->data[i][j] = cur_elem;
        }

    fclose(f);
    return OK;
}

int print_matrix_coord(char *path, matrix_t *matrix)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
        return ERROR_FILE;
        
    size_t count_not_null = 0;
    for (size_t i = 0; i < matrix->n; i++)
        for (size_t j = 0; j < matrix->m; j++)
            if (fabs(matrix->data[i][j]) >= EPS)
                count_not_null++;

    fprintf(f, "%zu %zu %zu\n", matrix->n, matrix->m, count_not_null);

    for (size_t i = 0; i < matrix->n; i++)
        for (size_t j = 0; j < matrix->m; j++)
            if (fabs(matrix->data[i][j]) >= EPS)
                fprintf(f, "%zu %zu %lf\n", i + 1, j + 1, matrix->data[i][j]);

    fclose(f);
    return OK;
}

int add_matrix(matrix_t **result, matrix_t *first, matrix_t *second)
{
    if ((first->n != second->n) || (first->m != second->m))
        return ERROR_WRONG_MATR_SIZE;

    *result = allocate_matrix(first->n, first->m);  
    if ((*result)->data == NULL)
        return ERROR_MALLOC;

    for (size_t i = 0; i < first->n; i++)
        for (size_t j = 0; j < first->m; j++)
            (*result)->data[i][j] = first->data[i][j] + second->data[i][j];

    return OK;
}

int mult_matrix(matrix_t **result, matrix_t *first, matrix_t *second)
{
    if (first->m != second->n)
        return ERROR_WRONG_MATR_SIZE;

    *result = allocate_matrix(first->n, second->m); 
    if ((*result)->data == NULL)
        return ERROR_MALLOC;

    for (size_t i = 0; i < first->n; i++)
        for (size_t j = 0; j < second->m; j++)
        {
            (*result)->data[i][j] = 0;
            for (size_t g = 0; g < first->m; g++)
                (*result)->data[i][j] += first->data[i][g] * second->data[g][j];
        }

    return OK;
}

int calc_gauss_deter(double *res, matrix_t *matrix)
{
    if (matrix->n != matrix->m)
        return ERROR_WRONG_MATR_SIZE;

    *res = 1;
    for (size_t i = 0; i < matrix->n; i++)
    {
        double cur_num = fabs(matrix->data[i][i]);
        size_t index = i;
        for (size_t j = i + 1; j < matrix->n; j++)
            if (fabs(matrix->data[j][i]) > cur_num)
            {
                cur_num = fabs(matrix->data[j][i]);
                index = j;
            }

        if (index != i)
        {
            for (size_t k = 0; k < matrix->n; k++)
            {
                double temp = matrix->data[i][k];
                matrix->data[i][k] = matrix->data[index][k];
                matrix->data[index][k] = temp;
            }
            *res *= -1;
        }
        
        for (size_t j = i + 1; j < matrix->n; j++)
        {
            if (fabs(matrix->data[i][i]) > EPS)
            {
                double mult = matrix->data[j][i] / matrix->data[i][i];
                for (size_t h = i; h < matrix->n; h++)
                    matrix->data[j][h] -= matrix->data[i][h] * mult;  
            } 
        }
    }
    
    for (size_t i = 0; i < matrix->n; i++)
        *res *= matrix->data[i][i];

    return OK;
}
