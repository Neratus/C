#ifndef COUNTRY_H
#define COUNTRY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

#define BASIC_ALLOC 2
#define ALLOC_INCR 2

#define ERROR_STR_INPUT -1
#define ERROR_WRONG_ARG_VAL -3
#define ERROR_UNABLE_TO_READ_NUMS -4
#define ERROR_NUM_VALUE -5
#define ERROR_FILE_PATH -6
#define ERROR_MALLOC -7
#define ERROR_FILE_INPUT -8

#define OK 0

typedef struct 
{
    char *name;
    char *capital;
    double gdp;
    int population;
} country_t;

int read_country(FILE *f, country_t *country);

void print_country(FILE *f, const void *country_ptr);

void free_countries(country_t *countries, size_t list_cnt);

int compar_countries(const void *first, const void *second);

int read_countries(char *path_to_file, country_t **countries, size_t *list_cnt);

#endif
