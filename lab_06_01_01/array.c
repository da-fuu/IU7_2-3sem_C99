#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "struct.h"
#include "array.h"


// Функция вычисления разницы между 2 полями
// Принимает два обьединения-поля и тип хранимого в них поля
// Возвращает разницу между полями
int get_field_diff(union field_union field1, union field_union field2, enum field_e field_type) 
{
    int diff = 0;
             
    switch (field_type)
    {
        case TITLE:
            diff = strncmp(field1.str, field2.str, TITLE_LEN);    
            break;
        case NAME:
            diff = strncmp(field1.str, field2.str, NAME_LEN);    
            break;
        case YEAR:
            diff = field1.year - field2.year;    
            break;
    }
    return diff;
}

// Функция вычисления разницы у двух структур по полю
// Принимает указатели на 2 структуры и тип поля
// Возвращает разницу между полями структур 
int compare_by_field(struct film_s *film1, struct film_s *film2, enum field_e field)
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
// массив структур по указателю и его новую длину 
void insert_film_in_arr(struct film_s *film, enum field_e field, struct film_s films_arr[], size_t new_len)
{
    size_t i = 0;

    while (i < new_len - 1)
    {
        if (compare_by_field(&films_arr[i], film, field) > 0)
            break;
        i++;
    }
    for (size_t j = new_len - 1; j > i; j--)
        films_arr[j] = films_arr[j - 1];

    films_arr[i] = *film;
}

// Функция чтения данных из текстового файла в массив
// Принимает имя текстового файла, массив структур и его длину по указателю и значение поля для сортировки
// Возвращает код ошибки
int read_file(char *filename, struct film_s films_arr[], size_t *arr_len, enum field_e field)
{
    FILE *in_file;
    struct film_s tmp_film;
    int ret_code;

    in_file = fopen(filename, "r");
    if (in_file == NULL)
        return ERR_FILE_ACCESS;

    *arr_len = 0;
    while ((ret_code = read_film(&tmp_film, in_file)) == OK)
    {
        (*arr_len)++;
        if (*arr_len > MAX_FILE_LEN)
            return ERR_FILE_TOO_LONG;
        insert_film_in_arr(&tmp_film, field, films_arr, *arr_len);
    }
    fclose(in_file);
    
    if (ret_code != ERR_EOF)
        return ERR_FILE_STRUCT;

    if (*arr_len == 0)
        return ERR_EMPTY_FILE;

    return OK;   
}

// Функция печати данных из массива
// Принимает массив структур и его длину
void print_arr(struct film_s films_arr[], size_t arr_len)
{
    for (size_t i = 0; i < arr_len; i++)
        print_film(&films_arr[i]);
}

// Функция бинарного поиска структуры в массиве по полю
// Принимает массив структур по указателю, его длину, тип поля для поиска, обьединение с полем для поиска
int find_by_field(struct film_s films_arr[], size_t arr_len, enum field_e field_type, union field_union field_to_find)
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
int find_film(struct film_s films_arr[], size_t arr_len, enum field_e field_type, char *str, int *index_finded)
{
    union field_union field_to_find;

    long long tmp_year;
    char *endptr;

    switch (field_type)
    {
        case TITLE:
            if (strlen(str) > TITLE_LEN)
                return ERR_FIND_ARG;
            field_to_find.str = str;
            break;
        case NAME:
            if (strlen(str) > NAME_LEN)
                return ERR_FIND_ARG;
            field_to_find.str = str;
            break;
        case YEAR:
            if (!isdigit(str[0]))
                return ERR_FIND_ARG;
            tmp_year = strtoll(str, &endptr, 10);
            if (*endptr != '\0')
                return ERR_FIND_ARG;
            if (tmp_year > INT_MAX || tmp_year < 0)
                return ERR_FIND_ARG;

            field_to_find.year = (int)tmp_year;
            break;
    }

    *index_finded = find_by_field(films_arr, arr_len, field_type, field_to_find);

    return OK;
}
