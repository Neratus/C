#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

#define ERROR_NOT_A_ACCEPTABLE_NUMBER 1


uint32_t shift_binary(uint32_t a, int n)
{
    if (n == 0)
    {
        return a;
    }
    return (a << n) + (a >> ((CHAR_BIT * 4) - n));
}


void print_binary(uint32_t a)
{
    for (int i = (CHAR_BIT * 4) - 1; i > -1; i--)
    {
        printf("%u", ((a >> i) & 1));
    }
}

int main(void)
{
    uint32_t a;
    int n;

    printf("Enter an unsigned number and the number of shift positions: ");
    if ((scanf("%" SCNu32"%d", &a, &n) == 2) && (a <= UINT_MAX) && (n >= 0))
    {
        n = n % (CHAR_BIT * 4);
        a = shift_binary(a, n);
        printf("Result: ");
        print_binary(a);
    }
    else
    {
        printf("Error:The number value is unacceptable\n"); 
        return ERROR_NOT_A_ACCEPTABLE_NUMBER;
    }
    return 0;
}


