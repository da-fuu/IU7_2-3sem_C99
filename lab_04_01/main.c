#include <stdio.h>
#include <string.h>
#include "functions.h"

// Максимальная длина строк в тестах
#define MAX_STR_LEN 20


// Функции для сравнения поведения реализованной функции и функции из стандартной библиотеки
// Принимают тестовые данные функции
// Возвращают 0 в случае совпадения результатов, иначе 1
int test_strpbrk(char *string, char *rule)
{
    return my_strpbrk(string, rule) != strpbrk(string, rule);
}

int test_strspn(char *string, char *rule)
{
    return my_strspn(string, rule) != strspn(string, rule);
}

int test_strcspn(char *string, char *rule)
{
    return my_strcspn(string, rule) != strcspn(string, rule);
}

int test_strchr(char *str, char chr)
{
    return my_strchr(str, chr) != strchr(str, chr);
}

int test_strrchr(char *str, char chr)
{
    return my_strrchr(str, chr) != strrchr(str, chr);
}

// Основная функция программы
int main(void)
{
    int fails = 0;

    // Создание тестовых массивов 
    // 1 - символ есть в строке, 2 - символа нет в строке, 3 - все символы есть в строке
    // 4 - пустая строка для поиска, 5 - повторяющиеся символы в строке для поиска, 6 - пустая строка
    // 7 - искомый символ первый, 8 - искомый символ последний
    char strpbrk_strings[][MAX_STR_LEN] = { "asdf", "fzdxgb", "xdfj", "wasaw", "rrrary" , "", "bre", "uety" };
    char strpbrk_rules[][MAX_STR_LEN] = { "d", "e", "jd", "", "yyy", "a", "b", "y" };
    size_t strpbrk_tests = sizeof(strpbrk_rules) / sizeof(strpbrk_rules[0]);

    // 1 - в строке нет данных символов, 2 - строка целиком из данных символов, 3 - начало строки из данных символов
    // 4 - данные символы в середине строки, 5 - пустая строка для поиска, 6 - пустая строка
    // 7 - строка из одного элемента
    char strspn_strings[][MAX_STR_LEN] = { "aszdx", "asd", "sdbv", "asqqwe", "werf", "", "t" };
    char strspn_rules[][MAX_STR_LEN] = { "er", "dsaaar", "sod", "qq", "", "a", "rt" };
    size_t strspn_tests = sizeof(strspn_rules) / sizeof(strspn_rules[0]);

    // 1 - данные символы в конце строки, 2 - данные символы в середине строки, 3 - начало строки из данных символов
    // 4 - в строке нет данных символов, 5 - пустая строка для поиска, 6 - пустая строка
    // 7 - строка из одного элемента, 8 - строка целиком из данных символов
    char strcspn_strings[][MAX_STR_LEN] = { "asdft", "dasrrtw", "dsdxvc", "werf", "dsaf", "", "e", "qwqwwq" };
    char strcspn_rules[][MAX_STR_LEN] = { "t", "rst", "dv", "a", "", "a", "e", "qw" };
    size_t strcspn_tests = sizeof(strcspn_rules) / sizeof(strcspn_rules[0]);

    // 1 - символ в середине строки, 2 - символа нет в строке, 3 - символ в начале строки
    // 4 - символ в конце строки, 5 - поиск символа с кодом 0, 6 - пустая строка
    // 7 - строка из одного элемента
    char strchr_strings[][MAX_STR_LEN] = { "abdb", "adssv", "ads", "ads", "sdf", "", "b" };
    char strchr_chars[] = { 'd', 'e', 'a', 's', '\0', 'a', 'b' };
    size_t strchr_tests = sizeof(strchr_chars) / sizeof(strchr_chars[0]);

    // 1 - символ в середине строки, 2 - символа нет в строке, 3 - символ в начале строки
    // 4 - символ в конце строки, 5 - поиск символа с кодом 0, 6 - пустая строка
    // 7 - строка из одного элемента
    char strrchr_strings[][MAX_STR_LEN] = { "abdb", "adssv", "ads", "ads", "sdf", "", "c" };
    char strrchr_chars[] = { 'd', 'e', 'a', 's', '\0', 'a', 'c' };
    size_t strrchr_tests = sizeof(strrchr_chars) / sizeof(strrchr_chars[0]);

    // Проверка поведения функций 
    for (size_t i = 0; i < strpbrk_tests; i++)
        fails += test_strpbrk(strpbrk_strings[i], strpbrk_rules[i]);

    for (size_t i = 0; i < strspn_tests; i++)
        fails += test_strspn(strspn_strings[i], strspn_rules[i]);

    for (size_t i = 0; i < strcspn_tests; i++)
        fails += test_strcspn(strcspn_strings[i], strcspn_rules[i]);

    for (size_t i = 0; i < strchr_tests; i++)
        fails += test_strchr(strchr_strings[i], strchr_chars[i]);

    for (size_t i = 0; i < strrchr_tests; i++)
        fails += test_strrchr(strrchr_strings[i], strrchr_chars[i]);

    printf("Количество проваленных сравнений поведения функций: %d \n", fails);
    return fails;
}
