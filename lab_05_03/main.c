/**
 * 
 *  Программа, создающая, сортирующая и
 *  выводящая на экран двоичные файлы с целыми числами.
 * 
 *  Для решения данной задачи выбран целочисленный тип int.
 * 
 *  Формат аргументов командной строки:
 *  1. app.exe c num filename - заполняет файл случайными числами
 *  num - количество заполняемых элементов
 *  2. app.exe p filename - выводит двоичный файл
 *  3. app.exe s filename - сортирует числа в файле
 * 
 *  Функции get_number_by_pos и put_number_by_pos - осмысленные функции.
 * 
 *  Сортировка производится методом Шелла, по возрастанию.
 */


#include "func.h"
#include "convert.h"


#define ERROR_WRONG_ARG -1
#define ERROR_NEGATIVE_NUM -2

int main(int argc, char **argv) 
{
    int rc = 0;
    if ((argc == 4) && (strcmp("c", argv[1]) == 0))
    {
        size_t num = atoi(argv[2]);
        if (num > 0)
        {
            rc = fill_binary(argv[3], num);
            if (rc == ERROR_IO)
                return rc;
            return OK;
        }
        else
            return ERROR_NEGATIVE_NUM;
    }
    if ((argc == 4) && (strcmp("export", argv[1]) == 0))
    {
        rc = export(argv[2], argv[3]);
        if (rc == ERROR_IO)
            return rc;
        return OK;
    }
    if ((argc == 4) && (strcmp("import", argv[1]) == 0))
    {
        rc = import(argv[2], argv[3]);
        if (rc == ERROR_IO)
            return rc;
        return OK;
    }
    if ((argc == 3) && (strcmp("p", argv[1]) == 0))
    {
        rc = print_binary(argv[2]);
        if (rc == ERROR_IO)
            return rc;
        return OK;
    }
    if ((argc == 3) && (strcmp("s", argv[1]) == 0))
    {
        rc = sort_binary(argv[2]);
        if (rc != OK)
            return rc;
        return OK;
    }
    return ERROR_WRONG_ARG;
}
