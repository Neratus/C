#include "student_bin.h"

int count_file_students(FILE *f, size_t *size)
{
    unsigned long sz;
    if (fseek(f, 0, SEEK_END))
        return ERROR_IO;
    sz = ftell(f);
    if ((sz < sizeof(student_t)) || (sz % sizeof(student_t) != 0))
        return ERROR_IO;
    *size = sz / sizeof(student_t);
    return fseek(f, 0, SEEK_SET);
}

 
int get_student_by_pos(FILE *f, size_t pos, student_t *s)
{
    int rc = fseek(f, pos * sizeof(student_t), SEEK_SET);
    if (!rc)
    {
        if (fread(s, sizeof(student_t), 1, f) != 1)
            return ERROR_IO;
        fseek(f, pos * sizeof(student_t), SEEK_SET);
        return OK;
    }
    return ERROR_INDEX_OUT_OF_RANGE;
}

int put_student_by_pos(FILE *f, size_t pos, student_t *s)
{
    int rc = fseek(f, pos * sizeof(student_t), SEEK_SET);
    if (!rc)
    {
        if (fwrite(s, sizeof(student_t), 1, f) != 1)
            return ERROR_IO;
        fseek(f, pos * sizeof(student_t), SEEK_SET);
        return OK;
    }
    return ERROR_INDEX_OUT_OF_RANGE;
}

int sort_students(char *file_path)
{
    FILE *f = fopen(file_path, "rb+");
    if (f == NULL)
        return ERROR_IO;
    size_t size_of_file;
    int rc = count_file_students(f, &size_of_file);
    if (rc == ERROR_IO)
    {
        fclose(f);
        return ERROR_IO;
    }
    student_t tmp;
    for (size_t step = size_of_file / 2; step > 0; step /= 2) 
    {
        for (size_t i = step; i < size_of_file; i++)
        {
            rc = get_student_by_pos(f, i, &tmp);
            int found = 1;  
            size_t j = i;
            while (j >= step && (found == 1)) 
            {
                student_t cur;
                rc = get_student_by_pos(f, j - step, &cur);
                if (compare_students_by_sur(&tmp, &cur) == 1)
                {
                    put_student_by_pos(f, j, &cur);
                    j -= step;
                }
                else 
                    found = 0;
            }
            rc = put_student_by_pos(f, j, &tmp);
            if (rc != OK)
            { 
                fclose(f);
                return rc;
            }
        }
    }
    fclose(f);
    return OK;
}

int filter_students(char *file_path_source, char *file_path_dest, char *substr)
{
    if (strlen(substr) > 25 || strlen(substr) == 0)
        return ERROR_INVALID_SUBSTRING;
    FILE *in = fopen(file_path_source, "rb");
    if (in == NULL)
        return ERROR_IO;
    FILE *out = fopen(file_path_dest, "wb");
    if (out == NULL)
    {
        fclose(in);
        return ERROR_IO;
    }
    size_t size_of_file;
    student_t cur;
    int rc = count_file_students(in, &size_of_file);
    if (rc != OK)
    { 
        fclose(in);
        fclose(out);
        return rc;
    }
    int count = 0;
    for (size_t i = 0; i < size_of_file; i++)
    {
        rc = get_student_by_pos(in, i, &cur);
        if (rc != OK)
        { 
            fclose(in);
            fclose(out);
            return rc;
        }
        if ((strlen(substr) == 0 && strlen(cur.surname) == 0) ||
            (strlen(substr) && strstr(cur.surname, substr) &&
            strstr(cur.surname, substr) - cur.surname == 0))
        {
            count++;
            rc = put_student_by_pos(out, count - 1, &cur);
            if (rc != OK)
            { 
                fclose(in);
                fclose(out);
                return rc;
            }
        }
    }
    fclose(in);
    fclose(out);
    if (count == 0)
        return ERROR_NO_ACCEPTABLE_SUR;
    return OK;
}


int get_average_grade(char *file_path, double *res)
{
    FILE *f = fopen(file_path, "rb+");
    if (f == NULL)
        return ERROR_IO;
    size_t stud_cnt;
    int rc = count_file_students(f, &stud_cnt);
    if (rc == ERROR_IO)
    {
        fclose(f);
        return ERROR_IO;
    }
    student_t tmp;
    double aver_sum = 0;
    for (size_t i = 0; i < stud_cnt; i++)
    {
        rc = get_student_by_pos(f, i, &tmp);
        if (rc != OK)
        { 
            fclose(f);
            return rc;
        }
        aver_sum += calc_stud_average_grade(tmp);
    }
    fclose(f);
    *res = aver_sum / stud_cnt;
    return OK;
}

int truncate_student_file(char *file_path, size_t entries_count)
{
    FILE* f = fopen(file_path, "wb");
    if (f == NULL)
        return ERROR_IO;
    int rc;
    FILE* temp_file = fopen("tmp", "rb");
    if (temp_file == NULL)
    {
        fclose(f);
        return ERROR_IO;
    }
    student_t s;
    for (size_t i = 0; i < entries_count; i++)
    {
        rc = get_student_by_pos(temp_file, i, &s);
        if (rc != OK)
            return rc;
        rc = put_student_by_pos(f, i, &s);
        if (rc != OK)
            return rc;
    }
    fclose(f);
    fclose(temp_file);
    remove("tmp");
    return OK;
}
 
int delete_low_grade_students(char *file_path, double aver)
{
    FILE *file = fopen(file_path, "rb+");
    FILE *temp_file = fopen("tmp", "w+b");
    if (file == NULL)
        return ERROR_IO;
    size_t size_of_file;
    int rc = count_file_students(file, &size_of_file);
    if (rc == ERROR_IO)
    {
        fclose(file);
        fclose(temp_file);
        return ERROR_IO;
    }
    size_t stud_cnt = 0;
    for (size_t i = 0; i < size_of_file; i++)
    {
        student_t s;
        rc = get_student_by_pos(file, i, &s);
        if (rc != OK)
            return rc;
        if (aver - calc_stud_average_grade(s) < 1e-8)
        {
            stud_cnt++;
            put_student_by_pos(temp_file, stud_cnt - 1, &s);
        }
    }
    fclose(file);
    fclose(temp_file);
    rc = truncate_student_file(file_path, stud_cnt);
    if (rc != 0)
        return rc;
    return OK;
}

