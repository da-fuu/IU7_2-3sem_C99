#ifndef LIST_H__
#define LIST_H__

// 

#include "struct.h"


// Функция освобождения списка
void free_list(node_t *head);

// Функция компаратора местоположения элементов
int compare_elems(const data_t *elem_1, const data_t *elem_2);

// Функция записи элемента в конец списка
int push_end(node_t **head, node_t **end, data_t *data);

// Функция вставку второго списка в конец первого
void link_lists(node_t **head, node_t **head_to_end);


#endif // #ifndef LIST_H__
