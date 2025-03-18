#include <stdlib.h>

#include "operations.h"


// Функция поиска элемента в списке
node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    if (head == NULL || comparator == NULL)
        return NULL;
    while (head != NULL)
    {
        if (comparator(data, head->data) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// Функция удаления элемента из начала списка
void *pop_front(node_t **head)
{
    void *data;
    node_t *temp;

    if (head == NULL || *head == NULL)
        return NULL;

    temp = *head;
    data = temp->data;
    *head = temp->next;
    free(temp);
    return data;
}

// Функция разворота списка
node_t *reverse(node_t *head)
{
    node_t *next, *prev;

    if (head == NULL || head->next == NULL)
        return head;

    prev = head;
    head = head->next;
    prev->next = NULL;
    while ((next = head->next) != NULL)
    {
        head->next = prev;
        prev = head;
        head = next;
    }
    head->next = prev;
    return head;
}
