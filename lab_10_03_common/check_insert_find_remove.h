#ifndef CHECK_INSERT_FIND_REMOVE_H__
#define CHECK_INSERT_FIND_REMOVE_H__

// Заголовочный файл файла для работы с модульными тестами вставки, поиска и удаления

#include <check.h>


// Функция объединения тестов вставки в набор
Suite *insert_suite(void);

// Функция объединения тестов поиска в набор
Suite *find_suite(void);

// Функция объединения тестов удаления в набор
Suite *remove_suite(void);


#endif // #ifndef CHECK_INSERT_FIND_REMOVE_H__
