#ifndef CHECK_LIST_H
#define CHECK_LIST_H

#include "list.h"
#include <check.h>

#define ERROR_STR_INPUT -1
#define ERROR_WRONG_ARG_VAL -3
#define ERROR_UNABLE_TO_READ_NUMS -4
#define ERROR_NUM_VALUE -5
#define ERROR_FILE_PATH -6
#define ERROR_MALLOC -7
#define ERROR_FILE_INPUT -8

#define OK 0

Suite* list_add_tail_suite(void);

Suite* find_suite(void);

#endif
