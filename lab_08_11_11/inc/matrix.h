#ifndef MATRIX_H__
#define MATRIX_H__

// Заголовочный файл файла для работы с матрицами

#include <stddef.h>


// Структура для работы с матрицей
typedef struct
{
    double **elements;
    size_t rows;
    size_t cols;
} matrix_t;

// Функция освобождения памяти из-под матрицы
// Принимает указатель на элементы матрицы
void free_matrix(double **matrix);

// Функция выделения памяти под матрицу
// Принимает размерности матрицы, возвращает указатель на элементы матрицы
double **allocate_matrix(size_t rows, size_t cols);


#endif // #ifndef MATRIX_H__
