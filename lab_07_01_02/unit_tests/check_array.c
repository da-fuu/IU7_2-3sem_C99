#include <check.h>
#include <malloc.h>
#include "array.h"
#include "errors.h"
#include "check_array.h"


// Пустой массив на вход фильтрации
START_TEST(key_empty_arr)
{
    int arr[] = { 1, 2 };
    int *pbs = arr;
    int *pes = pbs;
    int *pbd, *ped;
    int rc;

    rc = key(pbs, pes, &pbd, &ped);
    ck_assert_int_eq(rc, ERR_INVALID_ARR);
}
END_TEST

// Один из указателей на массив NULL на вход фильтрации
START_TEST(key_null_src)
{
    int arr[] = { 1, 2 };
    int *pbs = arr;
    int *pes = NULL;
    int *pbd, *ped;
    int rc;

    rc = key(pbs, pes, &pbd, &ped);
    ck_assert_int_eq(rc, ERR_NULLPTR);
}
END_TEST

// Один из указателей на указатель выходного массива NULL на вход фильтрации
START_TEST(key_null_dst)
{
    int arr[2] = { 1, 2 };
    int *pbs = arr;
    int *pes = arr + 2;
    int *ped;
    int rc;

    rc = key(pbs, pes, NULL, &ped);
    ck_assert_int_eq(rc, ERR_NULLPTR);
}
END_TEST

// После фильтрации пустой массив
START_TEST(key_empty_out_arr)
{
    int arr[] = { -3, 1, 2 };
    int *pbs = arr;
    int *pes = arr + 3;
    int *pbd, *ped;
    int rc;

    rc = key(pbs, pes, &pbd, &ped);
    ck_assert_int_eq(rc, ERR_EMPTY_OUT);
}
END_TEST


// Фильтрация массива из одного элемента
START_TEST(key_one_elem)
{
    int arr[] = { 2 };
    int *pbs = arr;
    int *pes = arr + 1;
    int *pbd, *ped;
    int rc;

    rc = key(pbs, pes, &pbd, &ped);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(1, ped - pbd);
    ck_assert_mem_eq(arr, pbd, sizeof(int) * 1);
    free(pbd);
}
END_TEST

// Первый отрицательный элемент последний
START_TEST(key_neg_elem_last)
{
    int arr[] = { 2, 1, -4 };
    int *pbs = arr;
    int *pes = arr + 3;
    int *pbd, *ped;
    int rc;

    rc = key(pbs, pes, &pbd, &ped);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(2, ped - pbd);
    ck_assert_mem_eq(arr, pbd, sizeof(int) * 2);
    free(pbd);
}
END_TEST

// Все элементы положительны
START_TEST(key_all_elems)
{
    int arr[] = { 2, 1, 4 };
    int *pbs = arr;
    int *pes = arr + 3;
    int *pbd, *ped;
    int rc;

    rc = key(pbs, pes, &pbd, &ped);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(3, ped - pbd);
    ck_assert_mem_eq(arr, pbd, sizeof(int) * 3);
    free(pbd);
}
END_TEST

// Функция объединения тестов фильтрации в набор
Suite* key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, key_empty_arr);
    tcase_add_test(tc_neg, key_null_src);
    tcase_add_test(tc_neg, key_null_dst);
    tcase_add_test(tc_neg, key_empty_out_arr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, key_one_elem);
    tcase_add_test(tc_pos, key_neg_elem_last);
    tcase_add_test(tc_pos, key_all_elems);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Пустой массив на вход сортировки
START_TEST(mysort_empty_arr)
{
    int arr[] = { 1, 2, 3 };
    int rc;

    rc = mysort(arr, 0, sizeof(int), compare_int);
    ck_assert_int_eq(rc, ERR_INVALID_ARR);
}
END_TEST

// Массив из элементов размером 0 на вход сортировки
START_TEST(mysort_zerosize_elems)
{
    int arr[] = { 1, 2, 3 };
    int rc;

    rc = mysort(arr, 3, 0, compare_int);
    ck_assert_int_eq(rc, ERR_INVALID_ARR);
}
END_TEST

