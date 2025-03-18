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

    fill_matrix(matrix, rows, columns);

    puts("Заполненная матрица:");
    print_matrix(matrix, rows, columns);

    return OK;
}
