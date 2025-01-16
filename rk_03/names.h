#ifndef NAMES_H
#define NAMES_H

#define _GNU_SOURCE
#include <stdlib.h>

#define ERROR_FILE -2
#define ERROR_MALLOC -3

#define OK 0

typedef struct
{
    char *name;
    size_t name_cnt;
}name_t;

int compar_names(const void *first, const void *second);

int read_names_from_file(char *file_path, name_t **name_arr, size_t *cnt);

int print_names(char *file_path, name_t *name_arr, size_t cnt);

void free_names(name_t *name_arr, size_t cnt);

#endif
