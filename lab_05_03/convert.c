#include "convert.h"


int export(char *file_path_in, char *file_path_out)
{
    FILE *in = fopen(file_path_in, "rb");
    if (in == NULL)
        return ERROR_IO;
    FILE *out = fopen(file_path_out, "w");
    if (out == NULL)
    {
        fclose(in);
        return ERROR_IO;
    }
    int cur;
    while (fread(&cur, sizeof(int), 1, in) == 1)
        fprintf(out, "%d ", cur);
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
    int cur;
    while (fscanf(in, "%d", &cur) == 1)
        if (fwrite(&cur, sizeof(int), 1, out) != 1)
        {
            fclose(in);
            fclose(out);
            return ERROR_IO;
        }
    fclose(in);
    fclose(out);
    return OK;
}
