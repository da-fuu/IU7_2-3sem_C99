#include <string.h>
#include <malloc.h>
#include "errors.h"
#include "file.h"


// Функция поиска количества чисел в файле
// Принимает файловую переменную, изменяет переменную количества по указателю
// Возвращает код ошибки
static int find_file_len(FILE *file, size_t *len)
{
    int tmp;
    *len = 0;

    if (fscanf(file, "%d", &tmp) != 1)
        return ERR_FILE_EMPTY;
    (*len)++;

    while (fscanf(file, "%d", &tmp) == 1)
        (*len)++;

    if (!feof(file))
        return ERR_FILE_STRUCT;

    rewind(file);
    return OK;
}


// Функция чтения данных из текстового файла в массив
// Принимает имя текстового файла, изменяет указатели на начало и конец массива по указателю
// Возвращает код ошибки
int read_file(const char *filename, int **ptr_beg, int **ptr_end)
{
    FILE *in_file;
    int ret_code;
    size_t arr_len;

    in_file = fopen(filename, "r");
    if (in_file == NULL)
        return ERR_FILE_IN_ACCESS;

    ret_code = find_file_len(in_file, &arr_len);
    if (ret_code != OK)
        return ret_code;

    *ptr_beg = malloc(sizeof(int) * arr_len);
    if (*ptr_beg == NULL)
    {
        fclose(in_file);
        return ERR_NO_MEMORY;
    }
    *ptr_end = *ptr_beg;

    for (size_t i = 0; i < arr_len; i++)
    {
        fscanf(in_file, "%d", *ptr_end);
        (*ptr_end)++;
    }
    fclose(in_file);
    return OK;   
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
