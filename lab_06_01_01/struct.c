#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "struct.h"


// Максимальная длина целого числа типа int в текстовом десятическом представлении
#define MAX_INT_BIT_STRING 10


// Функция чтения строки из текстового файла
// Принимает строку по указателю, ее максимальную длину и файловую переменную
// Возвращает код ошибки
int read_string(char *str, size_t len, FILE *file)
{
    if (fgets(str, len, file) == NULL)
        return ERR_EOF;
    len = strlen(str);
    if (len <= 1)
        return ERR_STRUCT;
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
    else if (fgetc(file) != '\n')
        return ERR_STRUCT;

    return OK;
}

// Функция чтения целого числа из текстового файла
// Принимает указатель на число и файловую переменную
// Возвращает код ошибки
int read_int(int *num, FILE *file)
{
    char buf[MAX_INT_BIT_STRING + 2];
    char *endptr;
    long long tmp_num;

    if (fgets(buf, MAX_INT_BIT_STRING + 2, file) == NULL)
        return ERR_STRUCT;

    if (!isdigit(buf[0]))
        return ERR_STRUCT;

    tmp_num = strtoll(buf, &endptr, 10);
    if (*endptr != '\n' && *endptr != '\0')
        return ERR_STRUCT;
    if (tmp_num > INT_MAX || tmp_num < 0)
        return ERR_STRUCT;

    *num = (int)tmp_num;
    return OK;
}

// Функция чтения структуры фильма из текстового файла
// Принимает указатель на структуру фильма и файловую переменную
// Возвращает код ошибки
int read_film(struct film_s *film, FILE *file)
{
    int ret_code;

    ret_code = read_string(film->title, TITLE_LEN + 1, file);
    if (ret_code != OK)
        return ret_code;
    
    ret_code = read_string(film->name, NAME_LEN + 1, file);
    if (ret_code != OK)
        return ERR_STRUCT;

    ret_code = read_int(&film->year, file);
    if (ret_code != OK)
        return ERR_STRUCT;

    return OK;
}

// Функция печати фильма
// Принимает указатель на структуру фильма
void print_film(struct film_s *film)
{
    printf("%s\n", film->title);
    printf("%s\n", film->name);
    printf("%d\n", film->year);
}
