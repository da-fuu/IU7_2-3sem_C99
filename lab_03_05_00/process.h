#ifndef PROCESS_H__

#define PROCESS_H__

// Заголовочный файл файла для выполнения основного задания (работы с матрицей)

#include <stddef.h>
#include "config.h"


// Функция заполнения массива простыми элементами матрицы
// Принимает матрицу по указателю, количество ее строк и столбцов, изменяет элементы массива по указателю, возвращает длину массива
size_t fill_array_with_primes(int matrix[][COLUMNS], size_t rows, size_t columns, int array_primes[]);

// Функция разворота массива
// Принимает длину массива и изменяет его элементы по указателю
void reverse_array(int array[], size_t length);

// Функция вставки в простые элементы матрицы элементы массива(допускает что количество простых чисел равно длине массива)
// Принимает матрицу по указателю, количество ее строк и столбцов и массив по указателю, изменяет элементы матрицы по указателю
void insert_nums_in_primes(int matrix[][COLUMNS], size_t rows, size_t columns, int array_primes[]);


#endif	// #ifndef PROCESS_H__
