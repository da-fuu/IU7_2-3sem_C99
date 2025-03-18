#include "lib_array.h"
#include "check_lib_array.h"


// Указатель на массив NULL
START_TEST(fill_fib_nullptr)
{
    int rc;

    rc = fill_fib(NULL, 0);
    ck_assert_int_eq(rc, ERR_NULLPTR);
}
END_TEST


// Заполнение массива из одного элемента
START_TEST(fill_fib_one_elem)
{
    size_t len = 1;
    int arr[1];
    int res[] = { 0 };
    int rc;
    
    rc = fill_fib(arr, len);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, res, sizeof(int) * len);
}
END_TEST

// Заполнение массива из двух элемента
START_TEST(fill_fib_two_elems)
{
    size_t len = 2;
    int arr[2];
    int res[] = { 0, 1 };
    int rc;
    
    rc = fill_fib(arr, len);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, res, sizeof(int) * len);
}
END_TEST

// Заполнение массива из нескольких элемента
START_TEST(fill_fib_many_elems)
{
    size_t len = 9;
    int arr[9];
    int res[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21 };
    int rc;
    
    rc = fill_fib(arr, len);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, res, sizeof(int) * len);
}

// Заполнение пустого массива
START_TEST(fill_fib_empty)
{
    size_t len = 0;
    int arr[1];
    int rc;
    
    rc = fill_fib(arr, len);
    ck_assert_int_eq(rc, OK);
}
END_TEST


// Функция объединения тестов заполнения числами Фибоначчи в набор
Suite *fill_fib_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("fill_fib");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, fill_fib_nullptr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, fill_fib_one_elem);
    tcase_add_test(tc_pos, fill_fib_two_elems);
    tcase_add_test(tc_pos, fill_fib_many_elems);
    tcase_add_test(tc_pos, fill_fib_empty);
    suite_add_tcase(s, tc_pos);

    return s;
}


// NULL вместо массива
START_TEST(copy_uniq_elems_nullptr_arr)
{
    int dst_arr[1];
    size_t dst_len;
    int rc;

    rc = copy_uniq_elems(NULL, 1, dst_arr, &dst_len);
    ck_assert_int_eq(rc, ERR_NULLPTR);
}
END_TEST

// NULL вместо указателя на выходную длину
START_TEST(copy_uniq_elems_nullptr_dst_len)
{
    int src_arr[] = { 1, 2, 1 };
    int dst_arr[3];
    int rc;

    rc = copy_uniq_elems(src_arr, 3, dst_arr, NULL);
    ck_assert_int_eq(rc, ERR_NULLPTR);
}
END_TEST


// Все элементы уникальные
START_TEST(copy_uniq_elems_all_uniq)
{
    int arr[] = { -2, 1, 2, 3 };
    int arr_dst[4];
    size_t dst_len;
    int arr_res[] = { -2, 1, 2, 3 };
    int rc;

    rc = copy_uniq_elems(arr, 4, arr_dst, &dst_len);
    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(dst_len, 4);
    ck_assert_mem_eq(arr_dst, arr_res, sizeof(int) * 4);
}
END_TEST

// Все элементы одинаковые
START_TEST(copy_uniq_elems_all_same)
{
    int arr[] = { 3, 3, 3, 3 };
    int arr_dst[1];
    size_t dst_len;
    int arr_res[] = { 3 };
    int rc;

    rc = copy_uniq_elems(arr, 4, arr_dst, &dst_len);
    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(dst_len, 1);
    ck_assert_mem_eq(arr_dst, arr_res, sizeof(int) * 1);
}
END_TEST

// И уникальные, и повторяющиеся элементы
START_TEST(copy_uniq_elems_mixed)
{
    int arr[] = { 3, 3, 4, 5, 4, 6, 5 };
    int arr_dst[4];
    size_t dst_len;
    int arr_res[] = { 3, 4, 5, 6 };
    int rc;

    rc = copy_uniq_elems(arr, 7, arr_dst, &dst_len);
    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(dst_len, 4);
    ck_assert_mem_eq(arr_dst, arr_res, sizeof(int) * 4);
}
END_TEST

// Один элемент
START_TEST(copy_uniq_elems_one_elem)
{
    int arr[] = { 3 };
    int arr_dst[1];
    size_t dst_len;
    int arr_res[] = { 3 };
    int rc;

    rc = copy_uniq_elems(arr, 1, arr_dst, &dst_len);
    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(dst_len, 1);
    ck_assert_mem_eq(arr_dst, arr_res, sizeof(int) * 1);
}
END_TEST

// Пустой массив
START_TEST(copy_uniq_elems_empty)
{
    int arr[] = { 3 };
    int arr_dst[1];
    size_t dst_len;
    int rc;

    rc = copy_uniq_elems(arr, 0, arr_dst, &dst_len);
    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(dst_len, 0);
}
END_TEST

// Выходной массив NULL
START_TEST(copy_uniq_elems_null_out)
{
    int arr[] = { -2, 2, -2 };
    size_t dst_len;
    int rc;

    rc = copy_uniq_elems(arr, 3, NULL, &dst_len);
    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(dst_len, 2);
}
END_TEST


// Функция объединения тестов копирования уникальных элементов в набор
Suite *copy_uniq_elems_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("copy_uniq_elems");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, copy_uniq_elems_nullptr_arr);
    tcase_add_test(tc_neg, copy_uniq_elems_nullptr_dst_len);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, copy_uniq_elems_all_uniq);
    tcase_add_test(tc_pos, copy_uniq_elems_all_same);
    tcase_add_test(tc_pos, copy_uniq_elems_one_elem);
    tcase_add_test(tc_pos, copy_uniq_elems_mixed);
    tcase_add_test(tc_pos, copy_uniq_elems_empty);
    tcase_add_test(tc_pos, copy_uniq_elems_null_out);
    suite_add_tcase(s, tc_pos);

    return s;
}
