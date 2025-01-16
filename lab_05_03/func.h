#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define OK 0
#define ERROR_IO -3
#define ERROR_NO_NUM -4
#define ERROR_INDEX_OUT_OF_RANGE -5

int fill_binary(char *file_path, size_t num_count);

int print_binary(char *file_path);

int get_number_by_pos(FILE *f, size_t pos, int *num);

int put_number_by_pos(FILE *f, size_t pos, int num);

int sort_binary(char *file_path);

#endif
