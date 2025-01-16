#ifndef PRODUCT_H
#define PRODUCT_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>

#define EPS -1e-5

#define ERROR_STR_INPUT -1
#define ERROR_WRONG_ARG_VAL -3
#define ERROR_UNABLE_TO_READ_NUMS -4
#define ERROR_PRICE_VALUE -5
#define ERROR_FILE_PATH -6
#define ERROR_MALLOC -7
#define ERROR_FILE_INPUT -8

#define OK 0
#define MATR_INCR 2
#define MATR_ALLOC 2

typedef struct 
{
    char *name;
    int price;
} product_t;

int read_product(FILE *f, product_t *prod);

void free_products(product_t *products, int cnt);

void print_product(FILE *f, const product_t *prod);

int read_products(char *path_to_file, product_t **products, size_t *prod_cnt);

void print_products_cheaper(product_t *products, size_t prod_cnt, double price);

#endif
