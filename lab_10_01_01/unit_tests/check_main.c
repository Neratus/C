#include <check.h>
#include <stdio.h>
#include "check_list.h"
#include "check_country.h"

int main(void)
{
    int fail = 0;
    Suite *s[4];
    SRunner *runner; 

    s[0] = list_add_tail_suite();
    s[1] = find_suite();
    s[2] = country_io_suite();
    s[3] = country_cmp_suite();

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
        printf("ALL UNIT TESTS PASSED SUCESSFULLY! \n");
    return fail;
}
