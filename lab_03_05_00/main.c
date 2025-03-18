#include <stdio.h>
#include "io.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int matrix[ROWS][COLUMNS];
    size_t rows, columns;
    int array_of_primes[ROWS * COLUMNS];
    size_t number_primes;
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

    number_primes = fill_array_with_primes(matrix, rows, columns, array_of_primes);
    if (number_primes == 0)
    {
        puts("В матрице нет простых чисел!");
        return ERROR_NO_PRIMES;
    }

    reverse_array(array_of_primes, number_primes);

    insert_nums_in_primes(matrix, rows, columns, array_of_primes);

    puts("Измененная матрица:");
    print_matrix(matrix, rows, columns);

    return OK;
}
