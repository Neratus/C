#include "matrix_list.h"

int compare_elems(const void *first, const void *second)
{
    const matrix_elem_t *first_elem = first;
    const matrix_elem_t *second_elem = second;
    if (first_elem->row != second_elem->row)
        return (int)(first_elem->row - second_elem->row);
    return (int)(first_elem->col - second_elem->col);
}

void print_elem(FILE *f, const void *elem_ptr)
{
    const matrix_elem_t *elem = elem_ptr;
    fprintf(f, "%zu %zu %d ", elem->row, elem->col, elem->value);
}

void print_elem_list(FILE *f, node_t *head)
{
    print_list(f, head, print_elem);
}

int init_matrix_list(node_t **head)
{
    size_t n, m;
    if (scanf("%zu %zu", &n, &m) != 2)
        return ERROR_SIZE_INPUT;
    if ((n <= 0) || (m <= 0))
        return ERROR_SIZE_VALUE;
    *head = NULL;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            matrix_elem_t *cur = malloc(sizeof(matrix_elem_t));
            if (cur == NULL)
                return ERROR_MALLOC;

            if (scanf("%d", &cur->value) != 1)
            {
                free(cur);
                return ERROR_ELEM_INPUT;
            }
            
            if (cur->value == 0)
            {
                free(cur);
                continue;
            }
            
            cur->row = i;
            cur->col = j;
            node_t *tmp = node_create(cur);
            if (tmp == NULL)
            {
                free(cur);
                return ERROR_MALLOC;
            }
            *head = list_add_tail(*head, tmp);
        }
    }
    return OK;
}

int add_matrix(node_t *first, node_t *second, node_t **res)
{
    if (first == NULL)
    {
        *res = second;
        return OK;
    }
    else if (second == NULL)
    {
        *res = first;
        return OK;
    }
    *res = NULL;
    node_t *cur_first = first;
    node_t *cur_second = second;
    while ((cur_first != NULL) && (cur_second != NULL))
    {
        int cmp = compare_elems(cur_first->data, cur_second->data);
        if (cmp < 0)
        {   
            matrix_elem_t *res_elem = malloc(sizeof(matrix_elem_t));
            if (res_elem == NULL)
                return ERROR_MALLOC;
            res_elem->row = ((matrix_elem_t*)cur_first->data)->row;
            res_elem->col = ((matrix_elem_t*)cur_first->data)->col;
            res_elem->value = ((matrix_elem_t*)cur_first->data)->value;
            *res = list_add_tail(*res, node_create(res_elem));

            if (*res == NULL)
                return ERROR_MALLOC;
            cur_first = cur_first->next;
        }
        else if (cmp == 0)
        {
            matrix_elem_t *res_elem = malloc(sizeof(matrix_elem_t));
            if (res_elem == NULL)
                return ERROR_MALLOC;
            res_elem->row = ((matrix_elem_t*)cur_first->data)->row;
            res_elem->col = ((matrix_elem_t*)cur_first->data)->col;
            res_elem->value = ((matrix_elem_t*)cur_first->data)->value + ((matrix_elem_t*)cur_second->data)->value;
            
            *res = list_add_tail(*res, node_create(res_elem));
            cur_first = cur_first->next;
            cur_second = cur_second->next;
        }
        else
        {
            matrix_elem_t *res_elem = malloc(sizeof(matrix_elem_t));
            if (res_elem == NULL)
                return ERROR_MALLOC;
            res_elem->row = ((matrix_elem_t*)cur_second->data)->row;
            res_elem->col = ((matrix_elem_t*)cur_second->data)->col;
            res_elem->value = ((matrix_elem_t*)cur_second->data)->value;
            *res = list_add_tail(*res, node_create(res_elem));
            if (*res == NULL)
                return ERROR_MALLOC;

            cur_second = cur_second->next;
        }  
    }
    if (cur_first != NULL)
    {
        while (cur_first != NULL)
        {
            matrix_elem_t *res_elem = malloc(sizeof(matrix_elem_t));
            if (res_elem == NULL)
                return ERROR_MALLOC;
            res_elem->row = ((matrix_elem_t*)cur_first->data)->row;
            res_elem->col = ((matrix_elem_t*)cur_first->data)->col;
            res_elem->value = ((matrix_elem_t*)cur_first->data)->value;
            *res = list_add_tail(*res, node_create(res_elem));

            cur_first = cur_first->next;
        }
    }
    else if (cur_second != NULL)
    {
        while (cur_second != NULL)
        {
            matrix_elem_t *res_elem = malloc(sizeof(matrix_elem_t));
            if (res_elem == NULL)
                return ERROR_MALLOC;
            res_elem->row = ((matrix_elem_t*)cur_second->data)->row;
            res_elem->col = ((matrix_elem_t*)cur_second->data)->col;
            res_elem->value = ((matrix_elem_t*)cur_second->data)->value;

            *res = list_add_tail(*res, node_create(res_elem));
            cur_second = cur_second->next;
        }
    }
    return OK;
}

