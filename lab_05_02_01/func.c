#include "func.h"


int calc_arifm_mean_of_max_min(char *file_path, double *avr)
{
    FILE *f = fopen(file_path, "r");
    if (f == NULL)
        return ERROR_IO;
    double max, min;
    if (fscanf(f, "%lf", &min) == 1)
    {
        double cur;
        max = min;
        while (fscanf(f, "%lf", &cur) == 1)
        {
            if (cur > max)
                max = cur;
            else if (cur < min)
                min = cur;
        }
        *avr = (min + max) / 2;
        fclose(f);
        return OK;
    }
    fclose(f);
    return ERROR_NO_NUM;
}

int count_numb_gt(char *file_path, double num, int *count)
{
    int cur_count = 0;
    FILE *f = fopen(file_path, "r");
    if (f == NULL)
        return ERROR_IO;
    double cur;
    if (fscanf(f, "%lf", &cur) == 1)
    {
        if (cur > num)
            cur_count++;
        while (fscanf(f, "%lf", &cur) == 1)
        {
            if (cur > num)
                cur_count++;
        }
        *count = cur_count;
        fclose(f);
        return OK;
    }
    fclose(f);
    return ERROR_NO_NUM;
}
