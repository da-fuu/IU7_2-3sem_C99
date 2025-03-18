#include "matrix.h"
#include "list.h"
#include "errors.h"
#include "check_matrix.h"

#define ARR_LEN(a) (sizeof(a) / sizeof((a)[0]))


// Функция создания списка с заданным содержимым
node_t *create_matrix(data_t arr[], int len)
{
    node_t *head = NULL;
    node_t *end = NULL;
    for (int i = 0; i < len; i++)
    {
        push_end(&head, &end, &arr[i]);
    }
    return head;
}

// Функция проверки равенства списков
void assert_list_eq(node_t *in1, node_t *in2)
{
    while (in1 != NULL && in2 != NULL)
    {
        ck_assert_int_eq(in1->data.row, in2->data.row);
        ck_assert_int_eq(in1->data.col, in2->data.col);
        ck_assert_int_eq(in1->data.val, in2->data.val);
        in1 = in1->next;
        in2 = in2->next;
    }
    ck_assert_ptr_null(in1);
    ck_assert_ptr_null(in2);
}


// Указатель на NULL вместо первого списка
START_TEST(add_matrices_nullptr_a)
{
    data_t arr[] = { { 0, 0, 4 }, { 2, 4, 2 } };
    node_t *in_2 = create_matrix(arr, ARR_LEN(arr));
    node_t *initial = create_matrix(arr, ARR_LEN(arr));
    node_t *out;

    out = add_matrices(NULL, &in_2);
    ck_assert_ptr_null(out);
    assert_list_eq(in_2, initial);

    free_list(in_2);
    free_list(initial);
}
END_TEST

