#include <stdio.h>
#include "errors.h"


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости реализовать
// предупреждения - обработать ошибку, но не прекратить выполнение main)
int process_error(int err_code)
{
    switch (err_code)
    {
        case ERR_INPUT:
            // puts("Ошибка ввода(пустой файл)");
            break;
        case ERR_STR_TOO_LONG:
            // puts("Слишком длинная строка");
            break;
        default:
            return OK;
    }
    return err_code;
}
