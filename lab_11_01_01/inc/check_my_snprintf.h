#ifndef CHECK_MY_SNPRINTF_H__
#define CHECK_MY_SNPRINTF_H__

#include <check.h>


// Функция объединения тестов всех спецификаторов в набор
Suite *all_suite(void);

// Функция объединения тестов спецификатора s в набор
Suite *s_suite(void);

// Функция объединения тестов спецификатора ho в набор
Suite *ho_suite(void);


#endif // #ifndef CHECK_MY_SNPRINTF_H__
