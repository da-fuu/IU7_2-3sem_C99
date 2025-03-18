#include <stdio.h>
#include "errors.h"


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code)
{
    switch (err_code)
    {
        case ERR_INPUT:
            puts("Ошибка ввода(ни одного числа в файле)");
            break;
        case ERR_ARGS:
            puts("Нужен строго один аргумент командной строки - имя файла");
            break;
        case ERR_FILE:
            puts("Файл не существует");
            break;
        case ERR_FILE_CONTENT:
            puts("Не только веществительные числа в файле!");
            break;
    }
    return err_code;
}
