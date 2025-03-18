#ifndef CHECK_SORT_H__
#define CHECK_SORT_H__

// Заголовочный файл файла для работы с модульными тестами сортировки

#include <check.h>


// Функция объединения тестов разбиения в набор
Suite *front_back_split_suite(void);

// Функция объединения тестов слияния в набор
Suite *sorted_merge_suite(void);

// Функция объединения тестов сортировки в набор
Suite *sort_suite(void);


#endif // #ifndef CHECK_SORT_H__
