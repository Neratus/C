#include <math.h>
#include <stdio.h>

#define N 10 
#define ERROR_UNACCEPTABLE_AMMOUNT 1
#define ERROR_EXCEEDS_ACCEPTABLE 100


int input_array(int array[], size_t *size_of_array) 
{
    size_t index = 0;
    int cur = 0;
    while ((index < N) && (scanf("%d", &cur) == 1)) 
    {
        array[index] = cur;
        index++;
    }
    if (index == 0) 
        return ERROR_UNACCEPTABLE_AMMOUNT;
    *size_of_array = index;
    if (scanf("%d", &cur) == 1) 
        return ERROR_EXCEEDS_ACCEPTABLE;
    return 0;
}


void sort_array(int array[], size_t *size_of_array) 
{
    int cur_element;
    size_t index;
    for (size_t i = 0; i < *size_of_array; i++) 
    {
        cur_element = array[i];
        index = i;
        for (size_t j = i + 1; j < *size_of_array; j++) 
        {
            if (array[j] < cur_element) 
            {
                cur_element = array[j];
                index = j;
            }
        }
        array[index] = array[i];
        array[i] = cur_element;
    }
}

int main(void) 
{
    int a[N];
    size_t size;
    int code;
    printf("Enter the elements of array: ");
    code = input_array(a, &size);
    if (code == ERROR_UNACCEPTABLE_AMMOUNT) 
    {
        printf("ERROR:there should be at leats one element in array\n");
        return ERROR_UNACCEPTABLE_AMMOUNT;
    }
    if (code == ERROR_EXCEEDS_ACCEPTABLE) 
        printf("ERROR:size of array exceeds acceptable ammount\n");
    sort_array(a, &size);
    printf("Sorted array: ");
    for (size_t i = 0; i < size; i++) 
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return code;
}
