#include "check_obfuscation.h"

// Функция для избавления от ошибок компилятора на неправильный формат
char *ret_char_p(char *format)
{
    return format;
}

// Функция для избавления от ошибок компилятора на неправильный размер
int ret_size(int size)
{
    return size;
}
