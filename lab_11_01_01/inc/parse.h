#ifndef PARSE_H__
#define PARSE_H__

#include <stdbool.h>

#define NOT_SPECIFIED (-1)
#define NEED_ARG (-2)

// Структура сведений о спецификаторе
typedef struct
{
    struct
    {
        bool minus;
        bool plus;
        bool space;
        bool alt;
        bool zero;
    } flags;
    int width;
    int precision;
    enum
    {
        S,
        HO
    } type;
} spec_info_t;


// Функция считывания данных о спецификаторе. Принимает указатель на спецификатор и изменяет его по указателю, 
// изменяет по указателю данные о спецификаторе. Возвращает флаг успешности чтения.
bool parse_spec(const char *restrict *format, spec_info_t *spec_info);


#endif // #ifndef PARSE_H__
