#include <stdio.h>
#include <stdbool.h>

#define INPUT_ERROR 2
#define DATA_ERROR 1
#define OK 0
#define MAX_LEN 10

// Функция ввода массива, принимает массив и его длину
bool input_arr(int arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            return false;
        }
    }
    return true;
}

// Функция проверки существования четного элемента в массиве, принимает массив и его длину, возвращает результат проверки
bool have_even(int arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (arr[i] % 2 == 0)
        {
            return true;
        }
    }
    return false; 
}

// Функция подсчета суммы четных элементов массива, принимает массив и его длину, возвращает искомую сумму
int sum_even(int arr[], size_t len)
{
    int sum = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (arr[i] % 2 == 0)
        {
            sum += arr[i];
        }
    }
    return sum;
}

// Основная функция программы
int main(void)
{
    int array[MAX_LEN];
    size_t length;
    int sum;

    printf("Введите длину массива до десяти:\n");
    if (scanf("%zu", &length) != 1 || length > MAX_LEN || length == 0)
    {
        printf("Длина должна быть целым положительным числом меньше десяти!\n");
        return INPUT_ERROR;
    }

    printf("Введите элементы массива: \n");
    if (!input_arr(array, length))
    {
        printf("Массив целых чисел введен некорректно!\n");
        return INPUT_ERROR;
    }

    if (!have_even(array, length))
    {
        printf("В массиве нет четных элементов!\n");
        return DATA_ERROR;
    }
    sum = sum_even(array, length);

    printf("Сумма четных элементов массива: %d \n", sum);
    return OK;
}
