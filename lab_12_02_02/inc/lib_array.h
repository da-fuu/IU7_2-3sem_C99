#ifndef LIBARRAY_H__
#define LIBARRAY_H__

#include <stddef.h>


#define OK 0
#define ERR_NULLPTR 1

// Функция заполнения массива числами Фибоначчи. Принимает указатель на массив и его размер
// Возвращает код ошибки
int fill_fib(int *array, size_t len);

// Функция копирования уникальных элементов из одного массива в другой
// Принимает указатель на первый массив, его размер, указатель на второй массив, изменяет по указателю его размер
// Возвращает код ошибки
int copy_uniq_elems(const int *src_array, size_t src_len, int *dst_array, size_t *dst_len);


#endif // #ifndef LIBARRAY_H__
