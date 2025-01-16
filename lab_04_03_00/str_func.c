#include "str_func.h"


int read_line(char *str, size_t str_max)
{
    if (!fgets(str, str_max, stdin))
    {
        return ERROR_STR_INPUT;
    }
    char *p = strchr(str, '\n');
    if (p)
    {
        *p = 0;
        return 0;
    }
    return ERROR_STR_SIZE;
}

void filter_dupl_first_letter(char word[WORD_MAX_LEN])
{
    char targ_symb = word[0];
    int new_len = 1;
    for (size_t i = 1; i < strlen(word) + 1; i++)
    {
        if (word[i] != targ_symb)
        {
            new_len++;
            word[new_len - 1] = word[i];
        }
    }
}

int split_str(char *str, char words[][WORD_MAX_LEN+1], size_t *words_cnt)
{
    size_t a = 0;
    char *pword = strtok(str, "\n \t.,:;?!-");
    while (pword)
    {
        if (strlen(pword) > WORD_MAX_LEN)
            return ERROR_WORD_SIZE;
        strcpy(words[a], pword);
        a++;
        pword = strtok(NULL,"\n \t.,:;?!-");
    }
    *words_cnt = a;
    return 0;
}

int form_new_str(char words[][WORD_MAX_LEN+1], size_t words_c, char new_str[STR_MAX_LEN+1])
{
    new_str[0] = 0;
    char unacceptable_word[WORD_MAX_LEN+1];
    strcpy(unacceptable_word, words[words_c - 1]);
    for (size_t i = words_c - 2; i + 1 >= 1; i--)
    {
        if (strcmp(unacceptable_word, words[i]))
        {
            filter_dupl_first_letter(words[i]);
            strcat(new_str, " ");
            strcat(new_str, words[i]);
        }
    }
    if (new_str[0] == 0)
        return ERROR_EMPTY_RES_STR;
    return 0;
}
