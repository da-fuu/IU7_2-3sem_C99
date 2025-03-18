#include <math.h>
#include "file.h"
#include "errors.h"


// Функция для подсчета среднего арифметического в последовательности чисел файла
// Принимает файловую переменную, изменяет по указателю переменную среднего арифметического и количества чисел
// Возвращает код ошибки
int find_avg(FILE *f, double *avg, size_t *len)
{
    double number, sum = 0.0;
    if (fscanf(f, "%lf", &number) != 1)
        return ERR_INPUT;
    sum += number;
    *len = 1;
    
    while (fscanf(f, "%lf", &number) == 1)
    {
        sum += number;
        (*len)++;
    }

    if (!feof(f))
        return ERR_FILE_CONTENT;

    *avg = sum / *len;

    return OK;
}

// Функция для подсчета дисперсии в последовательности чисел файла
// Принимает файловую переменную, изменяет по указателю переменную дисперсии
// Возвращает код ошибки
int find_disp(FILE *f, double *dispersion)
{
    double number, sq_sum = 0.0, avg;
    size_t len;
    int rc;

    rc = find_avg(f, &avg, &len);
    if (rc != OK)
        return rc;

    rewind(f);
    
    while (fscanf(f, "%lf", &number) == 1)
        sq_sum += pow((number - avg), 2);
    
    *dispersion = sq_sum / len;

    return OK;
}
