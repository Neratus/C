#include "my_str.h"
#include <stdio.h>

const char *my_strpbrk(const char *str, const char *sym)
{
    while (*str)
    {
        for (size_t j = 0;sym[j]; j++)
        {
            if (*str == sym[j])
                return (const char *) str;
        }
        str++;
    }
    return NULL;
}

size_t my_strspn(const char *str, const char *sym)
{
    size_t len = 0;
    for (size_t i = 0; str[i]; i++)
    {
        int symb_found = 0;
        for (size_t j = 0;sym[j]; j++)
        {
            if (str[i] == sym[j])
                symb_found = 1;
        }
        if (symb_found == 1)
            len++;
        if (symb_found == 0)
            return len;
    }
    return len;
}

size_t my_strcspn(const char *str, const char *sym)
{
    size_t len = 0;
    while (*str)
    {
        int symb_found = 0;
        for (size_t j = 0;sym[j]; j++)
        {
            if (*str == sym[j])
                symb_found = 1;
        }
        if (symb_found == 0)
            len++;
        else
            return len;
        str++;
    }
    return len;
}

const char *my_strchr(const char *str, int ch)
{
    while (*str)
    {
        if (*str == ch)
            return (const char *) (str);
        str++;
    }
    if (ch == 0)
        return (const char *) (str);
    return NULL;
}

const char *my_strrchr(const char *str, int ch)
{
    const char *res = NULL;
    do
    {
        if (*str == ch)
            res = str;
    }while (*str++);
    return (const char *)res;
}


