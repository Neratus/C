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

int split(char *str, char words[][WORD_MAX_LEN+1], size_t *words_cnt)
{
    size_t a = 0;
    str += strspn(str, "\n \t.,:;?!- \0");
    while (*str)
    {
        char *p_start = str;
        char *p_end = strpbrk(p_start, "\n \t.,:;?!- \0");
        if (p_end == NULL)
            p_end = strchr(str, '\0');
        size_t word_len = p_end - p_start;
        if (word_len > WORD_MAX_LEN)
            return ERROR_WORD_SIZE;
        strncpy(words[a], p_start, word_len);
        words[a][word_len] = '\0';
        a++;
        str = p_end;
        str += strspn(str, "\n \t.,:;?!- \0");
    }
    *words_cnt = a;
    return 0;
}

void copy_unique_words(char unique[][WORD_MAX_LEN+1], size_t *unique_c, char arr[][WORD_MAX_LEN+1], size_t arr_c)
{
    size_t cur_index = 0;
    for (size_t i = 0; i < arr_c; i++)
    {
        int is_unique = 1;
        for (size_t j = 0; j < cur_index; j++)
        {
            if (strcmp(arr[i], unique[j]) == 0)
                is_unique = 0;
        }
        if (is_unique)
        {
            strcpy(unique[cur_index], arr[i]);
            cur_index++;
        }
    }
    *unique_c = cur_index;
}

int is_word_in_word_array(char word[WORD_MAX_LEN], char array[][WORD_MAX_LEN+1], size_t array_len)
{
    for (size_t i = 0; i < array_len; i++)
    {
        if (strcmp(word, array[i]) == 0)
            return 0;
    }
    return 1;
}
