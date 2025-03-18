#include <stdio.h>
#include "io.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int matrix[ROWS * 2][COLUMNS];
    size_t rows, columns;
    int res, digit;

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

    puts("Введите целевую цифру:");
    res = input_digit(&digit);
    if (res != OK)
    {
        puts("Цифра введена некорректно!");
        return res;
    }

    rows = add_rows(matrix, rows, columns, digit);

    puts("Измененная матрица:");
    print_matrix(matrix, rows, columns);

    return OK;
}
