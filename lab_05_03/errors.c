#include <stdio.h>
#include "errors.h"

#define PIPELINE


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code)
{
    #ifndef PIPELINE
    switch (err_code)
    {
        case ERR_ARGS:
            puts("Нужен как минимум один аргумент - режим");
            break;
        case ERR_IMPORT:
            puts("Ошибка при импорте данных");
            break;
        case ERR_EXPORT:
            puts("Ошибка при экспорте данных");
            break;
        case ERR_CREATE_ARGS:
            puts("Неверные аргументы при создании файла");
            break;
        case ERR_PRINT_ARGS:
            puts("Неверные аргументы при печати файла");
            break;
        case ERR_SORT_ARGS:
            puts("Неверные аргументы при сортировке файла");
            break;
        case ERR_FILE_ACCESS:
            puts("Нет доступа к файлу");
            break;
        case ERR_FILE_READ:
            puts("Некорректный формат файла");
            break;
    }
    #endif // ifndef PIPELINE

    return err_code;
}
