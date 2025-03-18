#include <stdio.h>

#include "errors.h"
#include "file.h"

// Чтение размерностей квадратной матрицы из файла
// Принимает имя файла, изменяет размерность по указателю, возвращает код ошибки
int read_dimensions(char *filename, int *n)
{
    FILE *file;
    int rows, cols;
    int read;

    file = fopen(filename, "r");
    if (file == NULL)
        return ERR_FILE_IN;

    read = fscanf(file, "%d%d", &rows, &cols);
    fclose(file);
    if (read <= 0)
        return ERR_FILE_EMPTY;
    if (read != 2)
        return ERR_FILE_DIMENSIONS;

    if (rows < 1 || cols < 1)
        return ERR_FILE_DIMENSIONS;

    if (rows != cols)
        return ERR_FILE_DIMENSIONS;

    *n = rows;
    return OK;
}

// Чтение квадратной матрицы из файла
// Принимает имя файла, матрицу и размерность, изменяет матрицу, возвращает код ошибки
int read_matrix(char *filename, int **matrix, int n)
{
    FILE *file;
    int tmp1, tmp2;

    file = fopen(filename, "r");
    if (file == NULL)
        return ERR_FILE_IN;

    fscanf(file, "%d%d", &tmp1, &tmp2);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (fscanf(file, "%d", &matrix[i][j]) != 1)
            {
                fclose(file);
                return ERR_FILE_STRUCT;
            }
    if (fscanf(file, "%d", &tmp1) == 1 || !feof(file))
    {
        fclose(file);
        return ERR_FILE_STRUCT;
    }

    fclose(file);
    return OK;
}

// Запись квадратной матрицы в файл
// Принимает матрицу и размерность, возвращает код ошибки
int write_sq_matrix(int **matrix, int n, char *filename)
{
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL)
        return ERR_FILE_OUT;

    fprintf(file, "%d %d \n", n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fprintf(file, "%d ", matrix[i][j]);
        fprintf(file, "\n");
    }

    fclose(file);
    return OK;
}
