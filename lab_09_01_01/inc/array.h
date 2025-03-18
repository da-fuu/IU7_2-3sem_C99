#ifndef ARRAY_H__
#define ARRAY_H__

// Заголовочный файл файла для работы с массивом структур

#include <stdio.h>

#include "args.h"


// Функция вставки элемента в отсортированный массив так, чтобы он остался отсортированным
// Принимает указатель на структуру для вставки, тип поля для сортировки,
// массив структур по указателю и его старую длину
void insert_film_in_arr(const struct film_s *film, enum field_e field, struct film_s *films_arr, int old_len);

// Функция чтения данных из текстового файла в массив
// Принимает имя текстового файла, значение поля для сортировки
// Принимает и изменяет указатели на массив структур и его длину
// Возвращает код ошибки
int read_file(const char *filename, enum field_e field, struct film_s **films_arr, int *arr_len);

// Функция печати данных из массива
// Принимает массив структур по указателю и его длину
void print_arr(struct film_s *films_arr, int arr_len);

// Функция поиска фильма в массиве структур
// Принимает массив структур по указателю, его длину, тип поля к поиску, строку с полем
// Изменяет по указателю индекс структуры в массиве
// Возвращает код ошибки
int find_film(const struct film_s *films_arr, int arr_len, enum field_e field_type, const char *str, int *index_found);

// Функция освобождения массива структур
// Принимает массив структур по указателю и его длину
void free_arr(struct film_s *films_arr, int arr_len);


#endif	// #ifndef ARRAY_H__
