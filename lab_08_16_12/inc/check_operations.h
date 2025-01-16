#ifndef CHECK_OPER_H
#define CHECK_OPER_H

#include "matrix.h"
#include <check.h>

Suite *add_matrix_suite(void);
Suite *mult_matrix_suite(void);
Suite *find_deter_suite(void);

#endif
