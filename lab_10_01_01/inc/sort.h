#ifndef SORT_H__
#define SORT_H__

// Заголовочный файл файла для сортировки универсального списка

#include "struct.h"


// Функция разбиения одного списка на 2 половины
void front_back_split(node_t *head, node_t **back);

// Функция слияния 2 упорядоченных списков
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

// Функция сортировки списков
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));


#endif // #ifndef SORT_H__
