#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "filesort.h"
#include "errors.h"
#include "binwork.h"


// Функция получения структуры из файла по позиции
// Принимает файловую переменную и позицию
// Принимает и изменяет структуру по указателю
void get_student_by_pos(FILE *file, size_t pos, struct student *stud)
{
    fseek(file, pos * STRUCT_SIZE, SEEK_SET);
    fread(stud, STRUCT_SIZE, 1, file);
}

// Функция записи структуры по позиции
// Принимает файловую переменную, позицию и указатель на структуру
void put_student_by_pos(FILE *file, size_t pos, struct student *stud)
{
    fseek(file, pos * STRUCT_SIZE, SEEK_SET);
    fwrite(stud, STRUCT_SIZE, 1, file);
}

// Функция сравнения двух студентов
// Принимает указатели на первого и второго студента
// Возвращает true, если первый студент больше второго, иначе false
bool is_stud_greater(struct student *stud1, struct student *stud2)
{
    int diff;
    
    diff = strncmp(stud1->surname, stud2->surname, SURNAME_LEN + 1);
    if (diff != 0)
        return diff > 0;

    diff = strncmp(stud1->name, stud2->name, NAME_LEN + 1);
    return diff > 0;
}

// Функция сортировки файла
// Принимает имя файла
// Возвращает код ошибки
int sort_file(char *file_name)
{
    FILE *file;
    size_t file_len;
    struct student stud1, stud2;

    file = fopen(file_name, "r+b");
    if (file == NULL)
        return ERR_FILE_ACCESS;

    file_len = find_file_len(file);
    if (file_len == 0)
        return ERR_FILE_READ;

    for (size_t i = 0; i < file_len - 1; i++)
        for (size_t j = 0; j < file_len - 1 - i; j++)
        {
            get_student_by_pos(file, j, &stud1);
            get_student_by_pos(file, j + 1, &stud2);
            if (is_stud_greater(&stud1, &stud2))
            {
                put_student_by_pos(file, j, &stud2);
                put_student_by_pos(file, j + 1, &stud1);
            }
        }

    fclose(file);

    return OK; 
}

// Функция печати содержимого корректного файла на экран
// Принимает имя файла
void print_file(char *file_name)
{
    FILE *file;
    size_t file_len;

    file = fopen(file_name, "rb");
    file_len = find_file_len(file);

    write_file_to_stream(file, stdout, file_len);
}
