#include <stdio.h>

#define ERROR_TIME_FORMAT_INPUT 1
#define ERROR_TIME_NEGATIVE_INPUT 2 

int main(void)
{
    int sec;
    int min;
    int hour;

    printf("Enter time in seconds: ");
    if (scanf("%d", &sec) != 1)
    {
        printf("ERROR:Incorrect time input format\n");
        return ERROR_TIME_FORMAT_INPUT;
    }
 
    if (sec <= 0)
    {
        printf("ERROR:The time value must be positive\n");
        return ERROR_TIME_NEGATIVE_INPUT;
    }
  
    min = sec / 60;
    hour = min / 60;
    min = min % 60;
    sec = sec % 60;

    printf("Required time format %d : %d : %d\n", hour, min, sec);
    return 0;
}
