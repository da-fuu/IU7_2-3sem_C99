#ifndef CHECK_CREATE_CLEAR_DESTROY_H__
#define CHECK_CREATE_CLEAR_DESTROY_H__

// Заголовочный файл файла для работы с модульными тестами создания, опустошения и очистки

#include <check.h>


// Функция объединения тестов создания в набор
Suite *create_suite(void);

// Функция объединения тестов очистки массива в набор
Suite *clear_suite(void);

// Функция объединения тестов очистки памяти из-под массива в набор
Suite *destroy_suite(void);


#endif // #ifndef CHECK_CREATE_CLEAR_DESTROY_H__
