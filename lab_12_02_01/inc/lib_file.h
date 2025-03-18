#ifndef LIB_FILE_H__
#define LIB_FILE_H__

// Заголовочный файл файла для работы с файлами

#include <stddef.h>

#ifdef DYNLOAD

typedef int (*find_file_len_t)(const char *, size_t *);
typedef void (*read_file_t)(const char *, int *, const int *);
typedef int (*write_file_t)(const char *, const int *, const int *);

#else

// Функция поиска количества чисел в файле
// Принимает имя файла, изменяет переменную количества по указателю
// Возвращает код ошибки
int find_file_len(const char *filename, size_t *len);

// Функция чтения данных из текстового файла в массив
// Принимает имя текстового файла, указатели на начало и конец массива
void read_file(const char *filename, int *ptr_beg, const int *ptr_end);

// Функция записи данных из массива текстовый файл
// Принимает имя текстового файла и указатели на начало и конец массива
// Возвращает код ошибки
int write_file(const char *filename, const int *ptr_beg, const int *ptr_end);

#endif // #ifdef DYNLOAD

#endif	// #ifndef LIB_FILE_H__
