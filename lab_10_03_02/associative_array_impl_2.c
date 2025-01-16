#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "associative_array.h"

struct assoc_array_type
{
    hash_table_t *hash_table;
};

assoc_array_t assoc_array_create(void) 
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (arr == NULL) 
        return NULL;
    arr->hash_table = malloc(sizeof(hash_table_t));
    if (arr->hash_table == NULL)
    {
        free(arr);
        return NULL;
    }

    init_closed_hash_table(arr->hash_table, NULL);   
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr) 
{
    if (arr && *arr) 
    { 
        free_closed_table((*arr)->hash_table);
        free(*arr);  
        *arr = NULL;
    }
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num) 
{
    if ((arr == NULL) || (key == NULL) || (key[0] == 0))
        return ASSOC_ARRAY_INVALID_PARAM;

    int result = add_elem_to_table(&arr->hash_table, key, num); 
    if (result == ERROR_KEY_EXISTS) 
        return ASSOC_ARRAY_KEY_EXISTS;
    else if (result == ERROR_MEMORY)
        return ASSOC_ARRAY_MEM;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num) 
{
    if (!arr || !key || !num || strlen(key) == 0) 
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *node = find_node(arr->hash_table, key);  
    if (node) 
    {
        *num = &node->val; 
        return ASSOC_ARRAY_OK;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key) 
{
    if (!arr || !key || strlen(key) == 0) 
        return ASSOC_ARRAY_INVALID_PARAM;

    int result = delete_elem_from_table(arr->hash_table, key); 
    if (result == 0) 
        return ASSOC_ARRAY_OK;

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr) 
{
    if (!arr) 
        return ASSOC_ARRAY_INVALID_PARAM;

    int size = arr->hash_table->table_size;
    free_closed_table(arr->hash_table); 

    arr->hash_table = malloc(sizeof(hash_table_t)); 
    if (!arr->hash_table)
        return ASSOC_ARRAY_MEM;  

    init_closed_hash_table(arr->hash_table, &size);  
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param) 
{
    if (!arr || !action) 
        return ASSOC_ARRAY_INVALID_PARAM;

    for (int i = 0; i < arr->hash_table->table_size; i++) 
    {
        node_t *node = arr->hash_table->table[i];
        while (node) 
        {
            action(node->key, &node->val, param);
            node = node->next;
        }
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num) 
{
    if (!arr || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *min_node = find_min_node(arr->hash_table);
    if (min_node) 
    {
        *num = &min_node->val;
        return ASSOC_ARRAY_OK;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num) 
{
    if (!arr || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *max_node = find_max_node(arr->hash_table);
    if (max_node) 
    {
        *num = &max_node->val;
        return ASSOC_ARRAY_OK;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}
