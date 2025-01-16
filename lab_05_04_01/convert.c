#include "convert.h"

int export(char *file_path_in, char *file_path_out)
{
    student_t s;
    FILE *in = fopen(file_path_in, "rb");
    if (in == NULL)
        return ERROR_IO;
    FILE *out = fopen(file_path_out, "w");
    if (out == NULL)
    {
        fclose(in);
        return ERROR_IO;
    }
    while (fread(&s, sizeof(student_t), 1, in) == 1)
        print_student(out, &s);
    fclose(in);
    fclose(out);
    return OK;
}


int import(char *file_path_in, char *file_path_out)
{
    FILE *in = fopen(file_path_in, "r");
    if (in == NULL)
        return ERROR_IO;
    FILE *out = fopen(file_path_out, "wb");
    if (out == NULL)
    {
        fclose(in);
        return ERROR_IO;
    }
    student_t s = { "a", "a", { 1, 2, 3, 4 } };
    int rc = read_student(in, &s);
    while (rc == OK)
    {
        if (fwrite(&s, sizeof(student_t), 1, out) != 1)
        {
            fclose(in);
            fclose(out);
            return ERROR_IO;
        }
        rc = read_student(in, &s);
    }
    fclose(in);
    fclose(out);
    if (rc == ERROR_WRONG_STR_LEN)
        return rc;
    return OK;
}
