#include <stdio.h>

#include "errors.h"
#include "file.h"


// Функция чтения данных из текстового файла в матрицу
// Принимает имя текстового файла, изменяет матрицу по указателю
// Возвращает код ошибки
int read_matrix(const char *filename, matrix_t *matrix)
{
    FILE *in_file;
    int rows, cols;
    double tmp;

    in_file = fopen(filename, "r");
    if (in_file == NULL)
        return ERR_FILE_IN_ACCESS;

    if (fscanf(in_file, "%d%d", &rows, &cols) != 2)
    {
        fclose(in_file);
        return ERR_FILE_DIMENSIONS;
    }

    if (rows < 1 || cols < 1)
    {
        fclose(in_file);
        return ERR_FILE_DIMENSIONS;
    }

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->elements = allocate_matrix(matrix->rows, matrix->cols);
    if (!matrix->elements)
    {
        fclose(in_file);
        return ERR_NO_MEMORY;
    }

    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            if (fscanf(in_file, "%lf", &matrix->elements[i][j]) != 1)
            {
                free_matrix(matrix->elements);
                fclose(in_file);
                return ERR_FILE_STRUCT;
            }
    if (fscanf(in_file, "%lf", &tmp) == 1 || !feof(in_file))
    {
        free_matrix(matrix->elements);
        fclose(in_file);
        return ERR_FILE_STRUCT;
    }

    fclose(in_file);
    return OK;   
}

// Функция записи данных из матрицы в текстовый файл
// Принимает матрицу и имя текстового файла
// Возвращает код ошибки
int write_matrix(matrix_t matrix, const char *filename)
{
    FILE *out_file;

    out_file = fopen(filename, "w");
    if (out_file == NULL)
        return ERR_FILE_OUT_ACCESS;

    fprintf(out_file, "%zu %zu \n", matrix.rows, matrix.cols);
    for (size_t i = 0; i < matrix.rows; i++)
    {
        for (size_t j = 0; j < matrix.cols; j++)
            fprintf(out_file, "%lf ", matrix.elements[i][j]);
        fprintf(out_file, "\n");
    }
    fclose(out_file);
    return OK;
}
