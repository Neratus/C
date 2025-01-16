#include <stdio.h>
#include <stdlib.h>
#include "list.h"

node_t *node_create(void *data)
{
    node_t *node;
    node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void node_free(node_t *node, void (*free_data)(void*))
{
    if (free_data != NULL)
        free_data(node->data);
    free(node);
}

void node_print(FILE *f, node_t *node, void (*print)(FILE*, const void*))
{
    print(f, node->data);
}

list_t *list_init(void)
{
    list_t *list = malloc(sizeof(list_t));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int list_is_empty(list_t *list)
{
    return !list || !list->head || !list->tail;
}

void list_print(FILE *f, list_t *list, void (*print)(FILE*, const void*))
{
    for (node_t *tmp = list->head; tmp != NULL; tmp = tmp->next)
        node_print(f, tmp, print);
}

void list_free(list_t *list, void (*free_data)(void*))
{
    node_t *next;
    for (node_t *curr = list->head; curr != NULL;)
    {
        next = curr->next;
        node_free(curr, free_data);
        curr = next;
    }
    list->head = NULL;
    list->tail = NULL;
    free(list);
}

void list_make_empty(list_t *list, void (*free_data)(void*))
{
    node_t *next;
    for (node_t *curr = list->head; curr != NULL;)
    {
        next = curr->next;
        node_free(curr, free_data);
        curr = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

list_t *list_add_tail(list_t *list, void *data)
{
    if (list == NULL)
        return NULL;
    node_t *cur = node_create((void*)data);
    if (cur == NULL)
        return NULL;
    if (list_is_empty(list))
    {
        list->head = cur;
        list->tail = cur;
    }
    else
    {
        list->tail->next = cur;
        cur->prev = list->tail;
        list->tail = cur;
    }
    return list;
}

list_t *list_remove(list_t *list, const void *data, int (*comparator)(const void*, const void*), void (*free_data)(void*))
{
    node_t *tmp = list->head;
    node_t *next;
    while (tmp != NULL) 
    {
        next = tmp->next;
        if (comparator(tmp->data, data) == 0) 
        {  
            if (tmp->prev != NULL) 
                tmp->prev->next = tmp->next;  
            else 
                list->head = tmp->next;
            
            if (tmp->next != NULL) 
                tmp->next->prev = tmp->prev;  
            else 
                list->tail = tmp->prev;

            node_free(tmp, free_data);  
        }
        tmp = next;
    }
    return list;
}

node_t *list_find(list_t *list, const void *data, int (*comparator)(const void*, const void*))
{
    for (node_t *cur = list->head;cur != NULL; cur = cur->next)
    {
        if (comparator(cur->data, data) == 0)
            return cur;
    }
    return NULL;
}

node_t *list_find_min(list_t *list, int (*comparator)(const void*, const void*))
{
    node_t *res = list->head;
    for (node_t *cur = list->head;cur != NULL; cur = cur->next)
    {
        if (comparator(cur->data, res->data) < 0)
            res = cur;
    }
    return res;
}

node_t *list_find_max(list_t *list, int (*comparator)(const void*, const void*))
{
    node_t *res = list->head;
    for (node_t *cur = list->head;cur != NULL; cur = cur->next)
    {
        if (comparator(cur->data, res->data) > 0)
            res = cur;
    }
    return res;
}
