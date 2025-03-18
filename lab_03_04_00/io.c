#include <stdio.h>
#include "io.h"

// Функция ввода размерности квадратной матрицы - возвращает код ошибки и изменяет по указателю переменную размерности
int input_dimension_of_quad(size_t *dimension)
{
    size_t rows, columns;
    if (scanf("%zu %zu", &rows, &columns) != 2)
        return ERROR_IO;

    if (rows != columns)
        return ERROR_NOT_QUAD;
    if (rows == 0 || rows > DIMENSION)
        return ERROR_RANGE;
    
    *dimension = rows;

    return OK;
}

// Функция ввода квадратной матрицы - возвращает код ошибки, принимает количество строк(столбцов) матрицы, изменяет по указателю элементы матрицы
int input_quad_matrix(int matrix[][DIMENSION], size_t dimension)
{
    for (size_t i = 0; i < dimension; i++)
        for (size_t j = 0; j < dimension; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERROR_IO;

    return OK;
}