int matrix_multiply(node_t *first, node_t *second, node_t **res)
{
    *res = NULL;

    node_t *cur_first = first;
    while (cur_first != NULL)
    {
        matrix_elem_t *first_data = cur_first->data;
        node_t *cur_second = second;
        while (cur_second != NULL)
        {
            matrix_elem_t *second_data = cur_second->data;
            if (first_data->col == second_data->row)
            {
                node_t *cur_res = *res;
                int found = 0;
                while (cur_res != NULL)
                {
                    matrix_elem_t *res_data = cur_res->data;
                    if ((first_data->row == res_data->row) && (second_data->col == res_data->col))
                    {
                        res_data->value += first_data->value * second_data->value;
                        found = 1;
                        break;
                    }
                    cur_res = cur_res->next;
                }
                if (found == 0)
                {
                    matrix_elem_t *res_elem = malloc(sizeof(matrix_elem_t));
                    if (res_elem == NULL)
                        return ERROR_MALLOC;
                    res_elem->row = first_data->row;
                    res_elem->col = second_data->col;
                    res_elem->value = first_data->value * second_data->value;
                    node_t *tmp = node_create(res_elem);
                    if (tmp == NULL)
                        return ERROR_MALLOC;
                    *res = list_add_tail(*res, tmp);
                }
            }
            cur_second = cur_second->next;
        }
        cur_first = cur_first->next;
    }
    return OK;
}

void delete_str_with_max(node_t **head)
{
    node_t *cur = *head;
    int max_elem = 0;
    size_t max_row = 0;
    
    while (cur != NULL)
    {
        matrix_elem_t *elem = cur->data;
        if (elem->value > max_elem)
        {
            max_row = elem->row;
            max_elem = elem->value;
        }
        cur = cur->next;
    }

    cur = *head;
    node_t *prev = NULL; 

    while (cur != NULL)
    {
        matrix_elem_t *elem = cur->data;
        if (elem->row == max_row)
        {
            node_t *tmp = cur;
            cur = cur->next;

            if (prev == NULL) 
                *head = cur; 
            else
                prev->next = cur;
            node_free(tmp);
        }
        else
        {
            prev = cur; 
            cur = cur->next;
        }
    }
}

int out(void)
{
    node_t *first;
    int rc = init_matrix_list(&first);
    if (rc != OK)
    {
        list_free(first);
        return rc;
    }

    print_elem_list(stdout, first);
    list_free(first);
    return OK;
}

int add(void)
{
    node_t *first;
    node_t *second;
    int rc = init_matrix_list(&first);
    if (rc != OK)
    {
        list_free(first);
        return rc;
    }
    rc = init_matrix_list(&second);
    if (rc != OK)
    {
        list_free(first);
        list_free(second);
        return rc;
    }
    node_t *res = NULL;
    rc = add_matrix(first, second, &res);
    if (rc != OK)
    {
        list_free(first);
        list_free(second);
        list_free(res);
        return rc;
    }
    print_elem_list(stdout, res);

    if (first != NULL)
        list_free(first);
    if (second != NULL)
        list_free(second);
    if (res != NULL)
        list_free(res);
    return OK;
}

int mul(void)
{
    node_t *first;
    node_t *second;
    int rc = init_matrix_list(&first);
    if (rc != OK)
    {
        list_free(first);
        return rc;
    }
    rc = init_matrix_list(&second);
    if (rc != OK)
    {
        list_free(first);
        list_free(second);
        return rc;
    }
    node_t *res = NULL;
    rc = matrix_multiply(first, second, &res);
    if (rc != OK)
    {
        list_free(first);
        list_free(second);
        list_free(res);
        return rc;
    }
    print_elem_list(stdout, res);

    list_free(first);
    list_free(second);
    list_free(res);
    return OK;
}

int lin(void)
{
    node_t *first;
    int rc = init_matrix_list(&first);
    if (rc != OK)
    {
        list_free(first);
        return rc;
    }
    delete_str_with_max(&first);
    print_elem_list(stdout, first);

    list_free(first);
    return OK;
}
