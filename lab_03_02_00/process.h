#ifndef PROCESS_H__

#define PROCESS_H__

// Заголовочный файл файла для выполнения основного задания (работы с матрицей)

#include <stddef.h>
#include "config.h"


// Функция для добавления строк из чисел 100 после строк по условию
// Принимает количество строк и столбцов матрицы, изменяет ее значения по указателю, возвращает новое количество строк
size_t add_rows(int matrix[][COLUMNS], size_t rows, size_t columns, int digit);


#endif	// #ifndef PROCESS_H__
