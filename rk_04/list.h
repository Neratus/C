#ifndef LIST_H
#define LIST_H

#define _GNU_SOURCE
#include <stdlib.h>

#define ERROR_MALLOC -2
#define ERROR_FILE -3

#define OK 0

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

void print_list(char *file, node_t *head);

void free_list(node_t *head);

int init_list(char *file_path, node_t **node);

void split_list(node_t **head);

#endif
