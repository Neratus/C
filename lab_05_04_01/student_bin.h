#ifndef STDBIN_H
#define STDBIN_H


#include "student.h"

#define ERROR_INDEX_OUT_OF_RANGE 2
#define ERROR_INVALID_SUBSTRING 3
#define ERROR_NO_ACCEPTABLE_SUR 4

int sort_students(char *file_path);

int filter_students(char *file_path_source, char *file_path_dest, char *substr);

int get_average_grade(char *file_path, double *res);

int delete_low_grade_students(char *file_path, double aver);

#endif
