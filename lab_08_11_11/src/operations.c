#include <malloc.h>
#include <math.h>

#include "errors.h"
#include "operations.h"


// Функция сложения двух матриц. Принимает 2 входные матрицы, изменяет по указателю выходную матрицу
// Возвращает код ошибки
int add_matrices(matrix_t matrix_in_1, matrix_t matrix_in_2, matrix_t *matrix_out)
{
    if (matrix_in_1.rows != matrix_in_2.rows || matrix_in_1.cols != matrix_in_2.cols)
        return ERR_DIMENSIONS_ADD;

    matrix_out->rows = matrix_in_1.rows;
    matrix_out->cols = matrix_in_1.cols;
    matrix_out->elements = allocate_matrix(matrix_out->rows, matrix_out->cols);
    if (!matrix_out->elements)
        return ERR_NO_MEMORY;

    for (size_t i = 0; i < matrix_out->rows; i++)
        for (size_t j = 0; j < matrix_out->cols; j++)
            matrix_out->elements[i][j] = matrix_in_1.elements[i][j] + matrix_in_2.elements[i][j];
    return OK;
}

// Функция умножения двух матриц. Принимает 2 входные матрицы, изменяет по указателю выходную матрицу
// Возвращает код ошибки
int multiply_matrices(matrix_t matrix_in_1, matrix_t matrix_in_2, matrix_t *matrix_out)
{
    if (matrix_in_1.cols != matrix_in_2.rows)
        return ERR_DIMENSIONS_MULTIPLY;

    matrix_out->rows = matrix_in_1.rows;
    matrix_out->cols = matrix_in_2.cols;
    matrix_out->elements = allocate_matrix(matrix_out->rows, matrix_out->cols);
    if (!matrix_out->elements)
        return ERR_NO_MEMORY;

    for (size_t i = 0; i < matrix_out->rows; i++)
        for (size_t j = 0; j < matrix_out->cols; j++)
        {
            matrix_out->elements[i][j] = 0;
            for (size_t k = 0; k < matrix_in_1.cols; k++)
                matrix_out->elements[i][j] += matrix_in_1.elements[i][k] * matrix_in_2.elements[k][j];
        }
    return OK;
}

// Функция поиска и перемещения главного элемента в активной подматрице
// Принимает матрицу, индекс, с которого начинать поиск, изменяет массив индексов переменных
// Возвращает код ошибки
int move_max_abs_in_submatrix(matrix_t matrix, size_t k, size_t x_indexes[])
{
    double max_el = 0.0;
    size_t i_max = k, j_max = k;
    size_t tmp_x;
    double *tmp_row;
    double tmp_el;

    for (size_t i = k; i < matrix.rows; i++)
        for (size_t j = k; j < matrix.rows; j++)
            if (fabs(matrix.elements[i][j]) > max_el)
            {
                max_el = fabs(matrix.elements[i][j]);
                i_max = i;
                j_max = j;
            }
    if (max_el < EPS)
        return ERR_SOLVE;

    tmp_x = x_indexes[j_max];
    x_indexes[j_max] = x_indexes[k];
    x_indexes[k] = tmp_x;

    tmp_row = matrix.elements[i_max];
    matrix.elements[i_max] = matrix.elements[k];
    matrix.elements[k] = tmp_row;

    for (size_t i = 0; i < matrix.rows; i++)
    {
        tmp_el = matrix.elements[i][j_max];
        matrix.elements[i][j_max] = matrix.elements[i][k];
        matrix.elements[i][k] = tmp_el;
    }
    return OK;
}

// Функция прямого хода метода Гаусса
// Принимает и изменяет матрицу и массив индексов переменных
// Возвращает код ошибки
int forward(matrix_t matrix, size_t x_indexes[])
{
    double m;
    int ret_code;

    for (size_t k = 0; k < matrix.rows - 1; k++)
    {
        ret_code = move_max_abs_in_submatrix(matrix, k, x_indexes);
        if (ret_code != OK)
            return ret_code;

        for (size_t j = k + 1; j < matrix.rows; j++)
        {
            m = matrix.elements[j][k] / matrix.elements[k][k];
            for (size_t i = k; i < matrix.cols; i++)
                matrix.elements[j][i] = matrix.elements[j][i] - m * matrix.elements[k][i];
        }
    }
    if (fabs(matrix.elements[matrix.rows - 1][matrix.rows - 1]) < EPS)
        return ERR_SOLVE;

    return OK;
}

// Функция прямого хода метода Гаусса
// Принимает матрицу и массив индексов переменных, изменяет матрицу значений переменных
void backward(matrix_t in_matrix, const size_t x_indexes[], matrix_t out_matrix)
{
    size_t index;
    for (size_t i = in_matrix.cols - 1; i > 0; i--)
    {
        index = x_indexes[i - 1];
        out_matrix.elements[index][0] = in_matrix.elements[i - 1][in_matrix.cols - 1] / in_matrix.elements[i - 1][i - 1];
        for (size_t c = in_matrix.rows - 1; c > i - 1; c--)
            out_matrix.elements[index][0] -= in_matrix.elements[i - 1][c] * out_matrix.elements[x_indexes[c]][0] / in_matrix.elements[i - 1][i - 1];
    }
}

// Функция решения СЛАУ
// Принимает матрицу коэффициентов и свободных членов и изменяет выходную матрицу по указателю
// Возвращает код ошибки
int solve_sle(matrix_t matrix_in, matrix_t *matrix_out)
{
    int ret_code;
    size_t *x_indexes;

    if (matrix_in.rows + 1 != matrix_in.cols)
        return ERR_DIMENSIONS_SOLVE;

    matrix_out->rows = matrix_in.cols - 1;
    matrix_out->cols = 1;
    matrix_out->elements = allocate_matrix(matrix_out->rows, matrix_out->cols);
    if (!matrix_out->elements)
        return ERR_NO_MEMORY;

    x_indexes = malloc(sizeof(size_t) * matrix_out->rows);
    if (!x_indexes)
    {
        free_matrix(matrix_out->elements);
        return ERR_NO_MEMORY;
    }
    for (size_t i = 0; i < matrix_out->rows; i++)
        x_indexes[i] = i;

    ret_code = forward(matrix_in, x_indexes);
    if (ret_code != OK)
    {
        free(x_indexes);
        free_matrix(matrix_out->elements);
        return ret_code;
    }

    backward(matrix_in, x_indexes, *matrix_out);

    free(x_indexes);
    return OK;
}
