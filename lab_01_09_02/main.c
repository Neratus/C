#include <stdio.h>
#include <math.h>

#define ERROR_NOT_A_NUMBER -1 
#define ERROR_NO_POSITIVE_NUMBERS -2 


double calculate(double x)
{
    int n = 0;
    double sum = 0;

    while (x >= 0)
    {
        sum += sqrt(n + 1 + x);
        n++;
        if (scanf("%lf", &x) != 1)
        {
            return ERROR_NOT_A_NUMBER;
        }
    }
    if (n == 0)
    {
        return ERROR_NO_POSITIVE_NUMBERS;
    }
    sum = sum / n;
    return sum;
}

int main(void)
{
    double func_message;
    double x;
    const double eps = 0.0000001;

    if (scanf("%lf", &x) != 1)
    {
        printf("Error: incorrect input");
        return ERROR_NOT_A_NUMBER;
    }
    func_message = calculate(x);
    if (((fabs(func_message) - 1) <= eps) && (func_message <= 0))
    {
        printf("Error: incorrect input");
        return ERROR_NOT_A_NUMBER;
    }
    if (((fabs(func_message) - 2) <= eps) && (func_message <= 0))
    {
        printf("ERROR:Cannot complete calculation,at least one number should be positive\n");
        return ERROR_NO_POSITIVE_NUMBERS;
    }
    printf("Result: %.6lf\n", func_message);
    return 0;
}
