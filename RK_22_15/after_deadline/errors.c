#include <stdio.h>
#include "errors.h"

void process_error(int rc)
{
    switch (rc)
    {
        case FILE_ERROR:
            puts("Ошибка чтения файла (файл не существует)");
            break;
        case ERR_TOO_LONG_FILENAME:
            puts("Слишком длинная строка названия файла!");
            break;
        case ERR_INPUT_FILENAME:
            puts("Ошибка ввода имени файла");
            break;
        case ERR_NO_WORDS:
            puts("Нет слов в строке файла");
            break;
        case ERR_EMPTY_OUT_STR:
            puts("Пустая выходная строка");
            break;
        case ERR_TOO_LONG_STR:
            puts("Слишком длинная строка в файле");
            break;
        case ERR_INCORRECT_CHARS:
            puts("Строка не из малых лат букв!");
            break;
    }
}
