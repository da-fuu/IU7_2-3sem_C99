#ifndef FILE_H__
#define FILE_H__

#include <stddef.h>


// Чтение размерностей квадратной матрицы из файла
// Принимает имя файла, изменяет размерность по указателю, возвращает код ошибки
int read_dimensions(char *filename, int *n);

// Чтение квадратной матрицы из файла
// Принимает имя файла, матрицу и размерность, изменяет матрицу, возвращает код ошибки
int read_matrix(char *filename, int **matrix, int n);

// Запись квадратной матрицы в файл
// Принимает матрицу и размерность, возвращает код ошибки
int write_sq_matrix(int **matrix, int n, char *filename);


#endif // #ifndef FILE_H__
