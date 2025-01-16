#include <stdio.h>

#define ERROR_CONST_FORMAT_INPUT 1
#define ERROR_CONST_NEGATIVE_INPUT 2 


int division(int dividend, int divider)
{
    int quotient = 0;
    while (dividend >= divider)
    {
        quotient ++;
        dividend -= divider;
    }
    return quotient;
}


int main(void)
{
    int a;
    int d;
    int quotient;
    int dividend;

    printf("Enter an integer dividend and a divider: ");
    if (scanf("%d%d", &a, &d) != 2)
    {
        printf("ERROR:Incorrect number input format\n");
        return ERROR_CONST_FORMAT_INPUT;
    }
 
    if ((a <= 0) || (d <= 0))
    {
        printf("ERROR:The number value must be positive\n");
        return ERROR_CONST_NEGATIVE_INPUT;
    }
    quotient = division(a, d);
    dividend = a - quotient * d;
    printf("The quotient of the division is equal to %d \n", quotient);
    printf("The remainder of the division is equal to %d\n", dividend);
    return 0;
}
