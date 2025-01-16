#include "str_func.h"


int main(void)
{
    char first_line[STR_MAX_LEN+1];
    char first_line_words[WORD_MAX_CNT][WORD_MAX_LEN+1];
    size_t first_line_count = 0;
    char second_line[STR_MAX_LEN+1];
    char second_line_words[WORD_MAX_CNT][WORD_MAX_LEN+1];
    char unique_words[WORD_MAX_CNT][WORD_MAX_LEN+1];
    size_t unique_count = 0;
    size_t second_line_count = 0;
    int rc = read_line(first_line, STR_MAX_LEN+1);
    if (rc == ERROR_STR_INPUT)
    {
        printf("ERROR: error while reading string \n");
        return rc;
    }
    if (rc == ERROR_STR_SIZE)
    {
        printf("ERROR: string has exceeded the allowed string length \n");
        return rc;
    }
    rc = split(first_line, first_line_words, &first_line_count);
    if (rc == ERROR_WORD_SIZE)
    {
        printf("ERROR: word has exceeded the  allowed word length \n");
        return rc;
    }
    if (first_line_count == 0)
    {
        printf("ERROR: there are no words in this string \n");
        return ERROR_EMPTY_STR;
    }
    rc = read_line(second_line, STR_MAX_LEN+1);
    if (rc == ERROR_STR_INPUT)
    {
        printf("ERROR: error while reading string \n");
        return rc;
    }
    if (rc == ERROR_STR_SIZE)
    {
        printf("ERROR: string has exceeded the maximum allowed size \n");
        return rc;
    }
    rc = split(second_line, second_line_words, &second_line_count);
    if (rc == ERROR_WORD_SIZE)
    {
        printf("ERROR: word has exceeded the  allowed word length \n");
        return rc;
    }
    if (second_line_count == 0)
    {
        printf("ERROR: there are no words in this string \n");
        return ERROR_EMPTY_STR;
    }
    printf("Result: \n");
    copy_unique_words(unique_words, &unique_count, first_line_words, first_line_count);
    for (size_t i = 0; i < unique_count; i++)
    {
        int cur_word = is_word_in_word_array(unique_words[i], second_line_words, second_line_count);
        if (cur_word == 0)
            printf("%s yes\n", unique_words[i]);
        else 
            printf("%s no\n", unique_words[i]);
    }
    return rc;
}
