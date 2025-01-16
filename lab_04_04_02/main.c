#include "str_func.h"


int main(void) 
{
    char line[STR_MAX_LEN+1];
    int rc = read_line(line, STR_MAX_LEN+1);
    if ((rc == ERROR_STR_INPUT) || (rc == ERROR_STR_SIZE))
        return rc;
    trim(line);
    rc = check_line_correct_date(line);
    if (rc == NOT_VALID_DATE)
        printf("NO\n");
    else
    {
        printf("YES\n");
    }
    return 0;
}
