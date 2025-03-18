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
            puts("Ошибка в аргументах программы");
            break;
        case ERR_IMPORT:
            puts("Ошибка при импорте данных");
            break;
        case ERR_EXPORT:
            puts("Ошибка при экспорте данных");
            break;
        case ERR_FILTER_ARGS:
            puts("Неверные аргументы при фильтрации файла");
            break;
        case ERR_EMPTY_OUTPUT:
            puts("Для данной подстроки не найдено ни одной записи!");
            break;
        case ERR_SORT_ARGS:
            puts("Неверные аргументы при сортировке файла");
            break;
        case ERR_FILE_ACCESS:
            puts("Нет доступа к файлу");
            break;
        case ERR_FILE_READ:
            puts("Некорректный формат бинарного файла");
            break;
    }
    #endif // ifndef PIPELINE
    return err_code;
}
