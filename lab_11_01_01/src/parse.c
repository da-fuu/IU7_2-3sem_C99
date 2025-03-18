#include "parse.h"

// Функция проверки символа на, то является ли он флагом спецификатора. Возвращает результат проверки
static bool is_flag(char chr)
{
    return chr == '-' || chr == '+' || chr == ' ' || chr == '#' || chr == '0';
}

// Функция проверки символа на, то является ли он числом. Возвращает результат проверки
static bool is_digit(char chr)
{
    return chr >= '0' && chr <= '9';
}

// Инициализация полей структуры, принимает ее по указателю
static void init_spec_info(spec_info_t *spec_info)
{
    spec_info->flags.minus = false;
    spec_info->flags.plus = false;
    spec_info->flags.space = false;
    spec_info->flags.zero = false;
    spec_info->flags.alt = false;
    
    spec_info->width = NOT_SPECIFIED;
    spec_info->precision = NOT_SPECIFIED;
}

// Функция считывания данных о спецификаторе. Принимает указатель на спецификатор и изменяет его по указателю, 
// изменяет по указателю данные о спецификаторе. Возвращает флаг успешности чтения.
bool parse_spec(const char *restrict *format, spec_info_t *spec_info)
{
    (*format)++;
    init_spec_info(spec_info);
    
    while (is_flag(**format))
    {
        switch (**format)
        {
            case '-':
                spec_info->flags.minus = true;
                break;
            case '+':
                spec_info->flags.plus = true;
                break;
            case ' ':
                spec_info->flags.space = true;
                break;
            case '#':
                spec_info->flags.alt = true;
                break;
            case '0':
                spec_info->flags.zero = true;
                break;
        }
        (*format)++;
    }
    
    if (spec_info->flags.space && spec_info->flags.plus)
        spec_info->flags.space = false;
    
    if (spec_info->flags.zero && spec_info->flags.minus)
        spec_info->flags.zero = false;
    
    if (**format == '*' || is_digit(**format))
    {
        if (**format == '*')
        {
            spec_info->width = NEED_ARG;
            (*format)++;
        }
        else
        {
            spec_info->width = 0;
            while (is_digit(**format))
            {
                spec_info->width = spec_info->width * 10 + (**format - '0');
                (*format)++;
            }
        }
    }
    
    if (**format == '.')
    {
        (*format)++;
        if (**format == '*')
        {
            spec_info->precision = NEED_ARG;
            (*format)++;
        }
        else
        {
            spec_info->precision = 0;
            while (is_digit(**format))
            {
                spec_info->precision = spec_info->precision * 10 + (**format - '0');
                (*format)++;
            }
        }
    }
    
    if (**format == 's')
        spec_info->type = S;
    else if (**format == 'h' && *++*format == 'o')
        spec_info->type = HO;
    else
        return false;
    (*format)++;
    
    return true;
}
