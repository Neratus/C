#ifndef STRFUNC_H
#define STRFUNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define STR_MAX_LEN 256
#define WORD_MAX_LEN 16
#define WORD_MAX_CNT (STR_MAX_LEN/2)
#define ERROR_STR_INPUT -1
#define ERROR_STR_SIZE -2
#define NOT_VALID_DATE -3
#define VALID_DATE 0

int read_line(char *str, size_t str_max);

void trim(char line[STR_MAX_LEN+1]);

int valid_month(char *str_month);

int check_date_value(long date, long month, long year);

int split_str(char *str, char words[][STR_MAX_LEN + 1], size_t *words_cnt);

int check_line_correct_date(char line[STR_MAX_LEN+1]);

#endif
