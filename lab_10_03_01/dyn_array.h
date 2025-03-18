#ifndef DYN_ARRAY_H__
#define DYN_ARRAY_H__

#include <stdbool.h>


// Структура пары ключ-значение
typedef struct
{
    char *key;
    int value;
} pair_t;

struct assoc_array_type
{
    pair_t *array;
    int len;
    int capacity;
};


// Левый сдвиг массива
void lshift(pair_t *array, int new_len, int index);

// Правый сдвиг массива
void rshift(pair_t *array, int new_len, int index);

// Функция бинарного поиска в массиве
bool find_array(pair_t *array, int len, const char *key, int *index);


#endif // #ifndef DYN_ARRAY_H__
