#include <stdio.h>
#include <math.h>

#define ERROR_FIRST_COORD 1 
#define ERROR_SECOND_COORD 2 
#define ERROR_THIRD_COORD 3 
#define ERROR_TRIANGLE_DOESNT_EXIST 4 

int main(void)
{
    double x_a, y_a;
    double x_b, y_b;
    double x_c, y_c;
    double first_side, second_side, third_side;
    double perimetr;

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

    first_side = sqrt((x_b - x_a) * (x_b - x_a) + (y_b - y_a) * (y_b - y_a));
    second_side = sqrt((x_b - x_c) * (x_b - x_c) + (y_b - y_c) * (y_b - y_c));
    third_side = sqrt((x_c - x_a) * (x_c - x_a) + (y_c - y_a) * (y_c - y_a));

    if ((first_side + second_side <= third_side) || (third_side + second_side <= first_side) || \
        (first_side + third_side <= second_side))
    {
        printf("ERROR:This triangle doesn't exist \n");
        return ERROR_TRIANGLE_DOESNT_EXIST;
    }

    perimetr = first_side + second_side + third_side;
    printf("Perimeter of the triangle is equal to %.6lf\n", perimetr);
    return 0;
}
