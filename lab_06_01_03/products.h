#ifndef PRODS_H
#define PRODS_H

#include <stdio.h>

#define MAX_ARR_LEN 15
#define EPS -1e-5
#define MAX_NAME_LEN 25

#define ERROR_STR_INPUT -1
#define ERROR_STR_SIZE -2
#define ERROR_WRONG_ARG_VAL -3
#define ERROR_UNABLE_TO_READ_NUMS -4
#define ERROR_PRICE_VALLUE -5
#define ERROR_FILE_PATH -6
#define ERROR_MAX_FILE_CNT -7
#define ERROR_MIN_FILE_CNT -8
#define ERROR_NO_CNT -9
#define NO_CHEAPER_PRODUCTS -10

#define OK 0

typedef struct 
{
    char name[MAX_NAME_LEN + 1];
    size_t price;
}product_t;

int read_product(FILE *f, product_t *prod);

void print_product(const product_t *prod);

int read_products(char *path_to_file, product_t products[MAX_ARR_LEN], size_t *prod_cnt);

void print_products_cheaper(product_t products[MAX_ARR_LEN], size_t prod_cnt, double price);

#endif
