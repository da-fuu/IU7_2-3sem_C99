#ifndef FILE_H__

#define FILE_H__

// Заголовочный файл файла для выполнения основного задания (работы с файлом)


#include <stdio.h>


// Функция для подсчета дисперсии в последовательности чисел файла
// Принимает файловую переменную, изменяет по указателю переменную дисперсии
// Возвращает код ошибки
int find_disp(FILE *f, double *dispersion);


#endif	// #ifndef FILE_H__
