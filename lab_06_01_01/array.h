#ifndef ARRAY_H__

#define ARRAY_H__

// Заголовочный файл файла для работы с массивом структур


#include <stdio.h>
#include "args.h"

#define MAX_FILE_LEN 15


// Объединение для хранения значения одного поля
union field_union
{
    int year;
    char *str;
};

// Функция чтения данных из текстового файла в массив
// Принимает имя текстового файла, массив структур и его длину по указателю и значение поля для сортировки
// Возвращает код ошибки
int read_file(char *filename, struct film_s films_arr[], size_t *arr_len, enum field_e field);

// Функция печати данных из массива
// Принимает массив структур и его длину
void print_arr(struct film_s films_arr[], size_t arr_len);

// Функция поиска фильма в массиве структур
// Принимает массив структур по указателю, его длину, тип поля к поиску, строку с полем
// Изменяет по указателю индекс структуры в массиве
// Возвращает код ошибки
int find_film(struct film_s films_arr[], size_t arr_len, enum field_e field, char *str, int *index_finded);


#endif	// #ifndef ARRAY_H__
