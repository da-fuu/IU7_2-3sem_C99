#include <stdio.h>
#include "io.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int matrix[DIMENSION][DIMENSION];
    size_t dimension;
    int res;
    int min_odd;

    puts("Введите количество строк и столбцов квадратной матрицы до десяти:");
    res = input_dimension_of_quad(&dimension);
    if (res != OK)
    {
        puts("Размерности матрицы должны быть равными целыми положительными числами не больше десяти!");
        return res;
    }

    puts("Введите элементы матрицы:");
    res = input_quad_matrix(matrix, dimension);
    if (res != OK)
    {
        puts("Матрица целых чисел введена некорректно!");
        return res;
    }

    res = find_min_odd_under_diag(matrix, dimension, &min_odd);
    if (res != OK)
    {
        puts("Под главной диагональю отсутствуют нечетные числа!");
        return res;
    }

    printf("Минимальное нечетное число под главной диагональю: %d \n", min_odd);

    return OK;
}
