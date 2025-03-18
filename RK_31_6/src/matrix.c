#include <stdlib.h>

#include "matrix.h"


// Создание квадратной матрицы
// Принимает размерность, возвращает матрицу
int **create_sq_matrix(int n)
{
    int *row_ptr;
    int **matrix = malloc((sizeof(int *) + sizeof(int) * n) * n);

    if (matrix == NULL)
        return NULL;

    row_ptr = (int *)(matrix + n);
    for (int i = 0; i < n; i++)
    {
        matrix[i] = row_ptr;
        row_ptr += n;
    }
    return matrix;
}

// Освобождение матрицы
// Принимает матрицу
void free_sq_matrix(int **matrix)
{
    free(matrix);
}

// Перемещение строк матрицы по заданию
// Принимает матрицу и размерность
void swap_rows(int **matrix, int n)
{
    int *tmp_row;

    for (int i = 0; i < n / 2; i++)
    {
        tmp_row = matrix[n - i - 1];
        matrix[n - i - 1] = matrix[i];
        matrix[i] = tmp_row;
    }
}

// Перемещение столбцов матрицы по заданию
// Принимает матрицу и размерность
void swap_cols(int **matrix, int n)
{
    int tmp_val;

    for (int j = 0; j < n / 2; j++)
    {
        for (int i = 0; i < n; i++)
        {
            tmp_val = matrix[i][n - j - 1];
            matrix[i][n - j - 1] = matrix[i][j];
            matrix[i][j] = tmp_val;
        }
    }
}
