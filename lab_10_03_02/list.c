#include <stdlib.h>
#include <string.h>

#include "list.h"


// Функция освобождения списка
void free_list(node_t *head)
{
    node_t *temp;
    while (head != NULL)
    {
        free(head->key);
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Функция поиска в списке
node_t *find_list(node_t *head, const char *key)
{
    while (head != NULL)
    {
        if (strcmp(key, head->key) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// Функция удаления ноды из списка
void remove_node(node_t **head, node_t *node)
{
    node_t *curr;

    free(node->key);
    if (*head == node)
    {
        *head = node->next;
        free(node);
        return;
    }
    curr = *head;
    while (curr->next != node)
        curr = curr->next;

    curr->next = curr->next->next;
    free(node);
}
