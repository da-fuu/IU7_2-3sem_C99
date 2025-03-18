#include <stdio.h>

#include "errors.h"


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code)
{
    #ifdef DEBUG
    switch (err_code)
    {
        case ERR_ARGS:
            puts("Ошибка при выборе режима работы программы!");
            break;
        case ERR_INPUT:
            puts("Ошибка ввода матрицы!");
            break;
        case ERR_DIMENSIONS:
            puts("Ошибка ввода размерностей матрицы!");
            break;
        case ERR_NO_MEMORY:
            puts("Недостаточно памяти!");
            break;
        case ERR_EMPTY_OUT:
            puts("Пустой выход!");
            break;
        case ERR_MANY_MAX:
            puts("Несколько максимальных элементов в матрице!");
            break;
        default:
            break;
    }
    #endif // #ifdef DEBUG
    return err_code;
}
