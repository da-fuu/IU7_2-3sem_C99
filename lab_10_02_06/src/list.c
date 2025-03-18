#include <stdlib.h>

#include "errors.h"
#include "struct.h"
#include "list.h"


// Функция освобождения списка
void free_list(node_t *head)
{
    node_t *temp;
    while (head != NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
}

// Функция компаратора местоположения элементов
int compare_elems(const data_t *elem_1, const data_t *elem_2)
{
    if (elem_1->row != elem_2->row)
        return elem_1->row - elem_2->row;
    return elem_1->col - elem_2->col;
}

// Функция записи элемента в конец списка
int push_end(node_t **head, node_t **end, data_t *data)
{
    if (*head == NULL)
    {
        *head = malloc(sizeof(node_t));
        *end = *head;
    }
    else
    {
        (*end)->next = malloc(sizeof(node_t));
        *end = (*end)->next;
    }
    if (*end == NULL)
        return ERR_NO_MEMORY;
    (*end)->data = *data;
    (*end)->next = NULL;
    return OK;
}

// Функция вставку второго списка в конец первого
void link_lists(node_t **head, node_t **head_to_end)
{
    node_t *end;
    if (*head == NULL)
    {
        *head = *head_to_end;
        *head_to_end = NULL;
        return;
    }
    end = *head;
    while (end->next != NULL)
    {
        end = end->next;
    }
    end->next = *head_to_end;
    *head_to_end = NULL;
}
