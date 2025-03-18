#include <stdbool.h>
#include "process.h"


// Функция проверки, отсортирован ли столбец по убыванию
// Возвращает результат проверки, принимает массив по указателю и его длину
bool is_column_decreasing(int matrix[][COLUMNS], size_t rows, size_t column)
{
    if (rows == 1)
        return false;

    for (size_t i = 1; i < rows; i++)
        if (matrix[i - 1][column] <= matrix[i][column])
            return false;

    return true;
}

// Функция для заполнения целочисленными значениями 1 или 0 в зависимости от выполнения условия столбцом матрицы
// Принимает матрицу по указателю, количество строк и столбцов, изменяет значения массива по указателю 
void fill_array(int matrix[][COLUMNS], size_t rows, size_t columns, int array[])
{
    for (size_t j = 0; j < columns; j++)
        if (is_column_decreasing(matrix, rows, j))
            array[j] = 1;
        else
            array[j] = 0;
}
