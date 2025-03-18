#include <malloc.h>

#include "matrix.h"


// Функция освобождения памяти из-под матрицы
// Принимает указатель на элементы матрицы
void free_matrix(double **matrix)
{
    free(matrix);
}

// Функция выделения памяти под матрицу
// Принимает размерности матрицы, возвращает указатель на элементы матрицы
double **allocate_matrix(size_t rows, size_t cols)
{
    double *shift;
    double **matrix = malloc((sizeof(double *) + sizeof(double) * cols) * rows);
    if (!matrix)
        return NULL;

    shift = (double *)(matrix + rows);
    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = shift;
        shift += cols;
    }

    return matrix;
}
