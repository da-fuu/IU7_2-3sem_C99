#ifndef CHECK_OPERATIONS_H__
#define CHECK_OPERATIONS_H__

// Заголовочный файл файла для работы с модульными тестами

#include <check.h>


// Функция объединения тестов сложения матриц в набор
Suite *addition_suite(void);

// Функция объединения тестов умножения матриц в набор
Suite *multiplication_suite(void);

// Функция объединения тестов на решение СЛАУ в набор
Suite *solve_suite(void);


#endif // #ifndef CHECK_OPERATIONS_H__
