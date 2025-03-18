#include "file.h"
#include "errors.h"


// Функция для определения, являются ли два числа разными по знаку
// Возращает 1, если числа разные по знаку, иначе 0
int is_different_sign(int a, int b)
{
    return (int)((a < 0) != (b < 0));
}

// Функция для подсчета количества смен знаков в последовательности чисел файла
// Принимает файловую переменную, изменяет по указателю переменную количества смен знаков
// Возвращает код ошибки
int process(FILE *f, int *changed_times)
{
    int number, last_number;

    if (fscanf(f, "%d", &last_number) != 1)
        return ERR_INPUT;
    if (fscanf(f, "%d", &number) != 1)
        return ERR_ONE_ELEM;
    
    *changed_times = 0;
    do
    {
        *changed_times += is_different_sign(number, last_number);
        last_number = number;
    } while (fscanf(f, "%d", &number) == 1);

    return OK;
}
