#include <stdio.h>

#include "errors.h"


int process_error(int err_code)
{
    switch (err_code)
    {
        case ERR_ARGS:
            puts("Неправильные аргументы запуска программы!");
            break;
        case ERR_FILE_IN:
            puts("Входного файла не существует!");
            break;
        case ERR_FILE_EMPTY:
            puts("Пустой файл!");
            break;
        case ERR_FILE_DIMENSIONS:
            puts("Неправильные измерения квадратной матрицы!");
            break;
        case ERR_FILE_STRUCT:
            puts("Неправильное содержание файла с целочисленной матрицей!");
            break;
        case ERR_FILE_OUT:
            puts("Невозможно создать выходной файл!");
            break;
        case ERR_NO_MEMORY:
            puts("Ошибка выделения памяти!");
            break;
        default:
            break;
    }
    return err_code;
}
