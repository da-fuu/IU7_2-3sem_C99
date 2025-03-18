#include <stdlib.h>
#include <string.h>

#include "associative_array.h"
#include "dyn_array.h"


assoc_array_t assoc_array_create(void)
{
    assoc_array_t array = malloc(sizeof(struct assoc_array_type));
    if (array == NULL)
        return NULL;

    array->array = NULL;
    array->len = 0;
    array->capacity = 0;
    return array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
        return;

    for (int i = 0; i < (*arr)->len; i++)
        free((*arr)->array[i].key);
    free((*arr)->array);
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    int index;
    pair_t *new_arr;
    int new_cap;

    if (arr == NULL || key == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    if (find_array(arr->array, arr->len, key, &index))
        return ASSOC_ARRAY_KEY_EXISTS;

    if (arr->len >= arr->capacity)
    {
        new_cap = arr->capacity * 2 + 1;
        new_arr = realloc(arr->array, new_cap * sizeof(pair_t));
        if (new_arr == NULL)
            return ASSOC_ARRAY_MEM;
        arr->array = new_arr;
        arr->capacity = new_cap;
    }


    rshift(arr->array, ++(arr->len), index);
    arr->array[index].key = malloc((strlen(key) + 1) * sizeof(char));
    if (arr->array[index].key == NULL)
        return ASSOC_ARRAY_MEM;
    strcpy(arr->array[index].key, key);
    arr->array[index].value = num;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    int index;

    if (arr == NULL || key == NULL || key[0] == '\0' || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!find_array(arr->array, arr->len, key, &index))
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->array[index].value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    int index;

    if (arr == NULL || key == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!find_array(arr->array, arr->len, key, &index))
        return ASSOC_ARRAY_NOT_FOUND;

    free(arr->array[index].key);
    lshift(arr->array, --(arr->len), index);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (int i = 0; i < arr->len; i++)
        free(arr->array[i].key);
    arr->len = 0;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (int i = 0; i < arr->len; i++)
        action(arr->array[i].key, &arr->array[i].value, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;
    *num = &arr->array[0].value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;
    *num = &arr->array[arr->len - 1].value;

    return ASSOC_ARRAY_OK;
}
