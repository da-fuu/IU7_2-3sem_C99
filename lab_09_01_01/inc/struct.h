#ifndef STRUCT_H__
#define STRUCT_H__

// Заголовочный файл файла для работы со структурой

#include <stdio.h>


#define ERR_STRUCT -1
#define ERR_EOF -2

// Структура фильма
struct film_s 
{
    char *title;
    char *name;
    int year;
};


// Функция чтения целого положительного числа из строки
// Принимает строку по указателю
// Возвращает число в строке или -1 при ошибке
int parse_int(const char *str);

// Функция чтения структуры фильма из текстового файла
// Принимает файловую переменную, изменяет структуру фильма по указателю
// Возвращает код ошибки
int read_film(FILE *file, struct film_s *film);

// Функция печати фильма
// Принимает указатель на структуру фильма
void print_film(struct film_s *film);

// Функция освобождения структуры фильма
// Принимает структуру фильма по указателю
void free_film(struct film_s *film);


#endif	// #ifndef STRUCT_H__
