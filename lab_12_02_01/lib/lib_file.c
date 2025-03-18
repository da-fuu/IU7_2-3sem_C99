#include <stdio.h>

#include "errors.h"
#include "lib_file.h"


// Функция поиска количества чисел в файле
// Принимает имя файла, изменяет переменную количества по указателю
// Возвращает код ошибки
int find_file_len(const char *filename, size_t *len)
{
    int tmp;
    FILE *file;
    *len = 0;

    file = fopen(filename, "r");
    if (file == NULL)
        return ERR_FILE_IN_ACCESS;
    
    if (fscanf(file, "%d", &tmp) != 1)
    {
        fclose(file);
        return ERR_FILE_EMPTY;
    }
    (*len)++;

    while (fscanf(file, "%d", &tmp) == 1)
        (*len)++;

    if (!feof(file))
    {
        fclose(file);
        return ERR_FILE_STRUCT;
    }

    fclose(file);
    return OK;
}


// Функция чтения данных из текстового файла в массив
// Принимает имя текстового файла, указатели на начало и конец массива
void read_file(const char *filename, int *ptr_beg, const int *ptr_end)
{
    FILE *in_file = fopen(filename, "r");
    
    for (int *curr = ptr_beg; curr < ptr_end; curr++)
        fscanf(in_file, "%d", curr);
    
    fclose(in_file);
}


// Функция записи данных из массива текстовый файл
// Принимает имя текстового файла и указатели на начало и конец массива
// Возвращает код ошибки
int write_file(const char *filename, const int *ptr_beg, const int *ptr_end)
{
    FILE *out_file;

    out_file = fopen(filename, "w");
    if (out_file == NULL)
        return ERR_FILE_OUT_ACCESS;

    while (ptr_beg < ptr_end)
    {
        fprintf(out_file, "%d ", *ptr_beg);
        ptr_beg++;
    }
    fprintf(out_file, "\n");

    fclose(out_file);
    return OK;
}
