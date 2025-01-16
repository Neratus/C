#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "names.h"

int compar_names(const void *first, const void *second)
{
    const name_t *first_name = first;
    const name_t *second_name = second;
    return strcmp(first_name->name, second_name->name);
}

void free_names(name_t *name_arr, size_t cnt)
{
    for (size_t i = 0; i < cnt; i++)
        free(name_arr[i].name);
    free(name_arr);
}

int read_names_from_file(char *file_path, name_t **name_arr, size_t *cnt)
{
    FILE *f = fopen(file_path, "r");
    if (f == NULL)
        return ERROR_FILE;

    size_t alloc = 2;
    size_t cur = 0;
    *name_arr = malloc(sizeof(name_t) * alloc);
    if (*name_arr == NULL) 
    { 
        fclose(f);
        return ERROR_MALLOC;
    }

    char *name = NULL;
    size_t len = 0;
    while(getline(&name, &len, f) != -1)
    {
        name[strcspn(name, "\n")] = 0;

        if (cur >= alloc)
        {
            alloc *= 2;
            name_t *temp = realloc(*name_arr, sizeof(name_t) * alloc);
            if (temp == NULL)
            {
                free_names(*name_arr, cur);
                free(name);
                fclose(f);
                return ERROR_MALLOC;
            }
            *name_arr = temp;
        }

        int unique = -1;
        for (size_t i = 0; i < cur; i++)
        {
            if (strcmp(name, (*name_arr)[i].name) == 0)
            {
                (*name_arr)[i].name_cnt++;
                unique = 1;
                break;
            }
        }
        if (unique == -1)
        {
            (*name_arr)[cur].name = strdup(name);
            if ((*name_arr)[cur].name == NULL)
            {
                free_names(*name_arr, cur);
                free(name);
                fclose(f);
                return ERROR_MALLOC;
            }

            (*name_arr)[cur].name_cnt = 1;
            cur++;
        }
    }
    free(name);
    fclose(f);
    *cnt = cur;
    return OK;
}

int print_names(char *file_path, name_t *name_arr, size_t cnt)
{
    FILE *f = fopen(file_path, "w");
    if (f == NULL)
        return ERROR_FILE;
    for (size_t i = 0; i < cnt; i++)
        fprintf(f, "%s : %zu \n", name_arr[i].name, name_arr[i].name_cnt);
    fclose(f);
    return OK;
}
