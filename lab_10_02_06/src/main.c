#include "matrix_list.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#define _GNU_SOURCE

#define ERROR_WRONG_ARG -11

int main(void) 
{
    char *str = NULL;
    size_t len = 0;
    if (getline(&str, &len, stdin) == -1) 
    {
        free(str);
        return ERROR_STR_INPUT;
    }
    str[strcspn(str, "\n")] = 0;
    
    if (strcmp("out", str) == 0)
    {
        int rc = out();
        free(str);
        return rc;
    }
    if (strcmp("add", str) == 0)
    {
        int rc = add();
        free(str);
        return rc;
    }
    if (strcmp("mul", str) == 0)
    {
        int rc = mul();
        free(str);
        return rc;
    }
    if (strcmp("lin", str) == 0)
    {
        int rc = lin();
        free(str);
        return rc;
    }
    free(str);
    return ERROR_WRONG_ARG;
}
