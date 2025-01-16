#include <stdio.h>
#include <math.h>

#define ERROR_RESISTOR_INPUT 1 
#define ERROR_RESISTOR_ZERO 2
#define ERROR_RESISTOR_NEG 3 


int main(void)
{
    double r_1, r_2, r_3, r;
    const double eps = 0.0000001;
    
    printf("Enter the resistance of three resistors :");
    if (scanf("%lf%lf%lf", &r_1, &r_2, &r_3) != 3)
    {
        printf("ERROR:Incorrect resistance input format\n");
        return ERROR_RESISTOR_INPUT;
    }
 
    if ((fabs(r_1) <= eps) || (fabs(r_2) <= eps) || (fabs(r_3) <= eps))
    {
        printf("ERROR:At least one resistor has zero resistance\n");
        return ERROR_RESISTOR_ZERO;
    }

    if ((r_1 < 0) || (r_2 < 0) || (r_3 < 0))
    {
        printf("ERROR:At least one resistor has negative resistance\n");
        return ERROR_RESISTOR_NEG;
    }
    
    r_1 = 1 / (r_1);
    r_2 = 1 / (r_2);
    r_3 = 1 / (r_3);
    r = 1 / (r_1 + r_2 + r_3);
    printf("the resistance of this section of the circuit is equal to %.6lf\n", r);
    return 0;
}
