#ifndef PROCESS_H__

#define PROCESS_H__

// Заголовочный файл файла для выполнения основного задания (работы с матрицей)

#include <stddef.h>
#include "config.h"

// Функция сортировки строк в матрице по возрастанию суммы элементов
// Принимает количество строк и столбцов матрицы и изменяет ее значения по указателю
void sort_matrix_rows(int matrix[][COLUMNS], size_t rows, size_t columns);


#endif	// #ifndef PROCESS_H__
