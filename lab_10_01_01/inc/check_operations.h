#ifndef CHECK_OPERATIONS_H__
#define CHECK_OPERATIONS_H__

// Заголовочный файл файла для работы с модульными тестами

#include <check.h>

#include "struct.h"

#define ARR_LEN(a) (sizeof(a) / sizeof((a)[0]))


// Функция объединения тестов поиска в набор
Suite *find_suite(void);

// Функция объединения тестов удаления элемента из начала в набор
Suite *pop_front_suite(void);

// Функция объединения тестов разворота в набор
Suite *reverse_suite(void);

node_t *create_list_int(int arr[], int len);

void assert_list_eq(node_t *in1, node_t *in2, int (*comparator)(const void *, const void *));

int compare_int(const void *in1, const void *in2);

void free_int_list(node_t *head);


#endif // #ifndef CHECK_OPERATIONS_H__
