#ifndef IO_H__

#define IO_H__

// Заголовочный файл файла для работы с вводом-выводом

#include <stddef.h>
#include "config.h"


// Функция ввода размерности матрицы - возвращает код ошибки и изменяет по указателю переменные размерностей
int input_dimensions(size_t *rows, size_t *columns);

// Функция ввода матрицы - возвращает код ошибки, принимает количество строк и столбцов матрицы, изменяет по указателю элементы матрицы
int input_matrix(int matrix[][COLUMNS], size_t rows, size_t columns);

// Функция печати массива - принимает массив по указателю и его длину
void print_array(const int array[], size_t length);


#endif	// #ifndef IO_H__
