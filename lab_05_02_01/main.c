#include "func.h"

#define ERROR_WRONG_ARG -1

int main(int argc, char **argv) 
{
    if (argc != 2)
    {
        printf("ERROR: wrong arguments were given \n");
        return ERROR_WRONG_ARG;
    }
    double mean_of_max_min = 0;
    int count = 0;
    int rc = calc_arifm_mean_of_max_min(argv[1], &mean_of_max_min);
    if (rc == ERROR_IO)
    {
        printf("ERROR: error while opening file \n");
        return rc;
    }
    if (rc == ERROR_NO_NUM)
    {
        printf("ERROR: cannot read numbers in file \n");
        return rc;
    }
    rc = count_numb_gt(argv[1], mean_of_max_min, &count);
    if (rc == ERROR_IO)
    {
        printf("ERROR: error while opening file \n");
        return rc;
    }
    if (rc == ERROR_NO_NUM)
    {
        printf("ERROR: cannot read numbers in file \n");
        return rc;
    }
    printf("The ammount of matching numbers is: %d \n", count);
    return 0;
}
