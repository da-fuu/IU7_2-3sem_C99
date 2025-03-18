#include "operations.h"
#include "matrix.h"
#include "errors.h"
#include "check_operations.h"


// Функция создания матрицы с заданными измерениями
matrix_t create_matrix(size_t n, size_t m)
{
    matrix_t matrix;
    matrix.rows = n;
    matrix.cols = m;
    matrix.elements = allocate_matrix(n, m);
    return matrix;
}

// Функция проверки равенства матриц
void assert_matrix_eq(matrix_t in1, matrix_t in2)
{
    ck_assert(in1.rows == in2.rows && in1.cols == in2.cols);
    for (size_t i = 0; i < in1.rows; i++)
        for (size_t j = 0; j < in1.cols; j++)
            ck_assert_double_eq_tol(in1.elements[i][j], in2.elements[i][j], EPS);
}

// Функция освобождения нескольких матриц
void free_all(double **m1, double **m2, double **m3, double **m4)
{
    if (m1)
        free_matrix(m1);
    if (m2)
        free_matrix(m2);
    if (m3)
        free_matrix(m3);
    if (m4)
        free_matrix(m4);
}


// Разное кол-во столбцов при сложении
START_TEST(addition_diff_cols)
{
    int rc;
    matrix_t in1 = create_matrix(2, 1);
    matrix_t in2 = create_matrix(2, 2);
    matrix_t out;
    in1.elements[0][0] = 1.0;
    in1.elements[1][0] = 1.0;
    in2.elements[0][0] = 1.0;
    in2.elements[0][1] = 1.0;
    in2.elements[1][0] = 1.0;
    in2.elements[1][1] = 1.0;

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, ERR_DIMENSIONS_ADD);
    free_all(in1.elements, in2.elements, NULL, NULL);
}
END_TEST

// Разное кол-во строк при сложении
START_TEST(addition_diff_rows)
{
    int rc;
    matrix_t in1 = create_matrix(2, 1);
    matrix_t in2 = create_matrix(1, 1);
    matrix_t out;
    in1.elements[0][0] = 1.0;
    in1.elements[1][0] = 1.0;
    in2.elements[0][0] = 1.0;

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, ERR_DIMENSIONS_ADD);
    free_all(in1.elements, in2.elements, NULL, NULL);
}
END_TEST

// Разные измерения при сложении
START_TEST(addition_diff_dims)
{
    int rc;
    matrix_t in1 = create_matrix(2, 1);
    matrix_t in2 = create_matrix(1, 2);
    matrix_t out;
    in1.elements[0][0] = 1.0;
    in1.elements[1][0] = 1.0;
    in2.elements[0][0] = 1.0;
    in2.elements[0][1] = 1.0;

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, ERR_DIMENSIONS_ADD);
    free_all(in1.elements, in2.elements, NULL, NULL);
}
END_TEST


