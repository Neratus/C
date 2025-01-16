#include <stdarg.h>
#include <limits.h>
#include "my_snprintf.h"

static size_t my_strncpy(char *dest, const char *src, size_t size)
{
    size_t len = 0;
    for (; *src != '\0'; src++)
    {
        if (len + 1 < size)
            *dest++ = *src;
        len++;
    }
    return len;
}

static char *my_itoa(long value, char *str, int base)
{
    char digits[] = "0123456789abcdef";
    int cur = 0;

    if (value < 0 && base == 10)
    {
        str[cur++] = '-'; 
        value = -value;
    }

    if (value == 0) 
        str[cur++] = '0'; 
    else
    {
        int num_digits = 0;
        long temp_value = value;
        while (temp_value > 0) 
        {
            num_digits++;
            temp_value /= base;
        }

        for (int i = num_digits - 1; i >= 0; i--)
        {
            str[cur + i] = digits[value % base];
            value /= base;
        }
        cur += num_digits;
    }

    str[cur] = '\0'; 
    return str;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    if (format == NULL)
        return -1;
    if ((s == NULL) && (n < 0))
        return -2;

    va_list vl;
    va_start(vl, format);

    int space = (int)n;
    size_t written = 0;
    char *cur = s;
    char buf[BUF_LEN];

    while (*format != 0)
    {
        if (*format == '%' && *(format + 1) == 's')
        {
            char *str = va_arg(vl, char *);
            if (str == NULL)
                str = "(null)";

            if (space <= 0)
                space = 0;

            size_t len = my_strncpy(cur, str, (unsigned)space);
            if (space > 0)
            {
                if (len >= (unsigned)space - 1)
                    cur += space - 1;
                else 
                    cur += len;
            }
            space -= len;
            written += len;
            format += 2;
        }
        else if (*format == '%' && *(format + 1) == 'd')
        {
            int num = va_arg(vl, int);
            my_itoa(num, buf, 10);
            size_t len = my_strncpy(cur, buf, (unsigned)space);
            if (space > 0)
            {
                if (len >= (unsigned)space - 1)
                    cur += space - 1;
                else 
                    cur += len;
            }
            space -= len;
            written += len;
            format += 2;
        }
        else if (*format == '%' && *(format + 1) == 'h' && *(format + 2) == 'x')
        {
            unsigned short num = (unsigned short) va_arg(vl, int);
            int conv = (int)num;
            my_itoa(conv, buf, 16);
            size_t len = my_strncpy(cur, buf, (unsigned)space);
            if (space > 0)
            {
                if (len >= (unsigned)space - 1)
                    cur += space - 1;
                else 
                    cur += len;
            }
            space -= len;
            written += len;
            format += 3;
        }
        else 
        {
            if (space > 1)
            {
                *cur = *format;
                ++cur;
            }
            format++;
            space--;
            written++;
        }
    }
    if (cur != NULL)
        *cur = '\0';

    va_end(vl);

    return (int)written;
}
