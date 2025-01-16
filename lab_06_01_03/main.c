#include "products.h"
#include <string.h>
#include <stdlib.h>

#define ERROR_WRONG_ARG -11

int main(int argc, char **argv) 
{
    if (argc != 3)
        return ERROR_WRONG_ARG;
    double targ_price = -1;
    char *pend;
    targ_price = strtof(argv[2], &pend);
    if ((pend == argv[2]) || (targ_price <= 0))
        return ERROR_WRONG_ARG;
    product_t products[MAX_ARR_LEN];
    size_t cnt = 0;
    int rc = read_products(argv[1], products, &cnt);
    if (rc != OK)
        return rc;
    print_products_cheaper(products, cnt, targ_price);
    return OK;
}
