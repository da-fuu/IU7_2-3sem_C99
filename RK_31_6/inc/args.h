#ifndef ARGS_H__
#define ARGS_H__


typedef enum
{
    ROWS,
    COLS
} swap_t;

// Чтение аргументов командной строки
// Принимает кол-во аргументов, массив указателей на них
// Изменяет по указателю направление перемещений в матрице
// Возвращает код ошибки
int process_args(int argc, char **argv, swap_t *swap);

#endif // #ifndef ARGS_H__
