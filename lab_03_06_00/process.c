#include "process.h"

// Функция для заполнения матрицы ходом быка
// Принимает количество строк и столбцов матрицы, изменяет ее значения по указателю
void fill_matrix(int matrix[][COLUMNS], size_t rows, size_t columns)
{
    int element = 1;

    for (size_t j = 0; j < columns; j++)
        if (j % 2 == 0)
            for (size_t i = 0; i < rows; i++)
                matrix[i][j] = element++;
        else
            for (size_t i = rows; i > 0; i--)
                matrix[i - 1][j] = element++;         
}
