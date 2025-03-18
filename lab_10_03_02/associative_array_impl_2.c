#include <stdlib.h>
#include <string.h>

#include "associative_array.h"
#include "list.h"


assoc_array_t assoc_array_create(void)
{
    assoc_array_t array = malloc(sizeof(struct assoc_array_type));
    if (array == NULL)
        return NULL;

    array->head = NULL;
    return array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
        return;

    free_list((*arr)->head);
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    node_t *new_node;

    if (arr == NULL || key == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    if (find_list(arr->head, key) != NULL)
        return ASSOC_ARRAY_KEY_EXISTS;

    new_node = malloc(sizeof(node_t));
    if (new_node == NULL)
        return ASSOC_ARRAY_MEM;

    new_node->key = malloc((strlen(key) + 1) * sizeof(char));
    if (new_node->key == NULL)
        return ASSOC_ARRAY_MEM;

    strcpy(new_node->key, key);
    new_node->value = num;
    new_node->next = arr->head;
    arr->head = new_node;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    node_t *found;
    if (arr == NULL || key == NULL || key[0] == '\0' || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    found = find_list(arr->head, key);
    if (found == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &found->value;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    node_t *found;
    if (arr == NULL || key == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    found = find_list(arr->head, key);
    if (found == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    remove_node(&arr->head, found);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    free_list(arr->head);
    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    node_t *curr;

    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    curr = arr->head;
    while (curr != NULL)
    {
        action(curr->key, &curr->value, param);
        curr = curr->next;
    }
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    node_t *curr;
    node_t *min = NULL;

    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    curr = arr->head;
    while (curr != NULL)
    {
        if (min == NULL || strcmp(curr->key, min->key) < 0)
            min = curr;
        curr = curr->next;
    }
    if (min == NULL)
        return ASSOC_ARRAY_NOT_FOUND;
    *num = &min->value;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    node_t *curr;
    node_t *max = NULL;

    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    curr = arr->head;
    while (curr != NULL)
    {
        if (max == NULL || strcmp(curr->key, max->key) > 0)
            max = curr;
        curr = curr->next;
    }
    if (max == NULL)
        return ASSOC_ARRAY_NOT_FOUND;
    *num = &max->value;
    return ASSOC_ARRAY_OK;
}
