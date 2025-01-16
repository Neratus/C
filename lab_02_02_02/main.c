#include <stdio.h>
#include <stdlib.h>

#define N 10  
#define ERROR_SIZE_INPUT -1  
#define ERROR_ARRAY_INPUT -2  
#define ERROR_NO_REQ_PRESENT -3  


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


int is_acceptable(int number) 
{
    int first;
    number = abs(number);
    first = number % 10;
    while (number >= 10)
        number /= 10;
    return (first == number);
}


int copy_array(int initial_array[], int new_array[], size_t *size_of_array) 
{
    int index = 0;
    for (size_t i = 0; i < *size_of_array; i++) 
    {
        if (is_acceptable(initial_array[i])) 
        {
            new_array[index] = initial_array[i];
            index++;
        }
    }
    if (index == 0) 
        return ERROR_NO_REQ_PRESENT;
    return index;
}

int main(void) 
{
    int a[N];
    int b[N];
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
    code = copy_array(a, b, &size);
    if (code == -3) 
    {
        printf("ERROR:There are no acceptable elements in this array\n");
        return ERROR_NO_REQ_PRESENT;
    }
    printf("Array: ");
    for (int i = 0; i < code; i++) 
    {
        printf("%d ", b[i]);
    }
    printf("\n");
    return 0;
}
