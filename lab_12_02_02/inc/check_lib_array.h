#ifndef CHECK_ARRAY_H__
#define CHECK_ARRAY_H__

// Заголовочный файл файла для работы с модульными тестами

#include <check.h>

#define ERR_UNIT_FAIL 10


// Функция объединения тестов заполнения числами Фибоначчи в набор
Suite *fill_fib_suite(void);

// Функция объединения тестов копирования уникальных элементов в набор
Suite *copy_uniq_elems_suite(void);


#endif // #ifndef CHECK_ARRAY_H__
