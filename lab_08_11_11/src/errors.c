#include <stdio.h>

#include "errors.h"


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code)
{
    switch (err_code)
    {
        case ERR_ARGS:
            puts("Ошибка в аргументах программы!");
            break;
        case ERR_FILE_STRUCT:
            puts("Ошибка в содержимом файла!");
            break;
        case ERR_FILE_DIMENSIONS:
            puts("Некорректные измерения матрицы в файле!");
            break;
        case ERR_FILE_IN_ACCESS:
            puts("Нет доступа к входному файлу!");
            break;
        case ERR_NO_MEMORY:
            puts("Недостаточно памяти!");
            break;
        case ERR_FILE_OUT_ACCESS:
            puts("Нет доступа к выходному файлу!");
            break;
        case ERR_DIMENSIONS_ADD:
            puts("Некорректные измерения матриц для сложения!");
            break;
        case ERR_DIMENSIONS_MULTIPLY:
            puts("Некорректные измерения матриц для умножения!");
            break;
        case ERR_DIMENSIONS_SOLVE:
            puts("Некорректные измерения матрицы для решения СЛАУ!");
            break;
        case ERR_SOLVE:
            puts("СЛАУ имеет бесконечность или ни одного решения!");
            break;
        default:
            break;
    }
    return err_code;
}
