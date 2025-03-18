#include <stdio.h>
#include "io.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int matrix[ROWS][COLUMNS];
    size_t rows, columns;
    int res;

    puts("Введите количество строк и столбцов матрицы до десяти:");
    res = input_dimensions(&rows, &columns);
    if (res != OK)
    {
        puts("Размерности матрицы должны быть целыми положительными числами не больше десяти!");
        return res;
    }

    puts("Введите элементы матрицы:");
    res = input_matrix(matrix, rows, columns);
    if (res != OK)
    {
        puts("Матрица целых чисел введена некорректно!");
        return res;
    }

    sort_matrix_rows(matrix, rows, columns);

    puts("Отсортированная матрица:");
    print_matrix(matrix, rows, columns);

    return OK;
}
