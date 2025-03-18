#include <stdarg.h>

#include "parse.h"
#include "write.h"
#include "my_snprintf.h"


// Аналог функции snprintf для спецификаторов ho и s, обрабатывает спецификатор полностью, в соответствии со стандартом С99 
int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    int total_len = 0;
    size_t cur_pos = 0;
    spec_info_t spec_info;
    const char *s_arg;
    unsigned short int ho_arg;
    va_list arg_ptr;
    
    if (s == NULL && n > 0)
        return ERROR;

    va_start(arg_ptr, format);
    while (*format != '\0')
    {
        if (*format != '%')
        {
            write_char(s, &cur_pos, n, &total_len, *format);
            format++;
            continue;
        }
        if (!parse_spec(&format, &spec_info))
        {
            va_end(arg_ptr);
            return ERROR;
        }
        if (spec_info.width == NEED_ARG)
        {
            spec_info.width = va_arg(arg_ptr, int);
            if (spec_info.width < 0)
            {
                spec_info.flags.minus = true;
                spec_info.flags.zero = false;
                spec_info.width = -spec_info.width;
            }
        }
        if (spec_info.precision == NEED_ARG)
        {
            spec_info.precision = va_arg(arg_ptr, int);
            if (spec_info.precision < 0)
                spec_info.precision = NOT_SPECIFIED;
        }
        switch (spec_info.type)
        {
            case S:
                s_arg = va_arg(arg_ptr, char *);
                if (!write_string(s, &cur_pos, n, &total_len, &spec_info, s_arg))
                {
                    va_end(arg_ptr);
                    return ERROR;
                }
                break;
            case HO:
                ho_arg = va_arg(arg_ptr, unsigned int);
                if (!write_short_octal(s, &cur_pos, n, &total_len, &spec_info, ho_arg))
                {
                    va_end(arg_ptr);
                    return ERROR;
                }
                break;
        }
    }
    if (n > 0)
        s[cur_pos] = '\0';
    
    va_end(arg_ptr);
    return total_len;
}
