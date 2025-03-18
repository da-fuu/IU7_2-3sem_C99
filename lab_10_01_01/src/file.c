#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct.h"
#include "list.h"
#include "errors.h"
#include "file.h"

#define ERR_EOF (-1)


// Функция чтения строки из текстового файла
// Принимает файловую переменную, изменяет строку по указателю
// Возвращает код ошибки
int read_string(FILE *file, char **str)
{
    size_t len = 0;
    *str = NULL;
    if (getline(str, &len, file) == -1)
    {
        free(*str);
        return ERR_EOF;
    }

    len = strcspn(*str, "\n");
    if (len < 1)
    {
        free(*str);
        return ERR_FILE_STRUCT;
    }

    (*str)[len] = '\0';
    *str = realloc(*str, len + 1);
    return OK;
}

// Функция чтения целого положительного числа из строки
// Принимает строку по указателю
// Возвращает число в строке или -1 при ошибке
int parse_int(const char *str)
{
    long tmp_int;
    char *endptr;

    if (!isdigit(str[0]))
        return -1;
    tmp_int = strtol(str, &endptr, 10);
    if (*endptr != '\0')
        return -1;
    return (int)tmp_int;
}

// Функция чтения целого положительного числа из текстового файла
// Принимает файловую переменную, изменяет число по указателю
// Возвращает код ошибки
int read_mark(FILE *file, int *mark)
{
    char *buf;

    if (read_string(file, &buf) != OK)
        return ERR_FILE_STRUCT;

    *mark = parse_int(buf);
    free(buf);
    if (*mark < 0 || *mark > 100)
        return ERR_FILE_STRUCT;

    return OK;
}

// Функция чтения структуры студента из текстового файла
// Принимает файловую переменную, изменяет указатель структуру студента по указателю
// Возвращает код ошибки
int read_student(FILE *file, student_t **student)
{
    int ret_code;

    *student = malloc(sizeof(student_t));
    if (*student == NULL)
        return ERR_NO_MEMORY;

    ret_code = read_string(file, &(*student)->name);
    if (ret_code != OK)
    {
        free(*student);
        return ret_code;
    }

    ret_code = read_mark(file, &(*student)->mark);
    if (ret_code != OK)
    {
        free_student(*student);
        return ERR_FILE_STRUCT;
    }
    return OK;
}

// Функция чтения данных из текстового файла в список
// Принимает имя текстового файла, изменяет указатель на голову списка по указателю
// Возвращает код ошибки
int read_students(const char *filename, node_t **head)
{
    FILE *in_file;
    student_t *tmp_student;
    int ret_code;
    node_t *end;

    in_file = fopen(filename, "r");
    if (in_file == NULL)
        return ERR_FILE_IN_ACCESS;

    ret_code = read_student(in_file, &tmp_student);
    if (ret_code != OK)
    {
        if (ret_code == ERR_EOF)
            ret_code = ERR_FILE_EMPTY;
        fclose(in_file);
        return ret_code;
    }
    end = NULL;
    ret_code = push_end(&end, tmp_student);
    if (ret_code != OK)
    {
        free_student(tmp_student);
        fclose(in_file);
        return ret_code;
    }
    *head = end;

    while ((ret_code = read_student(in_file, &tmp_student)) == OK)
    {
        ret_code = push_end(&end, tmp_student);
        if (ret_code != OK)
        {
            free_list(*head);
            free_student(tmp_student);
            fclose(in_file);
            return ret_code;
        }
    }
    fclose(in_file);
    if (ret_code != ERR_EOF)
    {
        free_list(*head);
        return ERR_FILE_STRUCT;
    }
    return OK;
}

// Запись одной структуры студента в файл
void write_student(FILE *file, student_t *data)
{
    fprintf(file, "%s\n%d\n", data->name, data->mark);
}

// Функция записи данных из списка в текстовый файл
// Принимает список и имя текстового файла
// Возвращает код ошибки
int write_students(node_t *head, const char *filename)
{
    FILE *out_file;

    out_file = fopen(filename, "w");
    if (out_file == NULL)
        return ERR_FILE_OUT_ACCESS;

    while (head != NULL)
    {
        write_student(out_file, head->data);
        head = head->next;
    }

    fclose(out_file);
    return OK;
}
