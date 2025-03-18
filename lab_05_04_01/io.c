#include <string.h>
#include "errors.h"
#include "io.h"


// Функция анализа переданных аргументов
// Принимает количество переданных аргументов, указатели на переданные аргументы
// Изменяет переменную режима работы программы по указателю
// Возвращает код ошибки
int process_args(int argc, char **argv, enum mode_e *mode)
{
    if (argc < 2)
        return ERR_ARGS;

    if (strncmp(argv[1], "fb", 3) == 0)
        *mode = FILTER;
    else if (strncmp(argv[1], "sb", 3) == 0)
        *mode = SORT;
    else if (strncmp(argv[1], "import", 7) == 0)
        *mode = IMPORT;
    else if (strncmp(argv[1], "export", 7) == 0)
        *mode = EXPORT;
    else
        return ERR_ARGS;

    if (*mode == FILTER && argc != 5)
        return ERR_FILTER_ARGS;
    if (*mode == SORT && argc != 3)
        return ERR_SORT_ARGS;
    if (*mode == IMPORT && argc != 4)
        return ERR_IMPORT;
    if (*mode == EXPORT && argc != 4)
        return ERR_EXPORT;
    
    return OK;
}
