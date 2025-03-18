#ifndef PROCESS_H__

#define PROCESS_H__

// Заголовочный файл файла для выполнения основного задания (работы с матрицей)

#include <stddef.h>
#include "config.h"


// Функция для нахождения минимального нечетного элемента под главной диагональю
// Принимает матрицу по указателю и количество строк(столбцов), изменяет искомое число по указателю, возвращает код ошибки
int find_min_odd_under_diag(int matrix[][DIMENSION], size_t dimension, int *out);


#endif	// #ifndef PROCESS_H__