// Указатель на NULL вместо второго списка
START_TEST(add_matrices_nullptr_b)
{
    data_t arr[] = { { 0, 0, 4 }, { 2, 4, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    node_t *initial = create_matrix(arr, ARR_LEN(arr));
    node_t *out;

    out = add_matrices(&in_1, NULL);
    ck_assert_ptr_null(out);
    assert_list_eq(in_1, initial);

    free_list(in_1);
    free_list(initial);
}
END_TEST

// Оба списка пустые
START_TEST(add_matrices_both_empty)
{
    node_t *in_1 = NULL;
    node_t *in_2 = NULL;
    node_t *out;

    out = add_matrices(&in_1, &in_2);
    ck_assert_ptr_null(out);
    ck_assert_ptr_null(in_1);
    ck_assert_ptr_null(in_2);
}
END_TEST

// Пустая выходная матрица
START_TEST(add_matrices_result_zero)
{
    data_t arr[] = { { 0, 0, 4 }, { 2, 4, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 0, 0, -4 }, { 2, 4, -2 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    node_t *out;

    out = add_matrices(&in_1, &in_2);
    ck_assert_ptr_null(out);
    ck_assert_ptr_null(in_1);
    ck_assert_ptr_null(in_2);
}
END_TEST


// Все элементы присутствуют в обеих матрицах
START_TEST(add_matrices_same_elems)
{
    data_t arr[] = { { 0, 0, 4 }, { 2, 4, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 0, 0, 6 }, { 2, 4, -5 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 0, 0, 10 }, { 2, 4, -3 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    out = add_matrices(&in_1, &in_2);
    ck_assert_ptr_null(in_1);
    ck_assert_ptr_null(in_2);
    assert_list_eq(res, out);

    free_list(out);
    free_list(res);
}
END_TEST

// Все элементы уникальны
START_TEST(add_matrices_diff_elems)
{
    data_t arr[] = { { 0, 0, 4 }, { 2, 4, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 1, 1, 6 }, { 2, 3, -5 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 0, 0, 4 }, { 1, 1, 6 }, { 2, 3, -5 }, { 2, 4, 2 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    out = add_matrices(&in_1, &in_2);
    ck_assert_ptr_null(in_1);
    ck_assert_ptr_null(in_2);
    assert_list_eq(res, out);

    free_list(out);
    free_list(res);
}
END_TEST

// Матрицы из одного элемента
START_TEST(add_matrices_one_elem)
{
    data_t arr[] = { { 1, 2, 4 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 1, 2, 6 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 1, 2, 10 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    out = add_matrices(&in_1, &in_2);
    ck_assert_ptr_null(in_1);
    ck_assert_ptr_null(in_2);
    assert_list_eq(res, out);

    free_list(out);
    free_list(res);
}
END_TEST

// Матрицы-строки
START_TEST(add_matrices_one_row)
{
    data_t arr[] = { { 2, 0, 4 }, { 2, 4, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 2, 4, 6 }, { 2, 5, -5 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 2, 0, 4 }, { 2, 4, 8 }, { 2, 5, -5 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    out = add_matrices(&in_1, &in_2);
    ck_assert_ptr_null(in_1);
    ck_assert_ptr_null(in_2);
    assert_list_eq(res, out);

    free_list(out);
    free_list(res);
}
END_TEST

// Матрицы-столбцы
START_TEST(add_matrices_one_col)
{
    data_t arr[] = { { 1, 3, 4 }, { 2, 3, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 2, 3, 6 }, { 5, 3, -5 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 1, 3, 4 }, { 2, 3, 8 }, { 5, 3, -5 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    out = add_matrices(&in_1, &in_2);
    ck_assert_ptr_null(in_1);
    ck_assert_ptr_null(in_2);
    assert_list_eq(res, out);

    free_list(out);
    free_list(res);
}
END_TEST

// Функция объединения тестов сложения матриц в набор
Suite *add_matrices_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("add_matrices");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо первого списка
    tcase_add_test(tc_neg, add_matrices_nullptr_a);
    // Указатель на NULL вместо второго списка
    tcase_add_test(tc_neg, add_matrices_nullptr_b);
    // Оба списка пустые
    tcase_add_test(tc_neg, add_matrices_both_empty);
    // Пустая выходная матрица
    tcase_add_test(tc_neg, add_matrices_result_zero);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Все элементы присутствуют в обеих матрицах
    tcase_add_test(tc_pos, add_matrices_same_elems);
    // Все элементы уникальны
    tcase_add_test(tc_pos, add_matrices_diff_elems);
    // Матрицы из одного элемента
    tcase_add_test(tc_pos, add_matrices_one_elem);
    // Матрицы-строки
    tcase_add_test(tc_pos, add_matrices_one_row);
    // Матрицы-столбцы
    tcase_add_test(tc_pos, add_matrices_one_col);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Пустая первая матрица
START_TEST(mul_matrices_empty_a)
{
    int rc;
    node_t *in_1 = NULL;
    data_t arr[] = { { 0, 0, 4 }, { 2, 4, 2 } };
    node_t *in_2 = create_matrix(arr, ARR_LEN(arr));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_null(out);

    free_list(in_2);
}
END_TEST

// Пустая вторая матрица
START_TEST(mul_matrices_empty_b)
{
    int rc;
    node_t *in_2 = NULL;
    data_t arr[] = { { 0, 0, 4 }, { 2, 4, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_null(out);

    free_list(in_1);
}
END_TEST

// Указатель на NULL вместо выходного списка
START_TEST(mul_matrices_nullptr_out)
{
    int rc;
    data_t arr[] = { { 0, 0, 4 }, { 2, 2, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    node_t *in_2 = create_matrix(arr, ARR_LEN(arr));

    rc = mul_matrices(in_1, in_2, NULL);
    ck_assert_int_eq(rc, ERR_UNIT_FAIL);

    free_list(in_1);
    free_list(in_2);
}
END_TEST

// Пустая выходная матрица
START_TEST(mul_matrices_result_zero)
{
    int rc;
    data_t arr[] = { { 0, 0, 4 }, { 2, 0, 2 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 2, 0, 4 }, { 2, 2, 2 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_null(out);

    free_list(in_1);
    free_list(in_2);
}
END_TEST


// Умножение единичных матриц
START_TEST(mul_matrices_unit)
{
    int rc;
    data_t arr[] = { { 0, 0, 1 }, { 1, 1, 1 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 0, 0, 1 }, { 1, 1, 1 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 0, 0, 1 }, { 1, 1, 1 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(res, out);

    free_list(in_1);
    free_list(in_2);
    free_list(res);
    free_list(out);
}
END_TEST

// Умножение столбца на строку
START_TEST(mul_matrices_col_by_row)
{
    int rc;
    data_t arr[] = { { 0, 0, 1 }, { 2, 0, 4 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 0, 0, 5 }, { 0, 2, 5 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 0, 0, 5 }, { 0, 2, 5 }, { 2, 0, 20 }, { 2, 2, 20 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(res, out);

    free_list(in_1);
    free_list(in_2);
    free_list(res);
    free_list(out);
}
END_TEST

// Умножение строки на столбец
START_TEST(mul_matrices_row_by_col)
{
    int rc;
    data_t arr[] = { { 0, 0, 5 }, { 0, 2, 5 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 0, 0, 1 }, { 2, 0, 4 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 0, 0, 25 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(res, out);

    free_list(in_1);
    free_list(in_2);
    free_list(res);
    free_list(out);
}
END_TEST

// Умножение матриц из одного элемента
START_TEST(mul_matrices_one_elem)
{
    int rc;
    data_t arr[] = { { 0, 0, 5 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 0, 0, 1 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 0, 0, 5 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(res, out);

    free_list(in_1);
    free_list(in_2);
    free_list(res);
    free_list(out);
}
END_TEST

// Умножение квадратных матриц
START_TEST(mul_matrices_square)
{
    int rc;
    data_t arr[] = { { 0, 0, 1 }, { 0, 1, -3 }, { 1, 0, 4 }, { 1, 1, 9 } };
    node_t *in_1 = create_matrix(arr, ARR_LEN(arr));
    data_t arr_2[] = { { 0, 0, 8 }, { 0, 1, 5 }, { 1, 0, 11 }, { 1, 1, -5 } };
    node_t *in_2 = create_matrix(arr_2, ARR_LEN(arr_2));
    data_t arr_res[] = { { 0, 0, -25 }, { 0, 1, 20 }, { 1, 0, 131 }, { 1, 1, -25 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));
    node_t *out;

    rc = mul_matrices(in_1, in_2, &out);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(res, out);

    free_list(in_1);
    free_list(in_2);
    free_list(res);
    free_list(out);
}
END_TEST

// Функция объединения тестов умножения матриц в набор
Suite *mul_matrices_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("mul_matrices");

    tc_neg = tcase_create("negatives");
    // Пустая первая матрица
    tcase_add_test(tc_neg, mul_matrices_empty_a);
    // Пустая вторая матрица
    tcase_add_test(tc_neg, mul_matrices_empty_b);
    // Указатель на NULL вместо выходного списка
    tcase_add_test(tc_neg, mul_matrices_nullptr_out);
    // Пустая выходная матрица
    tcase_add_test(tc_neg, mul_matrices_result_zero);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Умножение единичных матриц
    tcase_add_test(tc_pos, mul_matrices_unit);
    // Умножение столбца на строку
    tcase_add_test(tc_pos, mul_matrices_col_by_row);
    // Умножение строки на столбец
    tcase_add_test(tc_pos, mul_matrices_row_by_col);
    // Умножение матриц из одного элемента
    tcase_add_test(tc_pos, mul_matrices_one_elem);
    // Умножение квадратных матриц
    tcase_add_test(tc_pos, mul_matrices_square);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Пустой список
START_TEST(remove_row_with_max_empty)
{
    int rc;
    node_t *in = NULL;

    rc = remove_row_with_max(&in);
    ck_assert_int_eq(rc, ERR_UNIT_FAIL);
    ck_assert_ptr_null(in);
}
END_TEST

// Указатель на NULL
START_TEST(remove_row_with_max_nullptr)
{
    int rc;

    rc = remove_row_with_max(NULL);
    ck_assert_int_eq(rc, ERR_UNIT_FAIL);
}
END_TEST

// Пустой список после удаления строки
START_TEST(remove_row_with_max_res_empty)
{
    int rc;
    data_t arr[] = { { 0, 0, 4 }, { 0, 4, 2 } };
    node_t *in = create_matrix(arr, ARR_LEN(arr));

    rc = remove_row_with_max(&in);
    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_null(in);
}
END_TEST

// Несколько максимальных элементов
START_TEST(remove_row_with_max_many_max)
{
    int rc;
    data_t arr[] = { { 0, 0, 4 }, { 0, 4, 2 }, {1, 2, 4} };
    node_t *in = create_matrix(arr, ARR_LEN(arr));
    node_t *initial = create_matrix(arr, ARR_LEN(arr));

    rc = remove_row_with_max(&in);
    ck_assert_int_eq(rc, ERR_MANY_MAX);
    assert_list_eq(in, initial);

    free_list(in);
    free_list(initial);
}
END_TEST


// Длинная удаляемая строка
START_TEST(remove_row_with_max_big_row)
{
    int rc;
    data_t arr[] = { { 0, 0, 4 }, { 1, 1, 2 }, {1, 2, 5}, {1, 5, 0}, {2, 5, 4} };
    node_t *in = create_matrix(arr, ARR_LEN(arr));
    data_t arr_res[] = { { 0, 0, 4 }, {2, 5, 4} };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));

    rc = remove_row_with_max(&in);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(in, res);

    free_list(in);
    free_list(res);
}
END_TEST

// Матрица с одним элементом в каждой строчке
START_TEST(remove_row_with_max_one_col)
{
    int rc;
    data_t arr[] = { { 0, 0, 4 }, { 1, 1, 2 }, {2, 2, 5}, {4, 5, 0}, {5, 5, 4} };
    node_t *in = create_matrix(arr, ARR_LEN(arr));
    data_t arr_res[] = { { 0, 0, 4 }, { 1, 1, 2 }, {4, 5, 0}, {5, 5, 4} };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));

    rc = remove_row_with_max(&in);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(in, res);

    free_list(in);
    free_list(res);
}
END_TEST

// После удаления в списке только один элемент
START_TEST(remove_row_with_max_one_elem_out)
{
    int rc;
    data_t arr[] = { { 0, 0, 4 }, { 1, 1, 2 } };
    node_t *in = create_matrix(arr, ARR_LEN(arr));
    data_t arr_res[] = { { 1, 1, 2 } };
    node_t *res = create_matrix(arr_res, ARR_LEN(arr_res));

    rc = remove_row_with_max(&in);
    ck_assert_int_eq(rc, OK);
    assert_list_eq(in, res);

    free_list(in);
    free_list(res);
}
END_TEST

// Функция объединения тестов на удаление строки с максимальным элементом в набор
Suite *remove_row_with_max_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("remove_row_with_max");

    tc_neg = tcase_create("negatives");
    // Пустой список
    tcase_add_test(tc_neg, remove_row_with_max_empty);
    // Указатель на NULL
    tcase_add_test(tc_neg, remove_row_with_max_nullptr);
    // Пустой список после удаления строки
    tcase_add_test(tc_neg, remove_row_with_max_res_empty);
    // Несколько максимальных элементов
    tcase_add_test(tc_neg, remove_row_with_max_many_max);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Длинная удаляемая строка
    tcase_add_test(tc_pos, remove_row_with_max_big_row);
    // Матрица с одним элементом в каждой строчке
    tcase_add_test(tc_pos, remove_row_with_max_one_col);
    // После удаления в списке только один элемент
    tcase_add_test(tc_pos, remove_row_with_max_one_elem_out);
    suite_add_tcase(s, tc_pos);

    return s;
}
