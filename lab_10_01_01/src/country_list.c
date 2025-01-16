#include "country_list.h"

int init_country_list_from_array(node_t **head, country_t *country_arr, size_t len)
{
    if (len == 0)
    {
        *head = NULL;
        return OK;
    }
    for (size_t i = 0; i < len; i++)
    {
        node_t *tmp = node_create(&country_arr[i]);
        if (tmp == NULL)
            return ERROR_MALLOC;
        *head = list_add_tail(*head, tmp);
    }
    return OK;
}

node_t *sort_countries_list(node_t *head)
{
    return sort(head, compar_countries);
}

void remove_dupl_countries_list(node_t **head)
{
    remove_duplicates(head, compar_countries);
}

country_t *find_countries_list(node_t *head, country_t *search)
{
    void *data = search;
    node_t *targ = find(head, data, compar_countries);
    if (targ == NULL)
        return NULL;
    return (country_t*)targ->data;
}

country_t *pop_front_countries_list(node_t **head)
{
    return (country_t*)pop_front(head);
}

void print_countries_list(FILE *f, node_t *head)
{
    print_list(f, head, print_country);
}

int func_sort(char *input, char *output)
{
    country_t *countries = NULL;
    node_t *head = NULL;
    size_t cnt = 0;

    int rc = read_countries(input, &countries, &cnt);
    if (rc != OK)
        return rc;

    rc = init_country_list_from_array(&head, countries, cnt);
    if (rc != OK)
        return rc;
            
    head = sort_countries_list(head);

    FILE *out = fopen(output, "w");
    if (out == NULL)
        return ERROR_FILE_PATH;
            
    print_countries_list(out, head);

    fclose(out);
    free_countries(countries, cnt);
    list_free(head);
    return OK;
}

int func_delete_dupl(char *input, char *output)
{
    country_t *countries = NULL;
    node_t *head = NULL;
    size_t cnt = 0;

    int rc = read_countries(input, &countries, &cnt);
    if (rc != OK)
        return rc;

    rc = init_country_list_from_array(&head, countries, cnt);
    if (rc != OK)
        return rc;
            
    remove_dupl_countries_list(&head);

    FILE *out = fopen(output, "w");
    if (out == NULL)
        return ERROR_FILE_PATH;
            
    print_countries_list(out, head);

    fclose(out);
    free_countries(countries, cnt);
    list_free(head);
    return OK;
}

int func_find(char *input, char *output, char *exp)
{
    country_t *countries = NULL;
    node_t *head = NULL;
    size_t cnt = 0;

    int rc = read_countries(input, &countries, &cnt);
    if (rc != OK)
        return rc;

    rc = init_country_list_from_array(&head, countries, cnt);
    if (rc != OK)
        return rc;

    country_t *cur = (country_t *)malloc(sizeof(country_t));
    if (cur == NULL)    
        return ERROR_MALLOC;

    cur->name = exp; 
        
    cur = find_countries_list(head, cur);
    if (cur == NULL)
        return OK;

    FILE *out = fopen(output, "w");
    if (out == NULL)
        return ERROR_NOT_FOUND;
            
    print_country(out, cur);
        
    fclose(out);
    free_countries(countries, cnt);
    list_free(head);
    return OK;
}