// NULL вместо массива на вход сортировки
START_TEST(mysort_nullptr_arr)
{
    int rc;

    rc = mysort(NULL, 1, sizeof(int), compare_int);
    ck_assert_int_eq(rc, ERR_NULLPTR);
}
END_TEST

// NULL вместо компаратора на вход сортировки
START_TEST(mysort_nullptr_compar)
{
    int arr[] = { 1, 2, 3 };
    int rc;

    rc = mysort(arr, 3, sizeof(int), NULL);
    ck_assert_int_eq(rc, ERR_NULLPTR);
}
END_TEST


// Сортировка отсортированного массива
START_TEST(mysort_sorted)
{
    int arr[] = { -2, 1, 2, 3 };
    int arr_s[] = { -2, 1, 2, 3 };
    int rc;

    rc = mysort(arr, 4, sizeof(int), compare_int);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_s, sizeof(arr_s));
}
END_TEST

// Сортировка отсортированного в обратном порядке массива
START_TEST(mysort_reversed)
{
    int arr[] = { 3, 2, 1, -2 };
    int arr_s[] = { -2, 1, 2, 3 };
    int rc;

    rc = mysort(arr, 4, sizeof(int), compare_int);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_s, sizeof(arr_s));
}
END_TEST

// Сортировка перемешанного массива
START_TEST(mysort_unordered)
{
    int arr[] = { 2, 5, 0, 1, 4 };
    int arr_s[] = { 0, 1, 2, 4, 5 };
    int rc;

    rc = mysort(arr, 5, sizeof(int), compare_int);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_s, sizeof(arr_s));
}
END_TEST

// Сортировка массива из одинаковых элементов
START_TEST(mysort_same_elem)
{
    int arr[] = { 0, 0, 0, 0 };
    int arr_s[] = { 0, 0, 0, 0 };
    int rc;

    rc = mysort(arr, 4, sizeof(int), compare_int);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_s, sizeof(arr_s));
}
END_TEST

// Сортировка массива из одного элемента
START_TEST(mysort_one_elem)
{
    int arr[] = { -2 };
    int arr_s[] = { -2 };
    int rc;

    rc = mysort(arr, 1, sizeof(int), compare_int);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_s, sizeof(arr_s));
}
END_TEST

// Функция компаратора для вещественных чисел
// Принимает указатели на числа
// Возвращает знак разности чисел
int compare_double(const void *a, const void *b)
{
    double a_double = *(double *) a;
    double b_double = *(double *) b;
    if (a_double > b_double)
        return 1;
    if (a_double < b_double)
        return -1;
    return 0;
}

// Сортировка массива вещественных чисел
START_TEST(mysort_double)
{
    double arr[] = { 2.5, 5.0, 2.2, 0.0, 2.2, 4.9 };
    double arr_s[] = { 0.0, 2.2, 2.2, 2.5, 4.9, 5.0 };
    int rc;

    rc = mysort(arr, 6, sizeof(double), compare_double);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_s, sizeof(arr_s));
}
END_TEST

// Функция компаратора для символов
// Принимает указатели на символы
// Возвращает разность кодов символов
int compare_char(const void *a, const void *b)
{
    char a_char = *(char *) a;
    char b_char = *(char *) b;
    return a_char - b_char;
}

// Сортировка массива символов
START_TEST(mysort_char)
{
    char arr[] = { '1', 'a', '!', '\n', 'A' };
    char arr_s[] = { '\n', '!', '1', 'A', 'a' };
    int rc;

    rc = mysort(arr, 5, sizeof(char), compare_char);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_s, sizeof(arr_s));
}
END_TEST

// Функция объединения тестов сортировки в набор
Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("mysort");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, mysort_empty_arr);
    tcase_add_test(tc_neg, mysort_zerosize_elems);
    tcase_add_test(tc_neg, mysort_nullptr_arr);
    tcase_add_test(tc_neg, mysort_nullptr_compar);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, mysort_sorted);
    tcase_add_test(tc_pos, mysort_reversed);
    tcase_add_test(tc_pos, mysort_unordered);
    tcase_add_test(tc_pos, mysort_same_elem);
    tcase_add_test(tc_pos, mysort_one_elem);
    tcase_add_test(tc_pos, mysort_double);
    tcase_add_test(tc_pos, mysort_char);
    suite_add_tcase(s, tc_pos);

    return s;
}
