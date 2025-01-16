#include "func.h"
#include "matrix_io.h"


int calc_mult_of_array_elem(int array[M], size_t array_size)
{
    int multipl = 1;
    for (size_t i = 0; i < array_size; i++)
    {
        multipl *= array[i];
    }
    return multipl;
}


void swap_array_el(int first[M], int second[M], size_t array_size)
{
    int cur;
    for (size_t i = 0; i < array_size; i++)
    {
        cur = first[i];
        first[i] = second[i];
        second[i] = cur;
    }   
}


int compare_array_by_el_value(int first[M], int second[M], size_t array_size)
{
    for (size_t i = 0; i < array_size; i++)
    {
        if (first[i] < second[i])
            return 0;
        else if (first[i] > second[i])
        {
            return 1;
        }
    }
    return 0;
}


void sort_array_by_row_mult(matrix matrix, size_t arr_n, size_t arr_m)
{
    int cur_element;
    int index;
    int mult[N];
    for (size_t i = 0; i < arr_n; i++)
    {
        mult[i] = calc_mult_of_array_elem(matrix[i], arr_m);
    }
    for (size_t i = 0; i < arr_n; i++) 
    {
        cur_element = mult[i];
        index = i;
        for (size_t j = i + 1; j < arr_n; j++) 
        {
            if (mult[j] < cur_element) 
            {
                cur_element = mult[j];
                index = j;
            }
            else if (mult[j] == cur_element)
            {
                int a = compare_array_by_el_value(matrix[index], matrix[j], arr_m);
                if (a == 1)
                {
                    cur_element = mult[j];
                    index = j;
                }
            }
        }
        mult[index] = mult[i];
        mult[i] = cur_element;
        swap_array_el(matrix[index], matrix[i], arr_m);
    }
}
