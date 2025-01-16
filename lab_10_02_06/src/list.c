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
    return node;
}

void node_free(node_t *node)
{
    free(node->data);
    free(node);
}

void node_print(FILE *f, node_t *node, void (*print)(FILE*, const void*))
{
    print(f, node->data);
}

node_t *list_add_tail(node_t *head, node_t *node)
{
    if (head == NULL)
        return node;
    node_t *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
    return head;
}

void print_list(FILE *f, node_t *head, void (*print)(FILE*, const void*))
{
    node_t *tmp = head;
    while (tmp != NULL)
    {
        node_print(f, tmp, print);
        tmp = tmp->next;
    }
}

void list_free(node_t *head)
{
    node_t *tmp = head;
    node_t *next; 
    while (tmp != NULL)
    {
        next = tmp->next;
        node_free(tmp);
        tmp = next;
    }
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*))
{
    node_t *cur = head;
    while (cur != NULL)
    {
        if (comparator(data, cur->data) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}
