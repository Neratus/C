#include "names.h"

#define ERROR_WRONG_ARG -1

int main(int argc, char **argv)
{
    if (argc != 3)
        return ERROR_WRONG_ARG;

    name_t *name_arr = NULL;
    size_t cnt = 0;

    int rc = read_names_from_file(argv[1], &name_arr, &cnt);
    if (rc != OK)
        return rc;
    
    qsort(name_arr, cnt, sizeof(name_t), compar_names);

    rc = print_names(argv[2], name_arr, cnt);
    if (rc != OK)
        return rc;
        
    free_names(name_arr, cnt);
    return OK;
}
