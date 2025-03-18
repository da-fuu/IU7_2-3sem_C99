#ifndef IO_H__

#define IO_H__

// Заголовочный файл файла для работы с вводом-выводом

#include <stddef.h>
#include "config.h"


// Функция ввода размерности квадратной матрицы - возвращает код ошибки и изменяет по указателю переменную размерности
int input_dimension_of_quad(size_t *dimension);

// Функция ввода квадратной матрицы - возвращает код ошибки, принимает количество строк(столбцов) матрицы, изменяет по указателю элементы матрицы
int input_quad_matrix(int matrix[][DIMENSION], size_t dimension);


#endif	// #ifndef IO_H__
