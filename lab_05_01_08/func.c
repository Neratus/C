#include "func.h"


int find_dist_max(FILE *f, int *dist)
{
    int prev, cur, next;
    int cur_index = 1;
    int prev_max = 0;
    if ((fscanf(f, "%d", &prev) != 1) || (fscanf(f, "%d", &cur) != 1) || (fscanf(f, "%d", &next) != 1))
        return ERROR_SEQUENCE_INPUT;
    do
    {
        if ((cur > prev) && (cur > next))
        {
            if (prev_max == 0)
                prev_max = cur_index;
            else if ((cur_index - prev_max < *dist) || (*dist == 0))
            {
                *dist = cur_index - prev_max;
                prev_max = cur_index;
            }
        }
        cur_index++;
        prev = cur;
        cur = next;
    }while (fscanf(f, "%d", &next) == 1);
    if (*dist == 0)
        return ERROR_NO_MAX;
    return OK;
}

