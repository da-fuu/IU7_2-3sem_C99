#include <stdio.h>

#include "errors.h"


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code)
{
    switch (err_code)
    {
        case ERR_CMD_ARGS:
            puts("Ошибка в аргументах программы!");
            break;
        case ERR_FILE_IN_ACCESS:
            puts("Нет доступа к входному файлу!");
            break;
        case ERR_FILE_EMPTY:
            puts("Входной файл пуст!");
            break;
        case ERR_FILE_STRUCT:
            puts("Некорректные данные во входном файле!");
            break;
        case ERR_NO_MEMORY:
            puts("Недостаточно памяти!");
            break;
        case ERR_EMPTY_OUT:
            puts("Пустой выход!");
            break;
        case ERR_FILE_OUT_ACCESS:
            puts("Нет доступа к выходному файлу!");
            break;
        default:
            break;
    }
    return err_code;
}
