#ifndef STD_H
#define STD_H

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
 
#define SURNAME_LEN 25
#define NAME_LEN 10
#define GRADES_LEN 4

#define OK 0
#define ERROR_IO 1
#define ERROR_WRONG_STR_LEN 6

typedef struct
{
    char surname[SURNAME_LEN + 1];
    char name[NAME_LEN + 1];
    uint32_t grades[GRADES_LEN];
} student_t;
 
void print_student(FILE *f, student_t *st);

int read_student(FILE *f, student_t *st);

int compare_students_by_sur(student_t *a, student_t *b);

double calc_stud_average_grade(student_t st);

#endif
