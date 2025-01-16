#include "array.h"

int cnt_file_nums(char *file)
{
    FILE *f = fopen(file, "r");
    if (f == NULL)
        return ERROR_FILE;

    int cnt = 0;
    int elem = 0;
    while (fscanf(f, "%d", &elem) == 1)
        cnt++;

    if (!feof(f))
    {
        fclose(f);
        return ERROR_NOT_NUM;
    }

    fclose(f);
    if (cnt == 0)
        return ERROR_EMPTY;
    return cnt;
} 

int fill_array(char *file, int **pb, int **pe)
{
    int *cur = *pb;
    int elem = 0;
    *pe = *pb;

    FILE *f = fopen(file, "r");
    if (f == NULL)
        return ERROR_FILE;

    while (fscanf(f, "%d", &elem) == 1)
        *cur++ = elem;

    if (!feof(f))
    {
        fclose(f);
        return ERROR_NOT_NUM;
    }

    *pe = cur;
    fclose(f);
    return OK;
}

int get_int_array(char *file, int **pb, int **pe)
{
    int rc = cnt_file_nums(file);
    if (rc <= 0)
        return rc;

    int cnt = rc;
    *pb = malloc(sizeof(int) * cnt);
    if (*pb == NULL)
        return ERROR_MALLOC;

    rc = fill_array(file, pb, pe);
    return rc;
}

int print_int_array(char *file, int *pb, int *pe)
{
    FILE *f = fopen(file, "w");
    if (f == NULL)
        return ERROR_FILE;

    for (int *cur = pb; cur < pe; cur++)
        fprintf(f, "%d ", *cur);

    return OK;
}

static int calc_aver(const int *pb, const int *pe, double *aver)
{
    if (pb == pe)
        return ERROR_NO_ELEM;

    double sum = 0;
    int len = 0;
    for (const int *cur = pb; cur < pe; cur++)
    {
        sum += *cur;
        len++;
    }

    *aver = sum / len;
    return OK;
}

static int count_nums_gt(const int *pb, const int *pe, double num, size_t *cnt)
{
    size_t count = 0;
    for (const int *cur = pb; cur < pe; cur++)
    {
        if (*cur > num)
            count++;
    }

    if (count == 0)
        return ERROR_NO_ACCEPTABLE_NUMS;

    *cnt = count;
    return OK;
}

static void filter_above(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst, double num)
{
    int *write = *pb_dst;

    for (const int *cur = pb_src; cur < pe_src; cur++)
    {
        if (*cur > num)
            *write++ = *cur;
    }

    *pe_dst = write;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    double aver;
    size_t cnt;

    int rc = calc_aver(pb_src, pe_src, &aver);
    if (rc != 0)
        return rc;

    rc = count_nums_gt(pb_src, pe_src, aver, &cnt);
    if (rc != 0)
        return rc;

    *pb_dst = malloc(sizeof(int) * cnt);
    if (*pb_dst == NULL)
        return ERROR_MALLOC;

    filter_above(pb_src, pe_src, pb_dst, pe_dst, aver);
    return OK;
} 


int compare_int(const void *arg1, const void *arg2)
{
    const int *first = arg1;
    const int *second = arg2;

    return *first - *second;
}

static void swap(void *arg1, void *arg2, size_t elem_size)
{
    char *first = arg1, *second = arg2;
    char tmp;
    
    for (size_t i = 0; i < elem_size; i++)
    {
        tmp = *first;
        *first = *second;
        *second = tmp;
        first++;
        second++;
    }
}

void mysort (void *base, size_t number, size_t width, int (*compar)(const void *, const void *))
{
    char *pbeg = base;
    char *pend = pbeg + number * width;
    for (char *i = pbeg + width; i < pend; i += width)
    {
        for (char *j = i;((j > pbeg) && (compar(j - width, j) > 0)); j -= width)
            swap(j - width, j, width);
    }
}