// Сложение нулевых матриц
START_TEST(addition_zero)
{
    int rc;
    matrix_t in1 = create_matrix(2, 2);
    matrix_t in2 = create_matrix(2, 2);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 2);
    for (size_t i = 0; i < in1.rows; i++)
        for (size_t j = 0; j < in1.cols; j++)
        {
            in1.elements[i][j] = 0.0;
            in2.elements[i][j] = 0.0;
            out_res.elements[i][j] = 0.0;
        }

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Сложение матриц из положительных элементов
START_TEST(addition_positives)
{
    int rc;
    matrix_t in1 = create_matrix(2, 2);
    matrix_t in2 = create_matrix(2, 2);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 2);
    for (size_t i = 0; i < in1.rows; i++)
        for (size_t j = 0; j < in1.cols; j++)
        {
            in1.elements[i][j] = (double)i + 0.5;
            in2.elements[i][j] = (double)j + 0.5;
            out_res.elements[i][j] = 1.0 + (double)i + (double)j;
        }

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Сложение матриц из отрицательных элементов
START_TEST(addition_negatives)
{
    int rc;
    matrix_t in1 = create_matrix(2, 2);
    matrix_t in2 = create_matrix(2, 2);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 2);
    for (size_t i = 0; i < in1.rows; i++)
        for (size_t j = 0; j < in1.cols; j++)
        {
            in1.elements[i][j] = -0.5 - (double)i;
            in2.elements[i][j] = -0.5 - (double)j;
            out_res.elements[i][j] = -1.0 - (double)i - (double)j;
        }

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Сложение матриц из одного элемента
START_TEST(addition_one_elem)
{
    int rc;
    matrix_t in1 = create_matrix(1, 1);
    matrix_t in2 = create_matrix(1, 1);
    matrix_t out;
    matrix_t out_res = create_matrix(1, 1);
    in1.elements[0][0] = 1.5;
    in2.elements[0][0] = -0.5;
    out_res.elements[0][0] = 1.0;

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Сложение матриц из одной строки
START_TEST(addition_one_row)
{
    int rc;
    matrix_t in1 = create_matrix(1, 3);
    matrix_t in2 = create_matrix(1, 3);
    matrix_t out;
    matrix_t out_res = create_matrix(1, 3);
    for (size_t j = 0; j < in1.cols; j++)
    {
        in1.elements[0][j] = -0.5 + (double)j;
        in2.elements[0][j] = -0.5 - (double)j;
        out_res.elements[0][j] = -1.0;
    }

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Сложение матриц из одного столбца
START_TEST(addition_one_col)
{
    int rc;
    matrix_t in1 = create_matrix(3, 1);
    matrix_t in2 = create_matrix(3, 1);
    matrix_t out;
    matrix_t out_res = create_matrix(3, 1);
    for (size_t i = 0; i < in1.rows; i++)
    {
        in1.elements[i][0] = 0.5 + (double)i;
        in2.elements[i][0] = 0.5 - (double)i;
        out_res.elements[i][0] = 1.0;
    }

    rc = add_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Функция объединения тестов сложения матриц в набор
Suite *addition_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("addition");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, addition_diff_rows);
    tcase_add_test(tc_neg, addition_diff_cols);
    tcase_add_test(tc_neg, addition_diff_dims);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, addition_zero);
    tcase_add_test(tc_pos, addition_positives);
    tcase_add_test(tc_pos, addition_negatives);
    tcase_add_test(tc_pos, addition_one_elem);
    tcase_add_test(tc_pos, addition_one_row);
    tcase_add_test(tc_pos, addition_one_col);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Умножение матриц с неправильными размерностями
START_TEST(multiplication_diff_dims)
{
    int rc;
    matrix_t in1 = create_matrix(2, 2);
    matrix_t in2 = create_matrix(1, 2);
    matrix_t out;
    in1.elements[0][0] = 1.0;
    in1.elements[1][0] = 1.0;
    in1.elements[1][1] = 1.0;
    in1.elements[0][1] = 1.0;
    in2.elements[0][0] = 1.0;
    in2.elements[0][1] = 1.0;

    rc = multiply_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, ERR_DIMENSIONS_MULTIPLY);
    free_all(in1.elements, in2.elements, NULL, NULL);
}
END_TEST

// Умножение матриц с неправильными, но равными размерностями
START_TEST(multiplication_same_row_col)
{
    int rc;
    matrix_t in1 = create_matrix(1, 2);
    matrix_t in2 = create_matrix(1, 2);
    matrix_t out;
    in1.elements[0][0] = 1.0;
    in1.elements[0][1] = 1.0;
    in2.elements[0][0] = 1.0;
    in2.elements[0][1] = 1.0;

    rc = multiply_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, ERR_DIMENSIONS_MULTIPLY);
    free_all(in1.elements, in2.elements, NULL, NULL);
}
END_TEST

// Умножение нулевых матриц
START_TEST(multiplication_all_zero)
{
    int rc;
    matrix_t in1 = create_matrix(2, 3);
    matrix_t in2 = create_matrix(3, 2);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 2);
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
        {
            in1.elements[i][j] = 0.0;
            in2.elements[i][j] = 0.0;
            out_res.elements[i][j] = 0.0;
        }
    in2.elements[2][0] = 0.0;
    in2.elements[2][1] = 0.0;
    in1.elements[0][2] = 0.0;
    in1.elements[1][2] = 0.0;

    rc = multiply_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Умножение единичных матриц
