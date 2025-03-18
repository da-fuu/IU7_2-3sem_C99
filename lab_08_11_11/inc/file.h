#ifndef FILE_H__
#define FILE_H__

// Заголовочный файл файла для работы с файлами

#include "matrix.h"


// Функция чтения данных из текстового файла в матрицу
// Принимает имя текстового файла, изменяет матрицу по указателю
// Возвращает код ошибки
int read_matrix(const char *filename, matrix_t *matrix);

// Функция записи данных из матрицы в текстовый файл
// Принимает матрицу и имя текстового файла
// Возвращает код ошибки
int write_matrix(matrix_t matrix, const char *filename);


#endif	// #ifndef FILE_H__
