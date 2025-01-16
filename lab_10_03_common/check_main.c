#include "check_clear.h" 
#include "check_each.h"
#include "check_find.h"
#include "check_min.h"
#include "check_max.h"
#include "check_remove.h"
#include <check.h>
#include <stdio.h>


int main(void)
{
    int fail = 0;
    Suite *s[6];
    SRunner *runner; 
    s[0] = clear_suite();
    s[1] = each_suite();
    s[2] = find_suite();
    s[3] = max_suite();
    s[4] = min_suite();
    s[5] = remove_suite();
    for (size_t i = 0; fail == 0 && i < 6; i++)
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
