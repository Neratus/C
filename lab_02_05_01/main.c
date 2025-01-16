#include <stdio.h>
#include <math.h>

#define N 10 
#define ERROR_SIZE_INPUT 1 
#define ERROR_ARRAY_INPUT 2 
#define ERROR_ARRAY_VALUE 3  


int input_array(int *start, int **end)
{
    size_t size_of_array;
    if ((scanf("%zu", &size_of_array) != 1))
        return ERROR_SIZE_INPUT;
    if ((size_of_array > N) || (size_of_array <= 0))
        return ERROR_SIZE_INPUT;
    *end = start + size_of_array;
    for (int *current = start; current < *end; current++)    
    {
        if (scanf("%d", current) != 1)
            return ERROR_ARRAY_INPUT;
    }
    return 0;
}


int sum_array(int *start, int *stop)
{
    int *begin, *end;
    int sum = 0;
    begin = start - 1;
    end = stop;
    while (begin != stop && end != start - 1)
    {
        do
            begin++;
        while (begin != stop && *begin >= 0);
        do
            end--;
        while (end != start - 1 && *end <= 0);
        if (begin != stop && end != start - 1)
            sum += (*end) * (*begin);
    }
    if (sum >= 0)
    {
        return ERROR_ARRAY_VALUE;
    }
    return sum;
}

int main(void)
{
    int a[N];
    int code;
    int *start = a;
    int *end = a + N;
    int sum_total;
    printf("Enter the size of the array and its elements: ");
    code = input_array(start, &end);
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
    sum_total = sum_array(start, end);
    if (sum_total == ERROR_ARRAY_VALUE)
    {
        printf("ERROR:no positive or negative numbers in array\n");
        return ERROR_ARRAY_VALUE;
    }
    printf("The required summ is equal to %d\n", sum_total);
    return 0;
}
