#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define ERROR_SIZE_INPUT -1 
#define ERROR_ARRAY_INPUT -2 
#define ERROR_NO_ELEMENTS_LEFT -3 



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


int is_square(int number) 
{
    int a;
    if (number < 0) 
        return 0;
    a = (int)sqrt(number);
    a = a * a;
    return a == number;
}


size_t filter_array(int initial_array[], size_t *size_of_array) 
{
    size_t index = 0;
    for (size_t i = 0; i < *size_of_array; i++) 
    {
        if (!is_square(initial_array[i])) 
        {
            index++;
            initial_array[index - 1] = initial_array[i];
        }
    }
    return index;
}

int main(void) 
{
    int a[N];
    size_t size;
    int code;
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
    size = filter_array(a, &size);
    if (size == 0) 
    {
        printf("ERROR:All elements were deleted\n");
        return ERROR_NO_ELEMENTS_LEFT;
    }
    printf("Array: [");
    for (size_t i = 0; i < size; i++) 
    {
        printf(" %d", a[i]);
    }
    printf(" ]\n");
    return 0;
}
