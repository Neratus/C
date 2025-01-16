#include "country_list.h"
#include <string.h>
#include <stdlib.h>

#define ERROR_WRONG_ARG -11

// app.exe s IN_FILE OUT_FILE - сортировка
// app.exe d IN_FILE OUT_FILE - удаление дубл
// app.exe f IN_FILE OUT_FILE NAME - поиск по названию

int main(int argc, char **argv) 
{
    if (argc == 4)
    {
        if (strcmp(argv[1], "s") == 0)
        {
            int rc = func_sort(argv[2], argv[3]);
            return rc;
        }
        if (strcmp(argv[1], "d") == 0)
        {
            int rc = func_delete_dupl(argv[2], argv[3]);
            return rc;
        }
    }
    if (argc == 5)
    {
        int rc = func_find(argv[2], argv[3], argv[4]);
        return rc;
    }
    return ERROR_WRONG_ARG;
}
