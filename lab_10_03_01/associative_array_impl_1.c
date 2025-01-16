#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "associative_array.h"

struct assoc_array_type
{
    list_t *list;
};

typedef struct
{
    const char *key;
    int val;
} pair_t;

pair_t *pair_create(const char *key, int val)
{
    pair_t *pair;
    pair = malloc(sizeof(pair_t));
    if (pair == NULL)
        return NULL;

    pair->key = key;
    pair->val = val;
    return pair;
}

void pair_free(void *p)
{
    free(p);
}

int pair_cmp(const void *l, const void *r)
{
    const pair_t *l_pair = l, *r_pair = r;
    return strcmp(l_pair->key, r_pair->key);
}

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (arr == NULL)
        return NULL;
    arr->list = list_init();
    if (arr->list == NULL)
    {
        free(arr);
        return NULL;
    }
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if ((arr != NULL) && (*arr != NULL))
    {
        assoc_array_clear(*arr);
        list_free((*arr)->list, pair_free);
        free(*arr);
        *arr = NULL;
    }
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if ((arr == NULL) || (key == NULL) || (key[0] == 0))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    pair_t *pair = pair_create(key, num);
    if (pair == NULL)
        return ASSOC_ARRAY_MEM;
    if (list_find(arr->list, pair, pair_cmp))
    {
        pair_free(pair);
        return ASSOC_ARRAY_KEY_EXISTS;
    }
    list_t *tmp = list_add_tail(arr->list, pair);
    if (tmp != NULL)
    {
        arr->list = tmp;
        return ASSOC_ARRAY_OK;
    }
    else 
    {
        pair_free(pair);
        return ASSOC_ARRAY_MEM;
    }
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if ((arr == NULL) || (key == NULL) || (key[0] == 0) || (num == NULL))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    pair_t *pair = pair_create(key, 0);

    if (pair == NULL)
        return ASSOC_ARRAY_MEM;
    
    node_t *node = list_find(arr->list, pair, pair_cmp);
    pair_free(pair);

    if (node == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &((pair_t *)(node->data))->val;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if ((arr == NULL) || (key == NULL) || (key[0] == 0))
        return ASSOC_ARRAY_INVALID_PARAM;

    pair_t *pair = pair_create(key, 0);
    if (pair == NULL)
        return ASSOC_ARRAY_MEM;
    
    if (!list_find(arr->list, pair, pair_cmp))
    {
        pair_free(pair);
        return ASSOC_ARRAY_NOT_FOUND;
    }
    
    arr->list = list_remove(arr->list, pair, pair_cmp, pair_free);
    pair_free(pair);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    list_make_empty(arr->list, pair_free);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if ((arr == NULL) || (action == NULL))
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *cur = arr->list->head;
    while (cur != NULL)
    {
        action(((pair_t *)(cur->data))->key, &((pair_t *)(cur->data))->val, param);
        cur = cur->next;
    }
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if ((arr == NULL) || (num == NULL))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    if (list_is_empty(arr->list))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *node = list_find_min(arr->list, pair_cmp);
    *num = &((pair_t *)(node->data))->val;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if ((arr == NULL) || (num == NULL))
        return ASSOC_ARRAY_INVALID_PARAM;
    
    if (list_is_empty(arr->list))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *node = list_find_max(arr->list, pair_cmp);
    *num = &((pair_t *)(node->data))->val;

    return ASSOC_ARRAY_OK;
}
