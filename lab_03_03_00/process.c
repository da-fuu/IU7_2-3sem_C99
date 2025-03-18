#include "process.h"


// Функция обмена строк в матрице
// Принимает количество столбцов матрицы, индексы строк для обмена и изменяет значения матрицы по указателю
void swap_rows(int matrix[][COLUMNS], size_t row1, size_t row2, size_t columns)
{
    int tmp;

    for (size_t j = 0; j < columns; j++)
    {
        tmp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = tmp;
    }
}

// Функция подсчета суммы элементов массива
// Принимает массив по указателю и его длину, возвращает искомую сумму
int array_sum(int array[], size_t length)
{
    int sum = 0;

    for (size_t i = 0; i < length; i++)
        sum += array[i];

    return sum;
}

// Функция сортировки строк в матрице по возрастанию суммы элементов
// Принимает количество строк и столбцов матрицы и изменяет ее значения по указателю
void sort_matrix_rows(int matrix[][COLUMNS], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows - 1; i++)
        for (size_t j = 0; j < rows - 1 - i; j++)
            if (array_sum(matrix[j], columns) > array_sum(matrix[j + 1], columns))
                swap_rows(matrix, j, j + 1, columns);
}
