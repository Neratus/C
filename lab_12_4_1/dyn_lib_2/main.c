#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERROR_WRONG_ARG_CNT 1
#define ERROR_LIBRARY 2

int main(int argc, char **argv)
{
    if (!((argc == 3) || ((argc == 4) && (strcmp(argv[3], "f") == 0))))
        return ERROR_WRONG_ARG_CNT;

    void* hlibarr;
    hlibarr = dlopen("./libarr.so", RTLD_NOW);
    if (hlibarr == NULL)
        return ERROR_LIBRARY;

    int (*get_int_array)(const char*, int**, int**) = (int (*)(const char*, int**, int**)) dlsym(hlibarr, "get_int_array");
    int (*key)(int*, int*, int**, int**) = (int (*)(int*, int*, int**, int**)) dlsym(hlibarr, "key");
    int (*mysort)(int*, size_t, size_t, int (*)(const void*, const void*)) = (int (*)(int*, size_t, size_t, int (*)(const void*, const void*))) dlsym(hlibarr, "mysort");
    void (*print_int_array)(const char*, int*, int*) = (void (*)(const char*, int*, int*)) dlsym(hlibarr, "print_int_array");
    int (*compare_int)(const void*, const void*) = (int (*)(const void*, const void*)) dlsym(hlibarr, "compare_int");

    if (!get_int_array || !key || !mysort || !print_int_array || !compare_int)
    {
        dlclose(hlibarr);
        return ERROR_LIBRARY;
    }

    int rc = 0;
    int *pb, *pe;
    rc = get_int_array(argv[1], &pb, &pe);
    if (rc != OK)
    {
        dlclose(hlibarr);
        return rc;
    }
    if (argc == 4)
    {
        int *new_pb = malloc(sizeof(int) * (pe - pb));
        int *new_pe;
        rc = key(pb, pe, &new_pb, &new_pe);
        free(pb);
        if (rc != 0)
        {
            free(new_pb);
            dlclose(hlibarr);
            return rc;
        }
        pb = new_pb;
        pe = new_pe;
    }
    mysort(pb, pe - pb, sizeof(int), compare_int);
    print_int_array(argv[2], pb, pe);
    dlclose(hlibarr);
    free(pb);
    return OK;
}
