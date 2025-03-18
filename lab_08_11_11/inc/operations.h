#ifndef OPERATIONS_H__
#define OPERATIONS_H__

// Заголовочный файл файла для работы с операциями над матрицами

#include "matrix.h"


#define EPS 0.0000001

// Функция сложения двух матриц. Принимает 2 входные матрицы, изменяет по указателю выходную матрицу
// Возвращает код ошибки
int add_matrices(matrix_t matrix_in_1, matrix_t matrix_in_2, matrix_t *matrix_out);

// Функция умножения двух матриц. Принимает 2 входные матрицы, изменяет по указателю выходную матрицу
// Возвращает код ошибки
int multiply_matrices(matrix_t matrix_in_1, matrix_t matrix_in_2, matrix_t *matrix_out);

// Функция решения СЛАУ
// Принимает матрицу коэффициентов и свободных членов и изменяет выходную матрицу по указателю
// Возвращает код ошибки
int solve_sle(matrix_t matrix_in, matrix_t *matrix_out);


#endif // #ifndef OPERATIONS_H__
