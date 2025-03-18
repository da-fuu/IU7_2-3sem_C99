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
            puts("Файл содержит не только целые числа!");
            break;
        case ERR_FILE_EMPTY:
            puts("Файл не содержит числа!");
            break;
        case ERR_FILE_IN_ACCESS:
            puts("Нет доступа к входному файлу!");
            break;
        case ERR_NO_MEMORY:
            puts("Слишком большой файл!");
            break;
        case ERR_EMPTY_OUT:
            puts("Пустой выходной файл!");
            break;
        case ERR_FILE_OUT_ACCESS:
            puts("Нет доступа к выходному файлу!");
            break;
        default:
            break;
    }
    return err_code;
}
