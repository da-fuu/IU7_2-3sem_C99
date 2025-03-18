#include <stdbool.h>
#include "process.h"


// Функция для нахождения минимального нечетного элемента под главной диагональю
// Принимает матрицу по указателю и количество строк(столбцов), изменяет искомое число по указателю, возвращает код ошибки
int find_min_odd_under_diag(int matrix[][DIMENSION], size_t dimension, int *out)
{
    bool odd_finded = false;

    if (dimension < 2)
        return ERROR_TOO_SMALL;

    for (size_t i = 0; i < dimension; i++)
        for (size_t j = 0; j < i; j++)
            if (matrix[i][j] % 2 != 0)
            {
                if (!odd_finded)
                {
                    *out = matrix[i][j];
                    odd_finded = true;
                    continue;
                }
                if (matrix[i][j] < *out)
                    *out = matrix[i][j];
            }
    
    if (!odd_finded)
        return ERROR_NO_ODD;

    return OK;
}
