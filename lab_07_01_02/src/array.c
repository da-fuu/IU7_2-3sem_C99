#include <malloc.h>
#include "errors.h"
#include "array.h"


// Функция фильтрации массива
// Принимает указатели на начало и конец массива, изменяет по указателям указатели на начало и конец выходного массива
// Возвращает код ошибки
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    size_t new_len = 0;
    const int *curr;

    if (pb_src == NULL || pe_src == NULL || pb_dst == NULL || pe_dst == NULL)
        return ERR_NULLPTR;
    if (pb_src >= pe_src)
        return ERR_INVALID_ARR;

    curr = pb_src;
    while (curr < pe_src && *curr >= 0)
    {
        new_len++;
        curr++;
    }
    if (new_len == 0)
        return ERR_EMPTY_OUT;

    *pb_dst = malloc(sizeof(int) * new_len);
    if (*pb_dst == NULL)
        return ERR_NO_MEMORY;
    *pe_dst = *pb_dst;

    curr = pb_src;
    for (size_t i = 0; i < new_len; i++)
    {
        **pe_dst = *curr;
        curr++;
        (*pe_dst)++;
    }
    return OK;
}


// Функция обмена 2 областей памяти
// Принимает указатели и размер областей к обмену
static void swap(void *l, void *r, size_t size)
{
    char tmp;
    char *a_byte = l;
    char *b_byte = r;

    for (size_t i = 0; i < size; i++)
    {
        tmp = *a_byte;
        *a_byte = *b_byte;
        *b_byte = tmp;
        a_byte++;
        b_byte++;
    }
}


// Функция компаратора для целых чисел
// Принимает указатели на числа
// Возвращает разность чисел
int compare_int(const void *a, const void *b)
{
    int a_int = *(int *) a;
    int b_int = *(int *) b;
    return a_int - b_int;
}


// Функция для модифицированной сортировки пузырьком
// Принимает указатель на массив, количество элементов, размер элемента, указатель на функцию-компаратор
// Возвращает код ошибки
int mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    char *curr;
    char *begin = base;
    char *end, *new_end;

    if (base == NULL || compar == NULL)
        return ERR_NULLPTR;
    if (nmemb == 0 || size == 0)
        return ERR_INVALID_ARR;

    for (end = begin + (nmemb - 1) * size; begin < end; end = new_end)
    {
        new_end = end;
        for (curr = begin; curr < end; curr += size)
            if (compar(curr, curr + size) > 0)
            {
                swap(curr, curr + size, size);
                new_end = curr;
            }
        if (end == new_end)
            break;
    }
    return OK;
}
