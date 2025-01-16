#include "student_bin.h"
#include "convert.h"


#define ERROR_WRONG_ARG 53
#define ERROR_NEGATIVE_NUM 5

int main(int argc, char **argv) 
{
    int rc = 0;
    if ((argc == 4) && (strcmp("export", argv[1]) == 0))
    {
        rc = export(argv[2], argv[3]);
        if (rc == ERROR_IO)
        {
            printf("ERROR: error while opening file \n");
            return rc;
        }
        return OK;
    }
    if ((argc == 4) && (strcmp("import", argv[1]) == 0))
    {
        rc = import(argv[2], argv[3]);
        if (rc == ERROR_IO)
        {
            printf("ERROR: error while opening file \n");
            return rc;
        }
        if (rc == ERROR_WRONG_STR_LEN)
        {
            printf("ERROR: wrong length of string in file \n");
            return rc;
        }
        return OK;
    }
    if ((argc == 3) && (strcmp("sb", argv[1]) == 0))
    {
        rc = sort_students(argv[2]);
        if (rc == ERROR_IO)
        {
            printf("ERROR: error while opening file \n");
            return rc;
        }
        if (rc == ERROR_INDEX_OUT_OF_RANGE)
        {
            printf("ERROR: trying to access an invalid index \n");
            return rc;
        }
        return OK;
    }
    if ((argc == 5) && (strcmp("fb", argv[1]) == 0))
    {
        rc = filter_students(argv[2], argv[3], argv[4]);
        if (rc == ERROR_IO)
        {
            printf("ERROR: error while opening file \n");
            return rc;
        }
        if (rc == ERROR_INVALID_SUBSTRING)
        {
            printf("ERROR: invalid length of given substring \n");
            return rc;
        }
        if (rc == ERROR_NO_ACCEPTABLE_SUR)
        {
            printf("ERROR: no acceptable surname in file \n");
            return rc;
        }
        return OK;
    }
    if ((argc == 3) && (strcmp("db", argv[1]) == 0))
    {
        double aver;
        rc = get_average_grade(argv[2], &aver);
        if (rc == ERROR_IO)
        {
            printf("ERROR: error while opening file \n");
            return rc;
        }
        if (rc == ERROR_INDEX_OUT_OF_RANGE)
        {
            printf("ERROR: trying to access an invalid index \n");
            return rc;
        }
        rc = delete_low_grade_students(argv[2], aver);
        if (rc == ERROR_IO)
        {
            printf("ERROR: error while opening file \n");
            return rc;
        }
        if (rc == ERROR_INDEX_OUT_OF_RANGE)
        {
            printf("ERROR: trying to access an invalid index \n");
            return rc;
        }
        return OK;
    }
    printf("ERROR: wrong format of given arguments \n");
    return ERROR_WRONG_ARG;
}
