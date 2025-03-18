#include <stdio.h>
#include "io.h"

// Функция ввода размерности матрицы - возвращает код ошибки и изменяет по указателю переменные размерностей
int input_dimensions(size_t *rows, size_t *columns)
{
    if (scanf("%zu %zu", rows, columns) != 2)
        return ERROR_IO;

    if (*rows == 0 || *rows > ROWS || *columns == 0 || *columns > COLUMNS)
        return ERROR_RANGE;

    return OK;
}

// Функция вывода матрицы - принимает матрицу по указателю и количество строк и столбцов матрицы
void print_matrix(int matrix[][COLUMNS], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}
