#include <stdio.h>
#include <string.h>
#include "io.h"
#include "errors.h"


// Функция ввода строки - возвращает код ошибки и изменяет по указателю строку
int input_string(char string[])
{
    size_t str_len;
    if (fgets(string, STR_LEN + 1, stdin) == NULL)
        return ERR_INPUT;

    str_len = strlen(string);
    if (string[str_len - 1] != '\n')
        return ERR_STR_TOO_LONG;

    return OK;
}
