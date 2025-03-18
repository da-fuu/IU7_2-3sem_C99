#ifndef OPERATIONS_H__
#define OPERATIONS_H__

// Заголовочный файл файла для работы с универсальным списком

#include "struct.h"


// Функция поиска элемента в списке
node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));

// Функция удаления элемента из начала списка
void *pop_front(node_t **head);

// Функция разворота списка
node_t *reverse(node_t *head);


#endif // #ifndef OPERATIONS_H__
