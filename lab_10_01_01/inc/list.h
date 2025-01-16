#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

node_t *node_create(void *data);

node_t *list_add_tail(node_t *head, node_t *node);

void print_list(FILE *f, node_t *head, void (*print)(FILE*, const void*));

void list_free(node_t *head);

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*));

void *pop_front(node_t **head);

void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif
