#include <stdio.h>
#include <math.h>

#define ERROR_FIRST_COORD 1 
#define ERROR_SECOND_COORD 2 
#define ERROR_THIRD_COORD 3 
#define ERROR_FOURTH_COORD 3 
#define ERROR_TRIANGLE_DOESNT_EXIST 4


int belong_in_triangle(double x_a, double y_a, double x_b, double y_b, \
double x_c, double y_c, double x_p, double y_p)
{
    double a, b, c;
    const double eps = 0.0000001;
    a = (x_a - x_p) * (y_b - y_a) - (x_b - x_a) * (y_a - y_p);
    b = (x_b - x_p) * (y_c - y_b) - (x_c - x_b) * (y_b - y_p);
    c = (x_c - x_p) * (y_a - y_c) - (x_a - x_c) * (y_c - y_p);
    if (((a > 0) && (b > 0) && (c > 0)) || ((a < 0) && (b < 0) && (c < 0)))
    {
        printf("Точка находится внутри треугольника \n");
        return 0;
    }
    else if ((fabs(a) <= eps) || (fabs(b) <= eps) || (fabs(c) <= eps))
    {
        printf("Точка находится на грани треугольника \n");
        return 1;
    }
    else
    {
        printf("Точка находится вне треугольника \n");
        return 2;
    }
}

int if_triangle_exist(double x_a, double y_a, double x_b, double y_b, double x_c, double y_c)
{
    const double eps = 0.0000001; 
    if (fabs((x_b - x_a) * (y_c - y_a) - (x_c - x_a) * (y_b - y_a)) < eps)
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    double x_a, y_a;
    double x_b, y_b;
    double x_c, y_c;
    double x_p, y_p;
    int ans;
    printf("Enter the coordinates of point A: ");
    if (scanf("%lf %lf", &x_a, &y_a) != 2)
    {
        printf("ERROR:Incorrect coordinate input format at point A\n");
        return ERROR_FIRST_COORD;
    }
    printf("Enter the coordinates of point B: ");
    if (scanf("%lf %lf", &x_b, &y_b) != 2)
    {
        printf("ERROR:Incorrect coordinate input format at point B\n");
        return ERROR_SECOND_COORD;
    }
    printf("Enter the coordinates of point C: ");
    if (scanf("%lf %lf", &x_c, &y_c) != 2)
    { 
        printf("ERROR:Incorrect coordinate input format at point C\n");
        return ERROR_THIRD_COORD;
    }
    printf("Enter the coordinates of point P: ");
    if (scanf("%lf %lf", &x_p, &y_p) != 2)
    {
        printf("ERROR:Incorrect coordinate input format at point P\n");
        return ERROR_FOURTH_COORD;
    }
    if (if_triangle_exist(x_a, y_a, x_b, y_b, x_c, y_c) == 1)
    {
        printf("ERROR:This triangle doesn't exist \n");
        return ERROR_TRIANGLE_DOESNT_EXIST;
    }
    ans = belong_in_triangle(x_a, y_a, x_b, y_b, x_c, y_c, x_p, y_p);
    printf("%d\n", ans);
    return 0;
}
