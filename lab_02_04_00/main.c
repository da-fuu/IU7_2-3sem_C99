#include <stdio.h>

#define INPUT_ERROR 2
#define OK 0
#define MAX_LEN 10
#define OVERFLOW 100

// Функция ввода массива по концевому условию, принимает массив, возвращает его длину
size_t input_arr(int arr[])
{   
    int tmp;
    for (size_t length = 0; length < MAX_LEN; length++)
    {
        if (scanf("%d", &arr[length]) != 1)
            return length;
    }

    if (scanf("%d", &tmp) != 1)
    {
        return MAX_LEN;
    } 
    return OVERFLOW;   
}

// Функция сортировки массива, принимает массив и его длину
void sort_array(int arr[], size_t len)
{
    int tmp;
    for (size_t i = 0; i < len - 1; i++)
    {
        for (size_t j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// Функция вывода массива, принимает массив и его длину
void output_array(int arr[], size_t len)
{   
    for (size_t i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Основная функция программы
int main(void)
{
    int array[MAX_LEN];
    size_t length;
    int ret_code = OK;

    printf("Введите элементы массива по концевому условию: \n");
    length = input_arr(array);
    if (length == 0)
    {
        printf("Массив целых чисел не может быть пустым!\n");
        return INPUT_ERROR;
    }
    if (length == OVERFLOW)
    {
        ret_code = OVERFLOW;
        length = MAX_LEN;
    }

    /*
    printf("Исходный массив: \n");
    output_array(array, length);
    */
    sort_array(array, length);

    printf("Измененный массив: \n");
    output_array(array, length);

    return ret_code;
}
