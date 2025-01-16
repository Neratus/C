#include "array.h"
#include <stdio.h>
#include <string.h>

#define ERROR_WRONG_ARG_CNT 1

int main(int argc, char **argv)
{
    int rc = 0;
    if (!((argc == 3) || ((argc == 4) && (strcmp(argv[3], "f") == 0))))
        return ERROR_WRONG_ARG_CNT;
    int *pb, *pe;
    rc = get_int_array(argv[1], &pb, &pe);
    if (rc != OK)
        return rc;
    if (argc == 4)
    {
        int *new_pb = malloc(sizeof(int) * (pe - pb));
        int *new_pe;
        rc = key(pb, pe, &new_pb, &new_pe);
        free(pb);
        if (rc != 0)
        {
            free(new_pb);
            return rc;
        }
        pb = new_pb;
        pe = new_pe;
    }
    mysort(pb, pe - pb, sizeof(int), compare_int);
    print_int_array(argv[2], pb, pe);
    free(pb);
    return OK;
}
