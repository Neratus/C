#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>

#define OK 0
#define ERROR_IO -2
#define ERROR_NO_NUM -3


int calc_arifm_mean_of_max_min(char *file_path, double *avr);

int count_numb_gt(char *file_path, double num, int *count);

#endif
