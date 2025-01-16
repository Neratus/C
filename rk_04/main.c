#include "list.h"

#define ERROR_WRONG_ARG -1

int main(int argc, char** argv)
{
    if (argc != 3)
        return ERROR_WRONG_ARG;

    node_t* head = NULL;
    int rc = init_list(argv[1], &head);
    if (rc != OK)
        return rc;
    
    split_list(&head);
    
    print_list(argv[2], head);
    free_list(head);
    return 0;
}
