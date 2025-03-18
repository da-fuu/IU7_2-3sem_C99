#ifndef MATRIX_H__
#define MATRIX_H__

#include <stddef.h>


// Создание квадратной матрицы
// Принимает размерность, возвращает матрицу
int **create_sq_matrix(int n);

// Освобождение матрицы
// Принимает матрицу
void free_sq_matrix(int **matrix);

// Перемещение строк матрицы по заданию
// Принимает матрицу и размерность
void swap_rows(int **matrix, int n);

// Перемещение столбцов матрицы по заданию
// Принимает матрицу и размерность
void swap_cols(int **matrix, int n);


#endif // #ifndef MATRIX_H__
