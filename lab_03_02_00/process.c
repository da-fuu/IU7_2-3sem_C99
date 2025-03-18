#include <stdlib.h>
#include <stdbool.h>
#include "process.h"


// Функция для получения старшей цифры числа
// Принимает целое число, возвращает целую цифру
int get_first_digit(int number)
{
    number = abs(number);
    while (number >= 10)
        number /= 10;
    
    return number;  
}

// Функция для проверки, равное ли количество элементов массива начинаются и заканчиваются на одну цифру
// Принимает массив по указателю, его длину, и искомую цифру, возвращает результат проверки
bool is_num_starts_same_as_ends(int array[], size_t length, int digit)
{
    int num_starts = 0, num_ends = 0;

    for (size_t i = 0; i < length; i++)
    {
        if (abs(array[i]) % 10 == digit)
            num_ends++;
        if (get_first_digit(array[i]) == digit)
            num_starts++;
    }

    if (num_ends == 0 || num_starts == 0)
        return false;
    return num_starts == num_ends;
}

// Функция для добавления строки из чисел 100 по индексу
// Принимает количество строк и столбцов матрицы и индекс для вставки строки, изменяет значения матрицы по указателю
void insert_row_of_100(int matrix[][COLUMNS], size_t rows, size_t columns, size_t index)
{
    for (size_t i = rows - 1; i > index; i--)
        for (size_t j = 0; j < columns; j++)
            matrix[i][j] = matrix[i - 1][j];
    
    for (size_t j = 0; j < columns; j++)
        matrix[index][j] = 100;
}

// Функция для добавления строк из чисел 100 после строк по условию
// Принимает количество строк и столбцов матрицы, изменяет ее значения по указателю, возвращает новое количество строк
size_t add_rows(int matrix[][COLUMNS], size_t rows, size_t columns, int digit)
{
    for (size_t i = 0; i < rows; i++)
        if (is_num_starts_same_as_ends(matrix[i], columns, digit))
            insert_row_of_100(matrix, ++rows, columns, ++i);
    
    return rows;
}
