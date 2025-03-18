#include <string.h>

#include "errors.h"
#include "args.h"


// Чтение аргументов командной строки
// Принимает кол-во аргументов, массив указателей на них
// Изменяет по указателю направление перемещений в матрице
// Возвращает код ошибки
int process_args(int argc, char **argv, swap_t *swap)
{
    if (argc != 4)
        return ERR_ARGS;

    if (strcmp(argv[3], "s") == 0)
        *swap = ROWS;
    else if (strcmp(argv[3], "c") == 0)
        *swap = COLS;
    else
        return ERR_ARGS;

    return OK;
}
