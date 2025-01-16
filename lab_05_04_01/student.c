#include "student.h"

void print_student(FILE *f, student_t *st)
{
    fprintf(f, "%s\n", st->surname);
    fprintf(f, "%s\n", st->name);
    for (size_t i = 0; i < GRADES_LEN; i++)
        fprintf(f, "%" PRIu32 " ", st->grades[i]);
    fprintf(f, "\n");
}

int read_student(FILE *f, student_t *st)
{
    char sur[SURNAME_LEN + 1];
    char nam[NAME_LEN + 1];
    uint32_t grades[GRADES_LEN];

    if (!fgets(sur, SURNAME_LEN + 2, f))
        return ERROR_IO;
    char *p = strchr(sur, '\n');
    if (!p)
        return ERROR_WRONG_STR_LEN;
    *p = 0;

    if (!fgets(nam, NAME_LEN + 2, f))
        return ERROR_IO;
    p = strchr(nam, '\n');
    if (!p)
        return ERROR_WRONG_STR_LEN;
    *p = 0;

    for (size_t i = 0; i < GRADES_LEN; i++)
        if (fscanf(f, "%"SCNu32" ", &grades[i]) != 1)
            return ERROR_IO;
    strcpy(st->surname, sur);
    strcpy(st->name, nam);
    memcpy(st->grades, grades, sizeof(uint32_t) * GRADES_LEN);
    return OK;
}
 
int compare_students_by_sur(student_t *a, student_t *b)
{
    int cmp = strcmp(a->surname, b->surname);
    if (cmp < 0) 
        return 1;
    else if (cmp == 0 && strcmp(a->name, b->name) < 0)
        return 1;
    return 0;
}

double calc_stud_average_grade(student_t st)
{
    double sum = 0;
    for (size_t i = 0; i < GRADES_LEN; i++)
        sum += st.grades[i];
    return (sum / GRADES_LEN);
}
