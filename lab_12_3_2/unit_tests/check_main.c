#include <check.h>
#include <stdio.h>
#include "check_arr.h"

int main(void)
{
    int fail = 0;
    Suite *s[3];
    SRunner *runner; 
    s[0] = prime_suite();
    s[1] = fill_suite();
    s[2] = add_odd_suite();
    for (size_t i = 0; fail == 0 && i < 3; i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner,CK_VERBOSE);
        fail = srunner_ntests_failed(runner);
        srunner_free(runner);
        if (fail != 0)
            printf("FAILED TEST NUMBER %zu \n",i);
    } 
    if (fail == 0)
        printf("ALL UNIT TESTS PASSED SUCESSFULLY! \n");
    return fail;
    
}
