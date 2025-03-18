#include <string.h>
#include "errors.h"
#include "args.h"


// Функция анализа переданных аргументов
// Принимает количество переданных аргументов, указатели на переданные аргументы
// Изменяет переменную режима работы программы и типа поля по указателю
// Возвращает код ошибки
int process_args(int argc, char **argv, enum mode_e *mode, enum field_e *field)
{
    if (argc < 3 || argc > 4)
        return ERR_ARGS;

    if (strcmp(argv[2], "title") == 0)
        *field = TITLE;
    else if (strcmp(argv[2], "name") == 0)
        *field = NAME;
    else if (strcmp(argv[2], "year") == 0)
        *field = YEAR;
    else
        return ERR_ARGS;

    if (argc == 3)
        *mode = PRINT;
    else
        *mode = FIND;
        
    return OK;
}
