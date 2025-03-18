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

// Функция ввода цифры - возвращает код ошибки, изменяет переменную цифры по указателю
int input_digit(int *digit)
{
    if (scanf("%d", digit) != 1)
        return ERROR_IO;

    if (*digit < 0 || *digit >= 10)
        return ERROR_RANGE;

    return OK;
}

// Функция ввода матрицы - возвращает код ошибки, принимает количество строк и столбцов матрицы, изменяет по указателю элементы матрицы
int input_matrix(int matrix[][COLUMNS], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERROR_IO;

    return OK;
}

// Функция вывода матрицы - принимает матрицу по указателю и количество строк и столбцов матрицы
void print_matrix(int matrix[][COLUMNS], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
            printf("| % 5d ", matrix[i][j]);
        printf("|\n");
    }
}
