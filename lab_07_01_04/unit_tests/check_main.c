#include "check_array.h"

int main(void)
{
    int fail = 0;

    Suite *s[4];
    SRunner *runner; 
    s[0] = cnt_file_nums_suite();
    s[1] = mysort_suite();
    s[2] = key_suite();
    s[3] = get_int_array_suite();

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
