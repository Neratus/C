#ifndef STRFUNC_H
#define STRFUNC_H

#include <stdio.h>
#include <string.h>

#define STR_MAX_LEN 256
#define WORD_MAX_LEN 16
#define WORD_MAX_CNT (STR_MAX_LEN/2)
#define ERROR_STR_INPUT -1
#define ERROR_STR_SIZE -2
#define ERROR_WORD_SIZE -3
#define ERROR_EMPTY_STR -4
#define ERROR_EMPTY_RES_STR -5

int read_line(char *str, size_t str_max);

void filter_dupl_first_letter(char word[WORD_MAX_LEN]);

int split_str(char *str, char words[][WORD_MAX_LEN+1], size_t *words_cnt);

int form_new_str(char words[][WORD_MAX_LEN+1], size_t words_c, char new_str[STR_MAX_LEN+1]);

#endif
