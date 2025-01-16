#include "func.h"


int fill_binary(char *file_path, size_t num_count)
{
    FILE *f = fopen(file_path, "wb");
    if (f == NULL)
        return ERROR_IO;
    int cur;
    for (size_t i = 0; i < num_count; i++)
    {
        cur = rand();
        if (fwrite(&cur, sizeof(int), 1, f) != 1)
        {
            fclose(f);
            return ERROR_IO;
        }
    }
    fclose(f);
    return OK;
}

int count_file_nums(FILE *f, size_t *size)
{
    unsigned long sz;
    if (fseek(f, 0, SEEK_END))
        return ERROR_IO;
    sz = ftell(f);
    if (sz < sizeof(int))
        return ERROR_IO;
    *size = sz / sizeof(int);
    return fseek(f, 0, SEEK_SET);
}


int print_binary(char *file_path)
{
    int num;
    FILE *f = fopen(file_path, "rb");
    if (f == NULL)
        return ERROR_IO;
    size_t file_size;
    int rc = count_file_nums(f, &file_size);
    if (rc == ERROR_IO)
    {
        fclose(f);
        return ERROR_IO;
    }
    for (size_t i = 0; i < file_size; i++)
    {
        size_t read = fread(&num, sizeof(int), 1, f);
        if (read == 1)
            printf("%d ", num);
        else
        {
            fclose(f);
            return ERROR_IO; 
        }
    }
    fclose(f);
    printf("\n");
    return 0;
}

int get_number_by_pos(FILE *f, size_t pos, int *num)
{
    int rc = fseek(f, pos * sizeof(int), SEEK_SET);
    if (!rc)
    {
        if (fread(num, sizeof(int), 1, f) != 1)
            return ERROR_IO;
        return OK;
    }
    return ERROR_INDEX_OUT_OF_RANGE;
}

int put_number_by_pos(FILE *f, size_t pos, int num)
{
    int rc = fseek(f, pos * sizeof(int), SEEK_SET);
    if (!rc)
    {
        if (fwrite(&num, sizeof(int), 1, f) != 1)
            return ERROR_IO;
        return OK;
    }
    return ERROR_INDEX_OUT_OF_RANGE;
}

int sort_binary(char *file_path)
{
    FILE *f = fopen(file_path, "rb+");
    if (f == NULL)
        return ERROR_IO;
    size_t size_of_array;
    int rc = count_file_nums(f, &size_of_array);
    if (rc == ERROR_IO)
    {   
        fclose(f);
        return ERROR_IO;
    }
    int tmp;
    for (size_t step = size_of_array / 2; step > 0; step /= 2) 
    {
        for (size_t i = step; i < size_of_array; i++)
        {
            rc = get_number_by_pos(f, i, &tmp);
            int found = 1;  
            size_t j = i;
            while (j >= step && found) 
            {
                int cur;
                rc = get_number_by_pos(f, j - step, &cur);
                if (tmp < cur) 
                {
                    rc = put_number_by_pos(f, j, cur);
                    j -= step;
                } 
                else
                    found = 0;
            }
            rc = put_number_by_pos(f, j, tmp);
            if (rc != OK)
            {
                fclose(f);
                return rc;
            }
        }
    }
    fclose(f);
    return OK;
}
