#include <stdio.h>
#include "io.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int matrix[ROWS][COLUMNS];
    size_t rows, columns;
    int out_array[COLUMNS];
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

    fill_array(matrix, rows, columns, out_array);

    puts("Массив результатов:");
    print_array(out_array, columns);

    return OK;
}
