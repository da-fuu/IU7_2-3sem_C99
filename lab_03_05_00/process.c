#include <stdbool.h>
#include <math.h>
#include "process.h"


// Функция проверки числа на простоту
// Принимает целое число, возвращает результат проверки
bool is_prime(int number)
{
    if (number < 2)
        return false;
    
    for (int i = 2; i <= (int)sqrt(number); i++)
        if (number % i == 0)
            return false;
    
    return true;
}

// Функция заполнения массива простыми элементами матрицы
// Принимает матрицу по указателю, количество ее строк и столбцов, изменяет элементы массива по указателю, возвращает длину массива
size_t fill_array_with_primes(int matrix[][COLUMNS], size_t rows, size_t columns, int array_primes[])
{
    size_t array_len = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            if (is_prime(matrix[i][j]))
                array_primes[array_len++] = matrix[i][j];
             
    return array_len;
}

// Функция разворота массива
// Принимает длину массива и изменяет его элементы по указателю
void reverse_array(int array[], size_t length)
{
    int tmp;

    for (size_t i = 0; i < length / 2; i++)
    {
        tmp = array[i];
        array[i] = array[length - 1 - i];
        array[length - 1 - i] = tmp;
    }
}

// Функция вставки в простые элементы матрицы элементы массива(допускает что количество простых чисел равно длине массива)
// Принимает матрицу по указателю, количество ее строк и столбцов и массив по указателю, изменяет элементы матрицы по указателю
void insert_nums_in_primes(int matrix[][COLUMNS], size_t rows, size_t columns, int array_primes[])
{
    size_t curr_elem = 0;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            if (is_prime(matrix[i][j]))
                matrix[i][j] = array_primes[curr_elem++];
}
