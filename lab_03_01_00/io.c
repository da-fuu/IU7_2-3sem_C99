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

// Функция ввода матрицы - возвращает код ошибки, принимает количество строк и столбцов матрицы, изменяет по указателю элементы матрицы
int input_matrix(int matrix[][COLUMNS], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERROR_IO;

    return OK;
}


// Функция печати массива - принимает массив по указателю и его длину
void print_array(const int array[], size_t length)
{    
    for (size_t i = 0; i < length; i++)
        printf("%d ", array[i]);

    printf("\n");
}
