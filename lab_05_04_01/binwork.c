#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "errors.h"
#include "binwork.h"

#define ERR_STRUCT -1
#define ERR_EOF -2

// Максимальная длина 32-битного беззнакового числа в текстовом десятическом представлении
#define MAX_32_BIT_STRING 10


// Функция чтения строки из текстового файла
// Принимает строку по указателю, ее максимальную длину и файловую переменную
// Возвращает код ошибки
int read_string(char *str, size_t len, FILE *file)
{
    if (fgets(str, len, file) == NULL)
        return ERR_EOF;
    len = strlen(str);
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
    else if (fgetc(file) != '\n')
        return ERR_STRUCT;

    return OK;
}

// Функция чтения 32-битного числа из текстового файла
// Принимает указатель на число и файловую переменную
// Возвращает код ошибки
int read_uint32(uint32_t *num, FILE *file)
{
    char buf[MAX_32_BIT_STRING + 2];
    char *endptr;
    long long tmp_num;

    if (fgets(buf, MAX_32_BIT_STRING + 2, file) == NULL)
        return ERR_STRUCT;

    if (!isdigit(buf[0]))
        return ERR_STRUCT;

    tmp_num = strtoll(buf, &endptr, 10);
    if (*endptr != '\n')
        return ERR_STRUCT;
    if (tmp_num > UINT32_MAX || tmp_num < 0)
        return ERR_STRUCT;

    *num = (uint32_t)tmp_num;
    return OK;
}

// Функция чтения структуры студента из текстового файла
// Принимает указатель на структуру студента и файловую переменную
// Возвращает код ошибки
int read_student(struct student *stud, FILE *file)
{
    int ret_code;

    ret_code = read_string(stud->surname, SURNAME_LEN + 1, file);
    if (ret_code != OK)
        return ret_code;
    
    ret_code = read_string(stud->name, NAME_LEN + 1, file);
    if (ret_code != OK)
        return ERR_STRUCT;

    for (size_t i = 0; i < MARKS_N; i++)
    {
        ret_code = read_uint32(&stud->marks[i], file);
        if (ret_code != OK)
            return ERR_STRUCT;
    }
    return OK;
}

// Функция импорта данных из текстового файла в бинарный
// Принимает имя текстового файла и имя бинарного файла
// Возвращает код ошибки
int import_file(char *text_name, char *bin_name)
{
    FILE *in_file, *out_file;
    struct student tmp_student = { 0 };
    int ret_code;

    in_file = fopen(text_name, "r");
    if (in_file == NULL)
        return ERR_IMPORT;

    out_file = fopen(bin_name, "wb");
    if (out_file == NULL)
    {
        fclose(in_file);
        return ERR_IMPORT;
    }

    while ((ret_code = read_student(&tmp_student, in_file)) == OK)
        fwrite(&tmp_student, STRUCT_SIZE, 1, out_file);

    fclose(out_file);

    if (ret_code != ERR_EOF)
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

    if (file_len % STRUCT_SIZE != 0)
        return 0;

    return file_len / STRUCT_SIZE;
}

// Функция записи данных из бинарного файла в текстовый поток(файл)
// Принимает файловые переменные открытого на чтение бинарного файла,
// открытого на запись текстового файла и длину файла в элементах
void write_file_to_stream(FILE *in_file, FILE *out_file, size_t file_len)
{
    struct student tmp_student;

    for (size_t i = 0; i < file_len; i++)
    {
        fread(&tmp_student, STRUCT_SIZE, 1, in_file);
        fprintf(out_file, "%s\n%s\n", tmp_student.surname, tmp_student.name);
        for (size_t j = 0; j < MARKS_N; j++)
            fprintf(out_file, "%" PRIu32 "\n", tmp_student.marks[j]);
    }
}

// Функция экспорта данных из бинарного файла в текстовый
// Принимает имя бинарного файла и имя текстового файла
// Возвращает код ошибки
int export_file(char *bin_name, char *text_name)
{
    FILE *in_file, *out_file;
    size_t file_len;

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

    write_file_to_stream(in_file, out_file, file_len);

    fclose(in_file);
    fclose(out_file);

    return OK;    
}
