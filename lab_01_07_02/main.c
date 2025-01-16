#include <stdio.h>
#include <math.h>

#define ERROR_NUMBER_INCORRECT_INPUT 1 
#define ERROR_MODULE_OF_NUMBER 2 
#define ERROR_MODULE_OF_EPSILON 3 


double calc_sec_func(double x, double epsi)
{
    int i = 3;
    double cof = 0.5;
    double second_fun = 0;
    double next_el = x;

    while (fabs(next_el) >= epsi)
    { 
        second_fun += next_el;
        next_el = cof * (pow(x, i) / i);
        cof *= i;
        cof /= i + 1;
        i += 2;
    }
    return second_fun;
}


int main(void)
{
    double x;
    double epsi;
    double first_fun, second_fun;
    double absol, relat;
    const double eps = 0.0000001;
    printf("Enter x value and accuracy: ");
    if (scanf("%lf%lf", &x, &epsi) != 2)
    {
        printf("ERROR:Incorrect number and accuracy input format\n");
        return ERROR_NUMBER_INCORRECT_INPUT;
    }
    if ((epsi <= 0) || (epsi > 1))
    {
        printf("ERROR:Incorrect epsilon  value\n");
        return ERROR_MODULE_OF_EPSILON;
    }
    if ((x < -1) || (x > 1))
    {
        printf("ERROR:Incorrect number value\n");
        return ERROR_MODULE_OF_NUMBER;
    }
    first_fun = asin(x);
    second_fun = calc_sec_func(x, epsi);

    printf("Precise value: %lf\n", first_fun);
    printf("Approximate value: %lf\n", second_fun);
    absol = fabs(first_fun - second_fun);
    printf("Absolute error: %lf\n", absol);
    if (fabs(first_fun) <= eps)
    {
        printf("Impossible to calculate relative error\n");
    }
    else
    {
        relat = absol / first_fun;
        printf("Relative error: %lf\n", relat);
    }
    return 0;
}
