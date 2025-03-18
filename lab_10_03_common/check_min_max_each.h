#ifndef CHECK_MIN_MAX_EACH_H__
#define CHECK_MIN_MAX_EACH_H__

// Заголовочный файл файла для работы с модульными тестами поиска минимума, максимума и применения функции ко всем элементам

#include <check.h>


// Функция объединения тестов поиска минимума в набор
Suite *min_suite(void);

// Функция объединения тестов поиска максимума в набор
Suite *max_suite(void);

// Функция объединения тестов применения функции ко всем элементам в набор
Suite *each_suite(void);


#endif // #ifndef CHECK_MIN_MAX_EACH_H__
