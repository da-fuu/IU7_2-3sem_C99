#ifndef FUNCTIONS_H__

#define FUNCTIONS_H__

// Заголовочный файл файла c аналогами строковых функций

#include <stddef.h>

// Аналог функции strpbrk - возвращает указатель на первый элемент строки, входящий во вторую строку, иначе NULL
char *my_strpbrk(const char *s, const char *accept);

// Аналог функции strspn - возвращает количество элементов из начала первой строки, входящих во вторую строку
size_t my_strspn(const char *s, const char *accept);

// Аналог функции strcspn - возвращает количество элементов из начала первой строки, не входящих во вторую строку
size_t my_strcspn(const char *s, const char *reject);

// Аналог функции strchr - возвращает указатель на символ из первой строки, равный данному символу, поиск с начала, иначе NULL
char *my_strchr(const char *s, int c);

// Аналог функции strchr - возвращает указатель на символ из первой строки, равный данному символу, поиск с конца, иначе NULL
char *my_strrchr(const char *s, int c);


#endif	// #ifndef FUNCTIONS_H__
