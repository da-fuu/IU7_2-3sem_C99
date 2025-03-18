#ifndef PROCESS_H__

#define PROCESS_H__

// Заголовочный файл файла для выполнения основного задания (работы с матрицей)

#include <stddef.h>
#include "config.h"


// Функция для заполнения целочисленными значениями 1 или 0 в зависимости от выполнения условия столбцом матрицы
// Принимает матрицу по указателю, количество строк и столбцов, изменяет значения массива по указателю 
void fill_array(int matrix[][COLUMNS], size_t rows, size_t columns, int array[]);


#endif	// #ifndef PROCESS_H__
