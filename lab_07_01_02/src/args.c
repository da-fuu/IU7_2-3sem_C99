#include <string.h>
#include "errors.h"
#include "args.h"


// Функция анализа переданных аргументов
// Принимает количество переданных аргументов, указатели на переданные аргументы
// Изменяет флаг необходимости фильтрации по указателю
// Возвращает код ошибки
int process_args(int argc, char **argv, bool *key_flag)
{
    if (argc < 3 || argc > 4)
        return ERR_ARGS;

    if (argc == 4)
        if (strcmp(argv[3], "f") == 0)
            *key_flag = true;
        else
            return ERR_ARGS;
    else
        *key_flag = false;

    return OK;
}
