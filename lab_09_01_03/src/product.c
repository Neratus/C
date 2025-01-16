#include "product.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

int read_product(FILE *f, product_t *prod)
{
    char *str = NULL;
    size_t len = 0;

    if (getline(&str, &len, f) == -1) 
    {
        free(str);
        return ERROR_STR_INPUT;
    }

    str[strlen(str) - 1] = 0;

    int price = -1;
    if (fscanf(f, "%d ", &price) != 1)
    {
        free(str);
        return ERROR_UNABLE_TO_READ_NUMS;
    }

    if (price < 0)
    {   
        free(str);
        return ERROR_PRICE_VALUE;
    }

    prod->name = str;
    prod->price = price;
    return OK;
}

void free_products(product_t *products, int cnt)
{
    for (int i = 0; i < cnt; i++)
        free(products[i].name); 
    free(products);
}

void print_product(FILE *f, const product_t *prod)
{
    fprintf(f, "%s\n%d\n", prod->name, prod->price);
}

int read_products(char *path_to_file, product_t **products, size_t *prod_cnt)
{ 
    FILE *f = fopen(path_to_file, "r");
    if (f == NULL)
        return ERROR_FILE_PATH;

    int arr_size = 0;
    int list_size = 0;
    int allocated = MATR_ALLOC;

    *products = malloc(sizeof(product_t) * allocated);
    if (*products == NULL)
    {
        fclose(f);
        return ERROR_MALLOC;
    }

    if (fscanf(f, "%d \n", &arr_size) != 1)
    {
        free(*products);
        fclose(f);
        return ERROR_UNABLE_TO_READ_NUMS;
    }

    int rc;
    while ((rc = read_product(f, &(*products)[list_size])) == OK)
    {
        list_size++;
        
        if (list_size == allocated)
        {
            allocated *= MATR_INCR;
            product_t *new_products = realloc(*products, sizeof(product_t) * allocated);

            if (new_products == NULL)
            {
                free_products(*products, list_size);
                fclose(f);
                return ERROR_MALLOC;
            }

            *products = new_products;
        }
    }
    fclose(f);
    
    if ((rc != ERROR_STR_INPUT) && (rc != OK))
    {
        free_products(*products, list_size);
        return rc; 
    }

    *prod_cnt = list_size;
    return OK;
}

bool is_cheaper(product_t item, void *extra)
{
    double *price = (double*) extra;
    if ((item.price - *price) < EPS)
        return true;
    return false;
}

static void print_product_by_filter(product_t *products, size_t prod_cnt, void *extra, bool filter(product_t item, void *extra))
{
    for (size_t i = 0; i < prod_cnt; i++)
        if (filter(products[i], extra))
            print_product(stdout, &products[i]);
}


void print_products_cheaper(product_t *products, size_t prod_cnt, double price)
{
    print_product_by_filter(products, prod_cnt, (void*)&price, is_cheaper);
}
