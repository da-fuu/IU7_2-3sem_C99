#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#include "errors.h"
#include "struct.h"


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
        return ERR_STRUCT;
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
    long long tmp_int;
    char *endptr;

    if (!isdigit(str[0]))
        return -1;
    tmp_int = strtoll(str, &endptr, 10);
    if (*endptr != '\0')
        return -1;
    if (tmp_int > INT_MAX || tmp_int < 0)
        return -1;
    return (int)tmp_int;
}

// Функция чтения целого положительного числа из текстового файла
// Принимает файловую переменную, изменяет число по указателю
// Возвращает код ошибки
int read_int(FILE *file, int *num)
{
    char *buf;

    if (read_string(file, &buf) != OK)
        return ERR_STRUCT;

    *num = parse_int(buf);
    free(buf);
    if (*num < 0)
        return ERR_STRUCT;

    return OK;
}

// Функция чтения структуры фильма из текстового файла
// Принимает файловую переменную, изменяет структуру фильма по указателю
// Возвращает код ошибки
int read_film(FILE *file, struct film_s *film)
{
    int ret_code;

    ret_code = read_string(file, &film->title);
    if (ret_code != OK)
        return ret_code;
    
    ret_code = read_string(file, &film->name);
    if (ret_code != OK)
    {
        free(film->title);
        return ERR_STRUCT;
    }

    ret_code = read_int(file, &film->year);
    if (ret_code != OK)
    {
        free_film(film);
        return ERR_STRUCT;
    }
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

// Функция освобождения структуры фильма
// Принимает структуру фильма по указателю
void free_film(struct film_s *film)
{
    free(film->title);
    free(film->name);
}
