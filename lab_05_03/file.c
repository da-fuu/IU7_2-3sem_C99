#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "errors.h"
#include "binwork.h"


// Функция создания файла с заданным количеством случайных чисел
// Принимает имя файла и количество случайных чисел
// Возвращает код ошибки
int create_file_with_num(char *file_name, long num_len)
{
    FILE *file;
    int num;

    if (num_len < 1)
        return ERR_CREATE_ARGS;

    file = fopen(file_name, "wb");
    if (file == NULL)
        return ERR_FILE_ACCESS;

    for (long i = 0; i < num_len; i++)
    {
        num = rand();
        fwrite(&num, sizeof(int), 1, file);
    }
    fclose(file);

    return OK;    
}

// Функция печати содержимого файла
// Принимает имя файла
// Возвращает код ошибки
int print_file(char *file_name)
{
    FILE *file;
    size_t file_len;
    int num;

    file = fopen(file_name, "rb");
    if (file == NULL)
        return ERR_FILE_ACCESS;

    file_len = find_file_len(file);
    if (file_len == 0)
        return ERR_FILE_READ;

    printf("Содержимое файла: \n");
    for (size_t i = 0; i < file_len; i++)
    {
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    fclose(file);

    return OK;    
}

// Функция получения числа из файла по позиции
// Принимает файловую переменную и позицию
// Возвращает число из файла
int get_number_by_pos(FILE *file, size_t pos)
{
    int num;
    fseek(file, pos * sizeof(int), SEEK_SET);
    fread(&num, sizeof(int), 1, file);
    return num;
}

// Функция записи числа по позиции
// Принимает файловую переменную, позицию и число
void put_number_by_pos(FILE *file, size_t pos, int num)
{
    fseek(file, pos * sizeof(int), SEEK_SET);
    fwrite(&num, sizeof(int), 1, file);
}

// Функция сортировки файла
// Принимает имя файла
// Возвращает код ошибки
int sort_file(char *file_name)
{
    FILE *file;
    size_t file_len;
    int num1, num2;

    file = fopen(file_name, "r+b");
    if (file == NULL)
        return ERR_FILE_ACCESS;

    file_len = find_file_len(file);
    if (file_len == 0)
        return ERR_FILE_READ;

    for (size_t i = 0; i < file_len - 1; i++)
    {
        for (size_t j = 0; j < file_len - 1 - i; j++)
        {
            num1 = get_number_by_pos(file, j);
            num2 = get_number_by_pos(file, j + 1);
            if (num1 > num2)
            {
                put_number_by_pos(file, j, num2);
                put_number_by_pos(file, j + 1, num1);
            }
        }
    }

    fclose(file);

    return OK; 
}
