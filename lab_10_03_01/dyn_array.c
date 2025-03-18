#include <string.h>

#include "dyn_array.h"


// Левый сдвиг массива
void lshift(pair_t *array, int new_len, int index)
{
    for (int i = index; i < new_len; i++)
        array[i] = array[i + 1];
}

// Правый сдвиг массива
void rshift(pair_t *array, int new_len, int index)
{
    for (int i = new_len - 1; i > index; i--)
        array[i] = array[i - 1];
}

// Функция бинарного поиска в массиве
bool find_array(pair_t *array, int len, const char *key, int *index)
{
    int left = 0;
    int right = len - 1;
    int mid;
    int diff;

    while (left <= right)
    {
        mid = (left + right) / 2;
        diff = strcmp(array[mid].key, key);

        if (diff == 0)
        {
            *index = mid;
            return true;
        }
        if (diff < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    *index = left;
    return false;
}
