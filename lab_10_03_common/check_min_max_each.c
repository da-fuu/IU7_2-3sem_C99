#include "associative_array.h"
#include "check_min_max_each.h"


// Указатель на NULL вместо выходного массива
START_TEST(min_null_out)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_min(array, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Указатель на NULL вместо входного массива
START_TEST(min_null_arr)
{
    assoc_array_error_t rc;
    int *tmp;

    rc = assoc_array_min(NULL, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Пустой входной массив
START_TEST(min_empty_arr)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_min(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST


// Массив из одного элемента
START_TEST(min_one_elem)
{
    assoc_array_error_t rc;
    int *tmp = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_min(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 1);

    assoc_array_destroy(&array);
}
END_TEST

// Последний вставленный - минимальный
START_TEST(min_last_min)
{
    assoc_array_error_t rc;
    int *tmp = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "b", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "a", 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_min(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 10);

    assoc_array_destroy(&array);
}
END_TEST

// Первый вставленный - минимальный
START_TEST(min_first_min)
{
    assoc_array_error_t rc;
    int *tmp = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "aa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_min(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 166);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов поиска минимума в набор
Suite *min_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("min");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо выходного массива
    tcase_add_test(tc_neg, min_null_out);
    // Указатель на NULL вместо входного массива
    tcase_add_test(tc_neg, min_null_arr);
    // Пустой входной массив
    tcase_add_test(tc_neg, min_empty_arr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Массив из одного элемента
    tcase_add_test(tc_pos, min_one_elem);
    // Последний вставленный - минимальный
    tcase_add_test(tc_pos, min_last_min);
    // Первый вставленный - минимальный
    tcase_add_test(tc_pos, min_first_min);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Указатель на NULL вместо выходного массива
START_TEST(max_null_out)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_max(array, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Указатель на NULL вместо входного массива
START_TEST(max_null_arr)
{
    assoc_array_error_t rc;
    int *tmp;

    rc = assoc_array_max(NULL, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Пустой входной массив
START_TEST(max_empty_arr)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_max(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST


// Массив из одного элемента
START_TEST(max_one_elem)
{
    assoc_array_error_t rc;
    int *tmp = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_max(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 1);

    assoc_array_destroy(&array);
}
END_TEST

// Последний вставленный - максимальный
START_TEST(max_last_max)
{
    assoc_array_error_t rc;
    int *tmp = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "b", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ra", 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_max(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 10);

    assoc_array_destroy(&array);
}
END_TEST

// Первый вставленный - максимальный
START_TEST(max_first_max)
{
    assoc_array_error_t rc;
    int *tmp = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_max(array, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 166);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов поиска максимума в набор
Suite *max_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("max");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо выходного массива
    tcase_add_test(tc_neg, max_null_out);
    // Указатель на NULL вместо входного массива
    tcase_add_test(tc_neg, max_null_arr);
    // Пустой входной массив
    tcase_add_test(tc_neg, max_empty_arr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Массив из одного элемента
    tcase_add_test(tc_pos, max_one_elem);
    // Последний вставленный - максимальный
    tcase_add_test(tc_pos, max_last_max);
    // Первый вставленный - максимальный
    tcase_add_test(tc_pos, max_first_max);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Функция изменения пары ключ-значение - прибавляет либо число переданное в параметре,
// Либо, при его отсутствии - первый символ ключа приведенный к цифре ("3" == 3)
void add_first_char_or_param(const char *key, int *num, void *param)
{
    int *add;
    if (param == NULL)
    {
        *num += key[0] - '0';
        return;
    }
    add = param;
    *num += *add;
}


// Указатель на NULL вместо массива
START_TEST(each_null_arr)
{
    assoc_array_error_t rc;
    int tmp = 4;

    rc = assoc_array_each(NULL, add_first_char_or_param, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Указатель на NULL вместо функции
START_TEST(each_null_action)
{
    assoc_array_error_t rc;
    int tmp = -4;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_each(array, NULL, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST


// Пустой массив
START_TEST(each_empty)
{
    assoc_array_error_t rc;
    int tmp = 4;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_each(array, add_first_char_or_param, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&array);
}
END_TEST

// Параметр функции - NULL
START_TEST(each_param_null)
{
    assoc_array_error_t rc;
    int *out = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "4", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "5", -4);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_each(array, add_first_char_or_param, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(array, "4", &out);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(out);
    ck_assert_int_eq(*out, 5);
    rc = assoc_array_find(array, "5", &out);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(out);
    ck_assert_int_eq(*out, 1);

    assoc_array_destroy(&array);
}
END_TEST

// Параметр функции - указатель на целое
START_TEST(each_param_nonnull)
{
    assoc_array_error_t rc;
    int tmp = 4;
    int *out = NULL;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "b", -4);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_each(array, add_first_char_or_param, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(array, "a", &out);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(out);
    ck_assert_int_eq(*out, 5);
    rc = assoc_array_find(array, "b", &out);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(out);
    ck_assert_int_eq(*out, 0);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов применения функции ко всем элементам в набор
Suite *each_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("each");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо массива
    tcase_add_test(tc_neg, each_null_arr);
    // Указатель на NULL вместо функции
    tcase_add_test(tc_neg, each_null_action);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Пустой массив
    tcase_add_test(tc_pos, each_empty);
    // Параметр функции - NULL
    tcase_add_test(tc_pos, each_param_null);
    // Параметр функции - указатель на целое
    tcase_add_test(tc_pos, each_param_nonnull);
    suite_add_tcase(s, tc_pos);

    return s;
}
