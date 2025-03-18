#ifndef LIB_ARRAY_H__
#define LIB_ARRAY_H__

// Заголовочный файл файла для работы с массивом

#include <stddef.h>

#ifdef DYNLOAD

typedef int (*key_t)(const int *, const int *, int *, int **);
typedef int (*compar_t)(const void *a, const void *b);
typedef int (*mysort_t)(void *, size_t, size_t, compar_t);

#else

// Функция фильтрации массива
// Принимает указатели на начало и конец массива, указатель на конец выходного массива, 
// изменяет по указателю указатель на конец выходного массива. Возвращает код ошибки
int key(const int *pb_src, const int *pe_src, int *pb_dst, int **pe_dst);

// Функция для модифицированной сортировки пузырьком
// Принимает указатель на массив, количество элементов, размер элемента, указатель на функцию-компаратор
// Возвращает код ошибки
int mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// Функция компаратора для целых чисел
// Принимает указатели на числа
// Возвращает разность чисел
int compare_int(const void *a, const void *b);

#endif // #ifdef DYNLOAD

#endif // #ifndef LIB_ARRAY_H__
