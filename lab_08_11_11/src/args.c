#include <string.h>

#include "errors.h"
#include "args.h"


// Функция анализа переданных аргументов
// Принимает количество переданных аргументов, указатели на переданные аргументы
// Изменяет режим работы по указателю
// Возвращает код ошибки
int process_args(int argc, char **argv, mode_t *mode)
{
    switch (argc)
    {
        case 4:
            if (strcmp(argv[1], "o") == 0)
                *mode = SOLVE;
            else
                return ERR_ARGS;
            break;
        case 5:
            if (strcmp(argv[1], "a") == 0)
                *mode = ADD;
            else if (strcmp(argv[1], "m") == 0)
                *mode = MULTIPLY;
            else
                return ERR_ARGS;
            break;
        default:
            return ERR_ARGS;
    }
    return OK;
}
