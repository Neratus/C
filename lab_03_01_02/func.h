#ifndef FUNC_H
#define FUNC_H
#include "matrix_io.h"

int is_col_alternate_pos_neg(matrix matrix, size_t col_num, size_t arr_n);

void matrix_alternate_pos_neg(matrix matrix, size_t arr_n, size_t arr_m, int res[M]);

#endif
