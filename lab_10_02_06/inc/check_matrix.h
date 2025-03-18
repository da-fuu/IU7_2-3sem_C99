#ifndef CHECK_MATRIX_H__
#define CHECK_MATRIX_H__

// Заголовочный файл файла для работы с модульными тестами

#include <check.h>


// Функция объединения тестов сложения матриц в набор
Suite *add_matrices_suite(void);

// Функция объединения тестов умножения матриц в набор
Suite *mul_matrices_suite(void);

// Функция объединения тестов на удаление строки с максимальным элементом в набор
Suite *remove_row_with_max_suite(void);


#endif // #ifndef CHECK_MATRIX_H__
