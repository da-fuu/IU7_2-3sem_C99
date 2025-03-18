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
        case ERR_FILE_STRUCT:
            puts("Ошибка в текстовом файле");
            break;
        case ERR_FIND_ARG:
            puts("Неверные аргументы при поиске файла");
            break;
        case ERR_FILE_ACCESS:
            puts("Нет доступа к файлу");
            break;
        case ERR_NO_MEMORY:
            puts("Ошибка при выделении памяти");
            break;
        case ERR_EMPTY_FILE:
            puts("Пустой файл");
            break;
    }
    #endif // ifndef PIPELINE
    return err_code;
}
