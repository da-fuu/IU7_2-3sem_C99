#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "file_filter.h"
#include "errors.h"
#include "binwork.h"


// Функция фильтрации студентов по фамилии
// Принимает имя входного файла, имя выходного файла и подстроку для фильтрации
// Возвращает код ошибки
int filter_file(char *file_name_in, char *file_name_out, char *surname_substr)
{
    FILE *in_file, *out_file;
    size_t file_len;
    struct student stud;
    bool output = false;

    size_t substr_len = strlen(surname_substr);

    if (substr_len == 0 || substr_len > SURNAME_LEN)
        return ERR_FILTER_ARGS;

    in_file = fopen(file_name_in, "rb");
    if (in_file == NULL)
        return ERR_FILE_ACCESS;

    file_len = find_file_len(in_file);
    if (file_len == 0)
        return ERR_FILE_READ;

    out_file = fopen(file_name_out, "wb");
    if (out_file == NULL)
    {
        fclose(in_file);
        return ERR_FILE_ACCESS;
    }

    for (size_t i = 0; i < file_len; i++)
    {
        fread(&stud, STRUCT_SIZE, 1, in_file);
        if (strstr(stud.surname, surname_substr) == stud.surname)
        {
            fwrite(&stud, STRUCT_SIZE, 1, out_file);
            output = true;
        }
    }

    fclose(in_file);
    fclose(out_file);

    if (!output)
        return ERR_EMPTY_OUTPUT;

    return OK;
}
