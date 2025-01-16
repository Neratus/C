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
 
void trim(char line[STR_MAX_LEN + 1]) 
{
    size_t index = 0;
    while (isspace(line[index])) 
        index++;
    for (size_t i = 0; line[i] != '\0'; i++) 
        line[i] = line[index + i];
    unsigned long len = strlen(line);
    if (len > 0) 
    {
        while (isspace(line[len - 1]))
            len--;
    }
    line[len] = '\0';
}

int valid_month(char *str_month)
{
    size_t len_month = strlen(str_month);
    if (len_month >= 10)
        return NOT_VALID_DATE;
    for (size_t i = 0; i < len_month; i++)
    {
        str_month[i] = (char)tolower(str_month[i]);
    }
    str_month[len_month] = 0;
    char *month_values[] = 
    {
        "january" ,
        "february" ,
        "march" ,
        "april" ,
        "may",
        "june" ,
        "july" ,
        "august" ,
        "september" ,
        "october" ,
        "november" ,
        "december" 
    };
    for (size_t i = 0; i < 12; ++i)
        if (strcmp(month_values[i], str_month) == 0)
            return (int)i;
    return NOT_VALID_DATE;
}


int check_date_value(long date, long month, long year)
{
    if ((date <= 0) || (year < 0))
        return NOT_VALID_DATE;
    const int month_dates[12] = { 31, 28, 31, 30, 31 ,30, 31, 31, 30, 31, 30, 31 };
    if ((month == 1) && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)))
    {
        if (date > 29)
            return NOT_VALID_DATE;
        return VALID_DATE;
    }
    if (date > month_dates[month])
            return NOT_VALID_DATE;
    return VALID_DATE;
}


int split_str(char *str, char words[][STR_MAX_LEN + 1], size_t *words_cnt)
{
    size_t a = 0;
    size_t len = 0;
    str += strspn(str, "\t \0");
    while ((strlen(str) > 0) && (a < 4))
    {
        len = strcspn(str, "\t \0");
        strncpy(words[a], str, len);
        words[a][len] = '\0';
        str += len;
        str += strspn(str, "\t \0");
        a++;
    }
    *words_cnt = a;
    if (a != 3)
        return NOT_VALID_DATE;
    return 0;
}                                                                                                                                                                                                                                                 


int check_line_correct_date(char line[STR_MAX_LEN + 1])
{
    char words[4][STR_MAX_LEN + 1];
    size_t line_count = 0;
    int rc;
    rc = split_str(line, words, &line_count);
    if (rc == NOT_VALID_DATE)
        return NOT_VALID_DATE;
    long date = strtol(words[0], NULL, 10);
    if ((date == 0) || ((words[0][0] == '+') || (date <= 0) || (date > 99)))
        return NOT_VALID_DATE;
    int month = valid_month(words[1]);
    if (month == NOT_VALID_DATE)
        return NOT_VALID_DATE;
    long year = strtol(words[2], NULL, 10);
    if ((year == 0) || ((words[2][0] == '+') || (year < 1000) || (year > 9999)))
        return NOT_VALID_DATE;
    return check_date_value(date, month, year);
}
