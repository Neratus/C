#include <math.h>
#include <stdio.h>

#define N 10  
#define ERROR_SIZE_INPUT 1  
#define ERROR_ARRAY_INPUT 2  
#define ERROR_NO_NEGATIVE_PRESENT 3  


int input_array(int array[], size_t *size_of_array) 
{
    if ((scanf("%zu", size_of_array) != 1)) 
        return ERROR_SIZE_INPUT;
    if ((*size_of_array > N) || (*size_of_array <= 0)) 
        return ERROR_SIZE_INPUT;
    for (size_t i = 0; i < *size_of_array; i++) 
    {
        if (scanf("%d", &array[i]) != 1) 
            return ERROR_ARRAY_INPUT;
    }
    return 0;
}


double calc_arifm_mean_of_neg(int array[], size_t *size_of_array) 
{
    double sum = 0;
    int ammount = 0;
    double total;
    for (size_t i = 0; i < *size_of_array; i++) 
    {
        if (array[i] < 0) 
        {
            sum += array[i];
            ammount++;
        }
    }
    if (!ammount) 
    {
        return ERROR_NO_NEGATIVE_PRESENT;
    }
    total = sum / ammount;
    return total;
}

int main(void) 
{
    int a[N];
    size_t size;
    int code;
    double arifm_mean;
    const double eps = 0.0000001;
    printf("Enter the size of the array and its elements: ");
    code = input_array(a, &size);
    if (code == ERROR_SIZE_INPUT) 
    {
        printf("ERROR:Invalid array size\n");
        return ERROR_SIZE_INPUT;
    }
    if (code == ERROR_ARRAY_INPUT) 
    {
        printf("ERROR:Invalid value of an array element\n");
        return ERROR_ARRAY_INPUT;
    }
    arifm_mean = calc_arifm_mean_of_neg(a, &size);
    if (fabs(arifm_mean - 3) <= eps) 
    {
        printf("ERROR:There are no negative elements in this array\n");
        return ERROR_NO_NEGATIVE_PRESENT;
    }
    printf("The arithmetic mean of the negative elements of the array is %.6lf\n", arifm_mean);
    return 0;
}
