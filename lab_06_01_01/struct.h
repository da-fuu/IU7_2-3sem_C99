#ifndef STRUCT_H__

#define STRUCT_H__

// Заголовочный файл файла для работы со структурой


#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "args.h"

#define ERR_STRUCT -1
#define ERR_EOF -2

#define TITLE_LEN 25
#define NAME_LEN 25

// Структура фильма
struct film_s 
{
    char title[TITLE_LEN + 1];
    char name[NAME_LEN + 1];
    int year;
};

#define MAX_FILE_LEN 15

// Функция чтения строки из текстового файла
// Принимает строку по указателю, ее максимальную длину и файловую переменную
// Возвращает код ошибки
int read_string(char *str, size_t len, FILE *file);

// Функция чтения целого числа из текстового файла
// Принимает указатель на число и файловую переменную
// Возвращает код ошибки
int read_int(int *num, FILE *file);

// Функция чтения структуры фильма из текстового файла
// Принимает указатель на структуру фильма и файловую переменную
// Возвращает код ошибки
int read_film(struct film_s *film, FILE *file);

// Функция печати фильма
// Принимает указатель на структуру фильма
void print_film(struct film_s *film);


#endif	// #ifndef STRUCT_H__
