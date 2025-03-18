#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "binwork.h"


// Функция импорта данных из текстового файла в бинарный
// Принимает имя текстового файла и имя бинарного файла
// Возвращает код ошибки
int import_file(char *text_name, char *bin_name)
{
    FILE *in_file, *out_file;
    int num;

    in_file = fopen(text_name, "r");
    if (in_file == NULL)
        return ERR_IMPORT;

    out_file = fopen(bin_name, "wb");
    if (out_file == NULL)
    {
        fclose(in_file);
        return ERR_IMPORT;
    }

    if (fscanf(in_file, "%d", &num) != 1)
    {
        fclose(in_file);
        fclose(out_file);
        return ERR_IMPORT;
    }

    do
    {
        fwrite(&num, sizeof(int), 1, out_file);
    } 
    while (fscanf(in_file, "%d", &num) == 1);
    
    fclose(out_file);

    if (!feof(in_file))
    {
        fclose(in_file);
        return ERR_IMPORT;
    }

    fclose(in_file);
    
    return OK;   
}

// Функция нахождения длины файла в элементах
// В случае ошибки возвращает 0
size_t find_file_len(FILE *file)
{
    size_t file_len;
    fseek(file, 0, SEEK_END);
    file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_len % sizeof(int) != 0)
        return 0;

    return file_len / sizeof(int);
}

// Функция экспорта данных из бинарного файла в текстовый
// Принимает имя бинарного файла и имя текстового файла
// Возвращает код ошибки
int export_file(char *bin_name, char *text_name)
{
    FILE *in_file, *out_file;
    size_t file_len;
    int num;

    in_file = fopen(bin_name, "rb");
    if (in_file == NULL)
        return ERR_EXPORT;

    file_len = find_file_len(in_file);
    if (file_len == 0)
        return ERR_EXPORT;

    out_file = fopen(text_name, "w");
    if (out_file == NULL)
    {
        fclose(in_file);
        return ERR_EXPORT;
    }

    for (size_t i = 0; i < file_len; i++)
    {
        fread(&num, sizeof(int), 1, in_file);
        fprintf(out_file, "%d ", num);
    }
    fprintf(out_file, "\n");
    
    fclose(in_file);
    fclose(out_file);

    return OK;    
}
