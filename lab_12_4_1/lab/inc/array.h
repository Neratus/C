#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR_FILE -1
#define ERROR_EMPTY -2
#define ERROR_NOT_NUM -3
#define ERROR_MALLOC -4
#define ERROR_NO_ELEM -5
#define ERROR_NO_ACCEPTABLE_NUMS -6


int cnt_file_nums(char *file);

int fill_array(char *file, int **pb, int **pe);

int get_int_array(char *file, int **pb, int **pe);

int print_int_array(char *file, int *pb, int *pe);

void mysort (void *base, size_t number, size_t width, int (*compar)(const void *, const void *));

int compare_int(const void *arg1, const void *arg2);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif
