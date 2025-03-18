#include <stddef.h>

#include "sort.h"


// Функция поиска длины списка
size_t len(node_t *head)
{
    size_t ind = 0;
    while (head != NULL)
    {
        ind++;
        head = head->next;
    }
    return ind;
}

// Функция разбиения одного списка на 2 половины
void front_back_split(node_t *head, node_t **back)
{
    size_t list_len;

    if (back == NULL)
        return;

    list_len = len(head);
    if (list_len == 0)
    {
        *back = NULL;
        return;
    }

    for (size_t i = 0; i < (list_len - 1) / 2; i++)
        head = head->next;

    *back = head->next;
    head->next = NULL;
}

// Функция слияния 2 упорядоченных списков
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t *new_head = NULL;
    node_t *end;
    node_t *cur;

    if (head_a == NULL || head_b == NULL || comparator == NULL)
        return NULL;

    while (*head_a != NULL && *head_b != NULL)
    {
        if (comparator((*head_a)->data, (*head_b)->data) <= 0)
        {
            cur = *head_a;
            *head_a = (*head_a)->next;
        }
        else
        {
            cur = *head_b;
            *head_b = (*head_b)->next;
        }
        if (new_head == NULL)
        {
            new_head = cur;
            end = cur;
        }
        end->next = cur;
        end = cur;
    }

    if (*head_a != NULL)
    {
        if (new_head == NULL)
            new_head = *head_a;
        else
            end->next = *head_a;
        *head_a = NULL;
    }
    else if (*head_b != NULL)
    {
        if (new_head == NULL)
            new_head = *head_b;
        else
            end->next = *head_b;
        *head_b = NULL;
    }

    return new_head;
}

// Функция сортировки списков
node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *back;

    if (comparator == NULL)
        return NULL;

    front_back_split(head, &back);

    if (head != NULL && head->next != NULL)
        head = sort(head, comparator);
    if (back != NULL && back->next != NULL)
        back = sort(back, comparator);

    return sorted_merge(&head, &back, comparator);
}
