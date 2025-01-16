#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct node node_t;

struct node
{
    void *data;
    node_t *prev;
    node_t *next;
};

typedef struct
{
    node_t *head;
    node_t *tail;
} list_t;

node_t *node_create(void *data);

list_t *list_init(void);

int list_is_empty(list_t *list);

void list_print(FILE *f, list_t *list, void (*print)(FILE*, const void*));

void list_free(list_t *list, void (*free_data)(void*));

void list_make_empty(list_t *list, void (*free_data)(void*));

list_t *list_add_tail(list_t *list, void *data);

list_t *list_remove(list_t *list, const void *data, int (*comparator)(const void*, const void*), void (*free_data)(void*));

node_t *list_find(list_t *list, const void *data, int (*comparator)(const void*, const void*));

node_t *list_find_min(list_t *list, int (*comparator)(const void*, const void*));

node_t *list_find_max(list_t *list, int (*comparator)(const void*, const void*));

#endif
