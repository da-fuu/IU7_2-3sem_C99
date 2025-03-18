#include <stdbool.h>
#include "functions.h"


// Аналог функции strpbrk - возвращает указатель на первый элемент строки, входящий во вторую строку, иначе NULL
char *my_strpbrk(const char *s, const char *accept)
{
    while (*s)
    {
        for (const char *curr_char = accept; *curr_char; curr_char++)
            if (*s == *curr_char)
                return (char *)s;
        s++;
    }
    return NULL;
}

// Вспомогательная функция проверки принадлежности символа строке
// Принимает символ и строку по указателю, возвращает результат проверки
bool char_in_str(char chr, const char *str)
{
    while (*str)
    {
        if (chr == *str)
            return true;
        str++;
    }
    return false;
}

// Аналог функции strspn - возвращает количество элементов из начала первой строки, входящих во вторую строку
size_t my_strspn(const char *s, const char *accept)
{
    size_t counter = 0;

    while (*s)
    {
        if (!char_in_str(*s, accept))
            break;
        counter++;
        s++;
    }
    return counter;
}

// Аналог функции strcspn - возвращает количество элементов из начала первой строки, не входящих во вторую строку
size_t my_strcspn(const char *s, const char *reject)
{
    size_t counter = 0;

    while (*s)
    {
        if (char_in_str(*s, reject))
            break;
        counter++;
        s++;
    }
    return counter;
}

// Аналог функции strchr - возвращает указатель на символ из первой строки, равный данному символу, поиск с начала, иначе NULL
char *my_strchr(const char *s, int c)
{
    char chr = (char)c;

    do
    {
        if (*s == chr)
            return (char*) s;
    }
    while (*s++);

    return NULL;
}

// Аналог функции strchr - возвращает указатель на символ из первой строки, равный данному символу, поиск с конца, иначе NULL
char *my_strrchr(const char *s, int c)
{
    const char *founded_char = NULL;
    char chr = (char)c;

    do
    {
        if (*s == chr)
            founded_char = s;
    }
    while (*s++);

    return (char*) founded_char;
}
