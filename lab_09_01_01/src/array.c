#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "struct.h"
#include "array.h"


// Объединение для хранения значения одного поля
union field_union
{
    int year;
    const char *str;
};

// Функция вычисления разницы между 2 полями
// Принимает два объединения-поля и тип хранимого в них поля
// Возвращает разницу между полями
int get_field_diff(union field_union field1, union field_union field2, enum field_e field_type) 
{
    int diff = 0;
             
    if (field_type == YEAR)
        diff = field1.year - field2.year;
    else
        diff = strcmp(field1.str, field2.str);

    return diff;
}

// Функция вычисления разницы у двух структур по полю
// Принимает указатели на 2 структуры и тип поля
// Возвращает разницу между полями структур 
int compare_by_field(const struct film_s *film1, const struct film_s *film2, enum field_e field)
{
    union field_union field_to_cmp1, field_to_cmp2;

    switch (field)
    {
        case TITLE:
            field_to_cmp1.str = film1->title;
            field_to_cmp2.str = film2->title;
            break;
        case NAME:
            field_to_cmp1.str = film1->name;
            field_to_cmp2.str = film2->name;
            break;
        case YEAR:
            field_to_cmp1.year = film1->year;
            field_to_cmp2.year = film2->year;
            break;
    }
    return get_field_diff(field_to_cmp1, field_to_cmp2, field);
}

// Функция вставки элемента в отсортированный массив так, чтобы он остался отсортированным
// Принимает указатель на структуру для вставки, тип поля для сортировки, 
// массив структур по указателю и его старую длину
void insert_film_in_arr(const struct film_s *film, enum field_e field, struct film_s *films_arr, int old_len)
{
    int i = 0;

    while (i < old_len)
    {
        if (compare_by_field(&films_arr[i], film, field) > 0)
            break;
        i++;
    }
    for (int j = old_len; j > i; j--)
        films_arr[j] = films_arr[j - 1];

    films_arr[i] = *film;
}

// Функция для поиска длины файла
// Принимает файловую переменную и изменяет по указателю длину файла
// Возвращает код ошибки
int find_file_len(FILE *file, int *len)
{
    *len = 0;
    struct film_s tmp_film;
    int rc;

    while ((rc = read_film(file, &tmp_film)) == OK)
    {
        (*len)++;
        free_film(&tmp_film);
    }

    rewind(file);

    if (rc != ERR_EOF)
        return ERR_FILE_STRUCT;
    if (*len == 0)
        return ERR_EMPTY_FILE;
    return OK;
}

// Функция чтения данных из текстового файла в массив
// Принимает имя текстового файла, значение поля для сортировки
// Принимает и изменяет указатели на массив структур и его длину
// Возвращает код ошибки
int read_file(const char *filename, enum field_e field, struct film_s **films_arr, int *arr_len)
{
    FILE *in_file;
    struct film_s tmp_film;
    int ret_code;

    in_file = fopen(filename, "r");
    if (in_file == NULL)
        return ERR_FILE_ACCESS;

    ret_code = find_file_len(in_file, arr_len);
    if (ret_code != OK)
    {
        fclose(in_file);
        return ret_code;
    }

    *films_arr = malloc(sizeof(struct film_s) * *arr_len);
    if (*films_arr == NULL)
    {
        fclose(in_file);
        return ERR_NO_MEMORY;
    }

    for (int i = 0; i < *arr_len; i++)
    {
        read_film(in_file, &tmp_film);
        insert_film_in_arr(&tmp_film, field, *films_arr, i);
    }
    fclose(in_file);

    return OK;   
}

// Функция печати данных из массива
// Принимает массив структур по указателю и его длину
void print_arr(struct film_s *films_arr, int arr_len)
{
    for (int i = 0; i < arr_len; i++)
        print_film(&films_arr[i]);
}

// Функция бинарного поиска структуры в массиве по полю
// Принимает массив структур по указателю, его длину, тип поля для поиска, объединение с полем для поиска
int find_by_field(const struct film_s *films_arr, int arr_len, enum field_e field_type, union field_union field_to_find)
{
    int left = 0;
    int right = arr_len - 1;
    int mid;
    int diff;
    union field_union curr_field;

    while (left <= right)
    {
        mid = (left + right) / 2;
        
        switch (field_type)
        {
            case TITLE:
                curr_field.str = films_arr[mid].title;  
                break;  
            case NAME:
                curr_field.str = films_arr[mid].name;  
                break; 
            case YEAR:
                curr_field.year = films_arr[mid].year;   
                break;            
        }
        diff = get_field_diff(curr_field, field_to_find, field_type);

        if (diff == 0)
            return mid;

        if (diff < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Функция поиска фильма в массиве структур
// Принимает массив структур по указателю, его длину, тип поля к поиску, строку с полем
// Изменяет по указателю индекс структуры в массиве
// Возвращает код ошибки
int find_film(const struct film_s *films_arr, int arr_len, enum field_e field_type, const char *str, int *index_found)
{
    union field_union field_to_find;

    if (field_type == YEAR)
    {
        field_to_find.year = parse_int(str);
        if (field_to_find.year < 0)
            return ERR_FIND_ARG;
    }
    else
        field_to_find.str = str;

    *index_found = find_by_field(films_arr, arr_len, field_type, field_to_find);

    return OK;
}

// Функция освобождения массива структур
// Принимает массив структур по указателю и его длину
void free_arr(struct film_s *films_arr, int arr_len)
{
    for (int i = 0; i < arr_len; i++)
        free_film(&films_arr[i]);
    free(films_arr);
}
