#include "associative_array.h"
#include "check_insert_find_remove.h"


// Указатель на NULL вместо массива
START_TEST(insert_null_arr)
{
    assoc_array_error_t rc;

    rc = assoc_array_insert(NULL, "a", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Указатель на NULL вместо ключа
START_TEST(insert_null_key)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_insert(array, NULL, 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Пустой ключ
START_TEST(insert_empty_key)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_insert(array, "", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Ключ уже есть в массиве
START_TEST(insert_same_key)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", 5);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&array);
}
END_TEST


// Вставка в пустой массив
START_TEST(insert_empty)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_insert(array, "zov", 333);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "zov", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 333);

    assoc_array_destroy(&array);
}
END_TEST

// Вставка в непустой массив
START_TEST(insert_many)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "zov", 333);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "ann", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, -10);
    rc = assoc_array_find(array, "wa", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 166);
    rc = assoc_array_find(array, "waa", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 166);
    rc = assoc_array_find(array, "zov", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 333);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов вставки в набор
Suite *insert_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("insert");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо массива
    tcase_add_test(tc_neg, insert_null_arr);
    // Указатель на NULL вместо ключа
    tcase_add_test(tc_neg, insert_null_key);
    // Пустой ключ
    tcase_add_test(tc_neg, insert_empty_key);
    // Ключ уже есть в массиве
    tcase_add_test(tc_neg, insert_same_key);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Вставка в пустой массив
    tcase_add_test(tc_pos, insert_empty);
    // Вставка в непустой массив
    tcase_add_test(tc_pos, insert_many);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Указатель на NULL вместо массива
START_TEST(find_null_arr)
{
    assoc_array_error_t rc;
    int *tmp;

    rc = assoc_array_find(NULL, "a", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Указатель на NULL вместо ключа
START_TEST(find_null_key)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, NULL, &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Пустой ключ
START_TEST(find_empty_key)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Указатель на NULL вместо выходного указателя
START_TEST(find_null_out)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "waa", NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Пустой массив
START_TEST(find_empty_arr)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_find(array, "waa", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

// Искомого ключа нет в массиве
START_TEST(find_no_elem)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "zz", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST


// Массив из одного элемента
START_TEST(find_one_elem)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "wa", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 166);

    assoc_array_destroy(&array);
}
END_TEST

// Искомый элемент минимальный по ключу
START_TEST(find_min)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "zov", 333);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "ann", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, -10);

    assoc_array_destroy(&array);
}
END_TEST

// Искомый элемент максимальный по ключу
START_TEST(find_max)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "zov", 333);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(array, "zov", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(tmp);
    ck_assert_int_eq(*tmp, 333);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов поиска в набор
Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("find");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо массива
    tcase_add_test(tc_neg, find_null_arr);
    // Указатель на NULL вместо ключа
    tcase_add_test(tc_neg, find_null_key);
    // Пустой ключ
    tcase_add_test(tc_neg, find_empty_key);
    // Указатель на NULL вместо выходного указателя
    tcase_add_test(tc_neg, find_null_out);
    // Пустой массив
    tcase_add_test(tc_neg, find_empty_arr);
    // Искомого ключа нет в массиве
    tcase_add_test(tc_neg, find_no_elem);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Массив из одного элемента
    tcase_add_test(tc_pos, find_one_elem);
    // Искомый элемент минимальный по ключу
    tcase_add_test(tc_pos, find_min);
    // Искомый элемент максимальный по ключу
    tcase_add_test(tc_pos, find_max);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Указатель на NULL вместо массива
START_TEST(remove_null_arr)
{
    assoc_array_error_t rc;

    rc = assoc_array_remove(NULL, "a");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Указатель на NULL вместо ключа
START_TEST(remove_null_key)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(array, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Пустой ключ
START_TEST(remove_empty_key)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(array, "");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&array);
}
END_TEST

// Пустой массив
START_TEST(remove_empty_arr)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);

    rc = assoc_array_remove(array, "waa");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

// Искомого ключа нет в массиве
START_TEST(remove_no_elem)
{
    assoc_array_error_t rc;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(array, "zz");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST


// Массив из одного элемента
START_TEST(remove_one_elem)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(array, "wa");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(array, "wa", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

// Искомый элемент минимальный по ключу
START_TEST(remove_min)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "zov", 333);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(array, "ann");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(array, "ann", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

// Искомый элемент максимальный по ключу
START_TEST(remove_max)
{
    assoc_array_error_t rc;
    int *tmp;
    assoc_array_t array = assoc_array_create();
    ck_assert_ptr_nonnull(array);
    rc = assoc_array_insert(array, "waa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "ann", -10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "wa", 166);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(array, "zov", 333);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(array, "zov");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_find(array, "zov", &tmp);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}
END_TEST

// Функция объединения тестов удаления в набор
Suite *remove_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("remove");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо массива
    tcase_add_test(tc_neg, remove_null_arr);
    // Указатель на NULL вместо ключа
    tcase_add_test(tc_neg, remove_null_key);
    // Пустой ключ
    tcase_add_test(tc_neg, remove_empty_key);
    // Пустой массив
    tcase_add_test(tc_neg, remove_empty_arr);
    // Искомого ключа нет в массиве
    tcase_add_test(tc_neg, remove_no_elem);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Массив из одного элемента
    tcase_add_test(tc_pos, remove_one_elem);
    // Искомый элемент минимальный по ключу
    tcase_add_test(tc_pos, remove_min);
    // Искомый элемент максимальный по ключу
    tcase_add_test(tc_pos, remove_max);
    suite_add_tcase(s, tc_pos);

    return s;
}
