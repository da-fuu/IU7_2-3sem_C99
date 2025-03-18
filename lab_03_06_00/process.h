#ifndef PROCESS_H__

#define PROCESS_H__

// Заголовочный файл файла для выполнения основного задания (работы с матрицей)

#include <stddef.h>
#include "config.h"


// Функция для заполнения матрицы ходом быка
// Принимает количество строк и столбцов матрицы, изменяет ее значения по указателю
void fill_matrix(int matrix[][COLUMNS], size_t rows, size_t columns);


#endif	// #ifndef PROCESS_H__
