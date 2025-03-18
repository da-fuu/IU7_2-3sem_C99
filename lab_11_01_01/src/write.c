#include "write.h"


// Функция нахождения длины строки с учетом точности. Принимает строку и максимальную длину.
// Возвращает найденную длину.
static int string_len_to_write(const char *str, int max_len)
{
    int len = 0;
    while ((len < max_len || max_len == NOT_SPECIFIED) && str[len] != '\0')
        len++;
    
    return len;
}

// Функция записи вставки символа в строку. Принимает указатель на выходную строку, указатель на текущую позицию в строке, максимальное 
// количество символов к записи, символ к записи, изменяет по указателю общий размер строки
void write_char(char *restrict s, size_t *cur_pos, size_t max_n, int *total_len, char chr)
{
    if (*cur_pos + 1 < max_n)
        s[(*cur_pos)++] = chr;
    (*total_len)++;
}

// Функция записи вставки строки в строку. Принимает указатель на выходную строку, указатель на текущую позицию в строке, максимальное 
// количество символов к записи, информацию о спецификаторе, строку к записи, изменяет по указателю общий размер строки
// Возвращает флаг успешности печати
bool write_string(char *restrict s, size_t *cur_pos, size_t max_n, int *total_len, spec_info_t *spec_info, const char *s_arg)
{
    int len;
    int padding = 0;
    
    if (spec_info->flags.alt)
        return false;

    if (spec_info->flags.zero)
        return false;

    len = string_len_to_write(s_arg, spec_info->precision);
    
    if (spec_info->width != NOT_SPECIFIED && spec_info->width > len)
        padding = spec_info->width - len;
    
    if (!spec_info->flags.minus)
        while (padding > 0)
        {
            write_char(s, cur_pos, max_n, total_len, ' ');
            padding--;
        }

    for (int i = 0; i < len; i++)
    {
        write_char(s, cur_pos, max_n, total_len, s_arg[i]);
    }

    while (padding > 0)
    {
        write_char(s, cur_pos, max_n, total_len, ' ');
        padding--;
    }
    
    return true;
}

// Функция нахождения длины числа в 8-ной СС. Принимает число. Возвращает найденную длину.
static int find_oct_len(unsigned short int num)
{
    int len = 0;
    while (num > 0)
    {
        num /= 8;
        len++;
    }
    return len;
}

// Функция вставки числа в 8-ной СС в строку. Принимает указатель на выходную строку, указатель на текущую позицию в строке, максимальное 
// количество символов к записи, число к записи и его длину, изменяет по указателю общий размер строки
static void write_oct_num(char *restrict s, size_t *cur_pos, size_t max_n, int *total_len, unsigned short int num, int num_len)
{
    int digit;
    
    int base = 1;
    for (int i = 0; i < num_len - 1; i++)
        base *= 8;
    
    for (int i = num_len; i > 0; i--)
    {
        digit = (num / base) % 8;
        base /= 8;

        write_char(s, cur_pos, max_n, total_len, (char)(digit + '0'));
    }
}

// Функция вставки числа в 8-ной СС в строку. Принимает указатель на выходную строку, указатель на текущую позицию в строке, максимальное 
// количество символов к записи, информацию о спецификаторе, число к записи, изменяет по указателю общий размер строки
// Возвращает флаг успешности печати
bool write_short_octal(char *restrict s, size_t *cur_pos, size_t max_n, int *total_len, spec_info_t *spec_info, unsigned short int ho_arg)
{
    int num_len;
    int padding = 0;
    char pad_char = ' ';
    
    if (spec_info->precision != NOT_SPECIFIED)
        spec_info->flags.zero = false;
    else
        spec_info->precision = 1;
        
    num_len = find_oct_len(ho_arg);
    if (spec_info->precision > num_len)
        num_len = spec_info->precision;
    else if (spec_info->flags.alt)
        num_len++;
    
    if (spec_info->width != NOT_SPECIFIED && spec_info->width > num_len)
    {
        padding = spec_info->width - num_len;
        if (!spec_info->flags.minus)
        {
            if (spec_info->flags.zero)
                pad_char = '0';
            for (; padding > 0; padding--)
                write_char(s, cur_pos, max_n, total_len, pad_char);
        }
    }
    
    write_oct_num(s, cur_pos, max_n, total_len, ho_arg, num_len);
    
    if (padding > 0)
        for (int i = 0; i < padding; i++)
            write_char(s, cur_pos, max_n, total_len, pad_char);
    
    return true;
}
