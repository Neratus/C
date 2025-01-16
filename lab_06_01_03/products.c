#include "products.h"
#include <string.h>
#include <stdlib.h>

int read_line(char *str, size_t str_max, FILE *f)
{
    if (!fgets(str, str_max, f))
        return ERROR_STR_INPUT;
    char *p = strchr(str, '\n');
    if (p)
    {
        *p = 0;
        return OK;
    }
    return ERROR_STR_SIZE;
}

int read_product(FILE *f, product_t *prod)
{
    char str[MAX_NAME_LEN + 1];
    int rc = read_line(str, MAX_NAME_LEN + 1, f);
    if (rc != OK)
        return rc;
    int price = -1;
    if (fscanf(f, "%d ", &price) != 1)
        return ERROR_UNABLE_TO_READ_NUMS;
    if (price < 0)
        return ERROR_PRICE_VALLUE;
    strncpy(prod->name, str, MAX_NAME_LEN);
    prod->price = price;
    return OK;
}

void print_product(const product_t *prod)
{
    printf("%s\n", prod->name);
    printf("%ld\n", prod->price);
}

int read_products(char *path_to_file, product_t products[MAX_ARR_LEN], size_t *prod_cnt)
{ 
    FILE *f = fopen(path_to_file, "r");
    if (f == NULL)
        return ERROR_FILE_PATH;
    int arr_size = 0;
    if (fscanf(f, "%d ", &arr_size) != 1)
        return ERROR_UNABLE_TO_READ_NUMS;
    if (arr_size < 0)
        return ERROR_MIN_FILE_CNT;
    if (arr_size > MAX_ARR_LEN)
        return ERROR_MAX_FILE_CNT;
    int rc;
    for (int i = 0; i < arr_size; i++)
    {
        rc = read_product(f, (products + i));
        if (rc != OK)
        {
            fclose(f);
            return rc;
        }
    }
    fclose(f);
    *prod_cnt = arr_size;
    return OK;
}

void print_products_cheaper(product_t products[MAX_ARR_LEN], size_t prod_cnt, double price)
{
    for (size_t i = 0; i < prod_cnt; i++)
        if ((products[i].price - price) < EPS)
            print_product(&products[i]);
}