START_TEST(multiplication_unit)
{
    int rc;
    matrix_t in1 = create_matrix(2, 2);
    matrix_t in2 = create_matrix(2, 2);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 2);
    for (size_t i = 0; i < in1.rows; i++)
        for (size_t j = 0; j < in1.cols; j++)
        {
            in1.elements[i][j] = (double)((i + j + 1) % 2);
            in2.elements[i][j] = (double)((i + j + 1) % 2);
            out_res.elements[i][j] = (double)((i + j + 1) % 2);
        }

    rc = multiply_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Умножение столбца на строку
START_TEST(multiplication_col_by_row)
{
    int rc;
    matrix_t in1 = create_matrix(3, 1);
    matrix_t in2 = create_matrix(1, 3);
    matrix_t out;
    matrix_t out_res = create_matrix(3, 3);
    for (size_t i = 0; i < 3; i++)
    {
        in1.elements[i][0] = (double)i;
        in2.elements[0][i] = (double)i;
    }
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            out_res.elements[i][j] = (double)i * (double)j;

    rc = multiply_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Умножение строки на столбец
START_TEST(multiplication_row_by_col)
{
    int rc;
    matrix_t in1 = create_matrix(1, 3);
    matrix_t in2 = create_matrix(3, 1);
    matrix_t out;
    matrix_t out_res = create_matrix(1, 1);
    for (size_t i = 0; i < 3; i++)
    {
        in2.elements[i][0] = (double)i;
        in1.elements[0][i] = (double)i;
    }
    out_res.elements[0][0] = 5.0;

    rc = multiply_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST

// Умножение матриц из одного элемента
START_TEST(multiplication_one_elem)
{
    int rc;
    matrix_t in1 = create_matrix(1, 1);
    matrix_t in2 = create_matrix(1, 1);
    matrix_t out;
    matrix_t out_res = create_matrix(1, 1);
    in2.elements[0][0] = -100.0;
    in1.elements[0][0] = 0.05;
    out_res.elements[0][0] = -5.0;

    rc = multiply_matrices(in1, in2, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out_res, out);
    free_all(in1.elements, in2.elements, out.elements, out_res.elements);
}
END_TEST


// Функция объединения тестов умножения матриц в набор
Suite *multiplication_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("multiplication");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, multiplication_diff_dims);
    tcase_add_test(tc_neg, multiplication_same_row_col);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, multiplication_all_zero);
    tcase_add_test(tc_pos, multiplication_unit);
    tcase_add_test(tc_pos, multiplication_col_by_row);
    tcase_add_test(tc_pos, multiplication_row_by_col);
    tcase_add_test(tc_pos, multiplication_one_elem);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Неправильные размерности матрицы
START_TEST(solve_diff_dims)
{
    int rc;
    matrix_t in = create_matrix(2, 2);
    matrix_t out;
    in.elements[0][0] = 2.0;
    in.elements[1][0] = 1.0;
    in.elements[1][1] = 2.0;
    in.elements[0][1] = 1.0;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, ERR_DIMENSIONS_SOLVE);
    free_all(in.elements, NULL, NULL, NULL);
}
END_TEST

// Несовместная СЛАУ
START_TEST(solve_no_roots)
{
    int rc;
    matrix_t in = create_matrix(2, 3);
    matrix_t out;
    in.elements[0][0] = 1.0;
    in.elements[0][1] = 1.0;
    in.elements[0][2] = 2.0;
    in.elements[1][0] = 1.0;
    in.elements[1][1] = 1.0;
    in.elements[1][2] = 1.0;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, ERR_SOLVE);
    free_all(in.elements, NULL, NULL, NULL);
}
END_TEST

// Бесконечное количество решений СЛАУ (ранг меньше на 1)
START_TEST(solve_inf_roots)
{
    int rc;
    matrix_t in = create_matrix(2, 3);
    matrix_t out;
    in.elements[0][0] = 1.0;
    in.elements[0][1] = 1.0;
    in.elements[0][2] = 2.0;
    in.elements[1][0] = 1.0;
    in.elements[1][1] = 1.0;
    in.elements[1][2] = 2.0;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, ERR_SOLVE);
    free_all(in.elements, NULL, NULL, NULL);
}
END_TEST

