#include <check.h>
#include <stdio.h>
#include "check_io.h"
#include "check_operations.h"

int main(void)
{
    int fail = 0;
    Suite *s[4];
    SRunner *runner; 
    s[0] = allocate_matrix_suite();
    s[1] = add_matrix_suite();
    s[2] = mult_matrix_suite();
    s[3] = find_deter_suite();

    for (size_t i = 0; fail == 0 && i < 4; i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner,CK_VERBOSE);
        fail = srunner_ntests_failed(runner);
        srunner_free(runner);
        if (fail != 0)
            printf("FAILED TEST NUMBER %zu \n",i);
    } 
    if (fail == 0)
        printf("ALL UNIT TESTS PASSED SUCСESSFULLY! \n");
    return fail;
    
}
