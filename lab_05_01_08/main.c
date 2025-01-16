#include "func.h"

int main(void) 
{
    int rc;
    int dist = 0;
    rc = find_dist_max(stdin, &dist);
    if (rc == ERROR_SEQUENCE_INPUT)
    {
        printf("ERROR: wrong sequence input \n");
        return rc;
    }
    if (rc == ERROR_NO_MAX)
    {
        printf("ERROR: cannot determine distance between two local maxima \n");
        return rc;
    }
    printf("Smallest distance between two local maxima of the sequence equals: %d\n", dist);
    return OK;
}
