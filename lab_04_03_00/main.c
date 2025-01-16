#include "str_func.h"

int main(void) 
{
    char line[STR_MAX_LEN+1];
    char line_words[WORD_MAX_CNT][WORD_MAX_LEN+1];
    size_t line_count = 0;
    char new_str[STR_MAX_LEN+1];
    int rc = read_line(line, STR_MAX_LEN+1);
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
    rc = split_str(line, line_words, &line_count);
    if (rc == ERROR_WORD_SIZE)
    {
        printf("ERROR: word has exceeded the  allowed word length \n");
        return rc;
    }
    if (line_count == 0)
    {
        printf("ERROR: there are no words in this string \n");
        return ERROR_EMPTY_STR;
    }
    rc = form_new_str(line_words, line_count, new_str);
    if (rc == ERROR_EMPTY_RES_STR)
    {
        printf("ERROR: there are no words in new string \n");
        return ERROR_EMPTY_RES_STR;
    }
    printf("Result: %s\n", new_str);
    return 0;
}
