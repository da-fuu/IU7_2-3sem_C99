#include <stdbool.h>

#include "lib_array.h"


// Функция заполнения массива числами Фибоначчи. Принимает указатель на массив и его размер
// Возвращает код ошибки
int fill_fib(int *array, size_t len)
{
    int a = 0;
    int b = 1;
    
    if (array == NULL)
        return ERR_NULLPTR;
    
    for (size_t i = 0; i < len; i++)
    {
        if (i % 2 == 0)
        {
            array[i] = a;
            a += b;
        }
        else
        {
            array[i] = b;
            b += a;
        }
    }
    return OK;
}


// Функция проверки нахождения элемента в массиве. Принимает указатель на массив, его размер и элемент к поиску
// Возвращает флаг результата проверки
static bool is_in_array(const int *array, size_t len, int elem)
{
    for (size_t i = 0; i < len; i++)
        if (array[i] == elem)
            return true;
    return false;
}

// Функция копирования уникальных элементов из одного массива в другой
// Принимает указатель на первый массив, его размер, указатель на второй массив, изменяет по указателю его размер
// Возвращает код ошибки
int copy_uniq_elems(const int *src_array, size_t src_len, int *dst_array, size_t *dst_len)
{
    if (src_array == NULL || dst_len == NULL)
        return ERR_NULLPTR;
    
    *dst_len = 0;
    for (size_t i = 0; i < src_len; i++)
        if (!is_in_array(src_array, i, src_array[i]))
        {
            if (dst_array != NULL)
                dst_array[(*dst_len)++] = src_array[i];
            else
                (*dst_len)++;
        }
    
    return OK;
}
