#ifndef FILM_LIST_H
#define FILM_LIST_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

#include "list.h"

#define ERROR_STR_INPUT -1
#define ERROR_WRONG_ARG_VAL -2
#define ERROR_SIZE_INPUT -3
#define ERROR_SIZE_VALUE -4
#define ERROR_ELEM_INPUT -5

#define ERROR_NUM_VALUE -5
#define ERROR_MALLOC -7
#define ERROR_FILE_INPUT -8

#define OK 0

typedef struct
{
    size_t row;
    size_t col;
    int value;
}matrix_elem_t;

void print_elem_list(FILE *f, node_t *head);

int init_matrix_list(node_t **head);

int add_matrix(node_t *first, node_t *second, node_t **res);

int matrix_multiply(node_t *first, node_t *second, node_t **res);

void delete_str_with_max(node_t **head);

int out(void);

int add(void);

int mul(void);

int lin(void);

#endif
