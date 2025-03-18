#include "associative_array.h"
#include "check_create_clear_destroy.h"


// Обычное создание
START_TEST(create_default)
{
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов создания в набор
Suite *create_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("create");

    tc_pos = tcase_create("positives");
    // Обычное создание
    tcase_add_test(tc_pos, create_default);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Указатель на NULL вместо массива
START_TEST(clear_nullptr)
{
    assoc_array_error_t rc;

    rc = assoc_array_clear(NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


// Очистка пустого массива
START_TEST(clear_empty)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_clear(array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&array);
}
END_TEST

// Очистка непустого массива
START_TEST(clear_nonempty)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_clear(array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(array, "a", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

// Очистка очищенного массива
START_TEST(clear_cleared)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_clear(array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(array, "a", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_clear(array);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов очистки массива в набор
Suite *clear_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("clear");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо массива
    tcase_add_test(tc_neg, clear_nullptr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Очистка пустого массива
    tcase_add_test(tc_pos, clear_empty);
    // Очистка непустого массива
    tcase_add_test(tc_pos, clear_nonempty);
    // Очистка очищенного массива
    tcase_add_test(tc_pos, clear_cleared);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Удаление пустого массива
START_TEST(destroy_empty)
{
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    assoc_array_destroy(&array);
    ck_assert_ptr_null(array);
}
END_TEST

// Удаление непустого массива
START_TEST(destroy_nonempty)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&array);
    ck_assert_ptr_null(array);
}
END_TEST

// Указатель на NULL вместо указателя на массив
START_TEST(destroy_nullptr)
{
    assoc_array_destroy(NULL);
}
END_TEST

// Указатель на NULL вместо массива
START_TEST(destroy_null_arr)
{
    assoc_array_t array = NULL;
    assoc_array_destroy(&array);
    ck_assert_ptr_null(array);
}
END_TEST

// Функция объединения тестов очистки памяти из-под массива в набор
Suite *destroy_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("destroy");

    tc_pos = tcase_create("positives");
    // Удаление пустого массива
    tcase_add_test(tc_pos, destroy_empty);
    // Удаление непустого массива
    tcase_add_test(tc_pos, destroy_nonempty);
    // Указатель на NULL вместо указателя на массив
    tcase_add_test(tc_pos, destroy_nullptr);
    // Указатель на NULL вместо массива
    tcase_add_test(tc_pos, destroy_null_arr);
    suite_add_tcase(s, tc_pos);

    return s;
}
