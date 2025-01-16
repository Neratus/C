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

int read_line(char *str, size_t str_max);

int split(char *str, char words[][WORD_MAX_LEN+1], size_t *words_cnt);

void copy_unique_words(char unique[][WORD_MAX_LEN+1], size_t *unique_c, char arr[][WORD_MAX_LEN+1], size_t arr_c);

int is_word_in_word_array(char word[WORD_MAX_LEN], char array[][WORD_MAX_LEN+1], size_t array_len);

#endif