// СЛАУ из одинаковых уравнений (ранг 1)
START_TEST(solve_many_same_eq)
{
    int rc;
    matrix_t in = create_matrix(3, 4);
    matrix_t out;
    for (size_t i = 0; i < 3; i++)
    {
        in.elements[i][0] = 1.0;
        in.elements[i][1] = 1.5;
        in.elements[i][2] = -1.3;
        in.elements[i][3] = 155.5;
    }

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, ERR_SOLVE);
    free_all(in.elements, NULL, NULL, NULL);
}
END_TEST


// Все неизвестные равны 0 в решении
START_TEST(solve_all_zero)
{
    int rc;
    matrix_t in = create_matrix(2, 3);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 1);
    in.elements[0][0] = 1.0;
    in.elements[0][1] = 1.0;
    in.elements[0][2] = 0.0;
    in.elements[1][0] = 1.0;
    in.elements[1][1] = 2.0;
    in.elements[1][2] = 0.0;
    out_res.elements[0][0] = 0.0;
    out_res.elements[0][1] = 0.0;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out, out_res);
    free_all(in.elements, out.elements, out_res.elements, NULL);
}
END_TEST

// Входная матрица коэффициентов - единичная
START_TEST(solve_alredy_solved)
{
    int rc;
    matrix_t in = create_matrix(2, 3);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 1);
    in.elements[0][0] = 1.0;
    in.elements[0][1] = 0.0;
    in.elements[0][2] = 3.0;
    in.elements[1][0] = 0.0;
    in.elements[1][1] = 1.0;
    in.elements[1][2] = -1.5;
    out_res.elements[0][0] = 3.0;
    out_res.elements[0][1] = -1.5;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out, out_res);
    free_all(in.elements, out.elements, out_res.elements, NULL);
}
END_TEST

// Только одна из переменных в решении ненулевая
START_TEST(solve_one_var_nonzero)
{
    int rc;
    matrix_t in = create_matrix(2, 3);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 1);
    in.elements[0][0] = 1.0;
    in.elements[0][1] = 1.0;
    in.elements[0][2] = 3.0;
    in.elements[1][0] = -0.5;
    in.elements[1][1] = 1.0;
    in.elements[1][2] = -1.5;
    out_res.elements[0][0] = 3.0;
    out_res.elements[0][1] = 0.0;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out, out_res);
    free_all(in.elements, out.elements, out_res.elements, NULL);
}
END_TEST

// СЛАУ из одного уравнения
START_TEST(solve_one_row)
{
    int rc;
    matrix_t in = create_matrix(1, 2);
    matrix_t out;
    matrix_t out_res = create_matrix(1, 1);
    in.elements[0][0] = -1.0;
    in.elements[0][1] = 2.0;
    out_res.elements[0][0] = -2.0;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out, out_res);
    free_all(in.elements, out.elements, out_res.elements, NULL);
}
END_TEST

// СЛАУ, при решении которой методом Гаусса с выбором главного элемента по активной подматрице,
// всегда придется менять местами строки или столбцы
START_TEST(solve_main_reversed)
{
    int rc;
    matrix_t in = create_matrix(2, 3);
    matrix_t out;
    matrix_t out_res = create_matrix(2, 1);
    in.elements[0][0] = 1.0;
    in.elements[0][1] = 1.0;
    in.elements[0][2] = 3.0;
    in.elements[1][0] = 1.0;
    in.elements[1][1] = 5.0;
    in.elements[1][2] = 7.0;
    out_res.elements[0][0] = 2.0;
    out_res.elements[0][1] = 1.0;

    rc = solve_sle(in, &out);
    ck_assert_int_eq(rc, OK);
    assert_matrix_eq(out, out_res);
    free_all(in.elements, out.elements, out_res.elements, NULL);
}
END_TEST


// Функция объединения тестов на решение СЛАУ в набор
Suite *solve_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("solve");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, solve_diff_dims);
    tcase_add_test(tc_neg, solve_no_roots);
    tcase_add_test(tc_neg, solve_inf_roots);
    tcase_add_test(tc_neg, solve_many_same_eq);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, solve_all_zero);
    tcase_add_test(tc_pos, solve_alredy_solved);
    tcase_add_test(tc_pos, solve_one_var_nonzero);
    tcase_add_test(tc_pos, solve_one_row);
    tcase_add_test(tc_pos, solve_main_reversed);
    suite_add_tcase(s, tc_pos);

    return s;
}
