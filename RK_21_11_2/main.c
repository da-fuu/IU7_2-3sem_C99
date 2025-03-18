#include <stdio.h>
#include <stdbool.h>

#define INPUT_ERROR 1
#define OK 0
#define MAX_LEN 10

// Функция ввода массива, принимает массив и длину
bool input_array(int array[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (scanf("%d", &array[i]) != 1)
            return false;
    }
    return true;
}

// Функция вывода массива, принимает массив и длину
void output_array(int array[], size_t len)
{   
    for (size_t i = 0; i < len; i++)
        printf("%d ", array[i]);
    
    printf("\n");
}

// Функция вставки элемента по индексу, принимает массив, его длину, значение для вставки и его индекс
// Возвращает новую длину
size_t insert_elem(int array[], size_t len, int value, size_t index)
{
    for (size_t i = len; i > index; i--)
    {
        array[i] = array[i - 1];
    }
    array[index] = value;

    return len + 1;
}

// Функция вставки максимального элемента после каждого четного элемента
// Принимает массив и его длину, возвращает новую длину
size_t insert_maxes_after_evens(int array[], size_t len)
{
    size_t new_len = len;
    int running_max;
    int shift;

    if (array[0] % 2 == 0)
        running_max = 0;
    else
        running_max = array[0];

    for (size_t i = 0; i < new_len; i++)
    {
        shift = 0;
        if (array[i] % 2 == 0)
        {
            new_len = insert_elem(array, new_len, running_max, i + 1);
            shift = 1;
        }
        if (array[i] > running_max)
            running_max = array[i];
        i += shift;
    }

    return new_len;
}

// Основная функция программы
int main(void)
{
    int array[MAX_LEN*2];
    size_t length;

    printf("Введите длину массива от одного до десяти:\n");
    if (scanf("%zu", &length) != 1 || length == 0 || length > MAX_LEN)
    {
        printf("Длина должна быть целым положительным числом меньше десяти!\n");
        return INPUT_ERROR;
    }

    printf("Введите элементы массива:\n");
    if (!input_array(array, length))
    {
        printf("Массив целых чисел введен некорректно!\n");
        return INPUT_ERROR;
    }

    length = insert_maxes_after_evens(array, length);

    printf("Измененный массив: \n");
    output_array(array, length);

    return OK;
}
