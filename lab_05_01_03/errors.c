#include <stdio.h>
#include <stdlib.h>
#include "errors.h"


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code)
{
    switch (err_code)
    {
        case ERR_INPUT:
            puts("Ошибка ввода(ни одного числа не было введено)");
            break;
        case ERR_ONE_ELEM:
            puts("Введено только одно число");
            break;
    }
    return abs(err_code);
}
