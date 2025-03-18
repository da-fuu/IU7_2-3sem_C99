#include <stdio.h>
#include <stdbool.h>

#define INPUT_ERROR 2
#define DATA_ERROR 1
#define OK 0
#define MAX_LEN 10

// Функция ввода массива со сдвигом к правому краю, принимает массив и его длину
bool input_arr_with_shift(int arr[], size_t length)
{
    for (size_t i = MAX_LEN - length; i < MAX_LEN; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
            return false;
    }
    return true;
}

// Функция проверки числа на то, является ли оно палиндромом, принимает число, возвращает результат проверки
bool is_palindrome(int num)
{
    int reversed_num = 0;
    int curr_num = num;
    if (num < 0)
        return false;
    while (curr_num > 0)
    {
        reversed_num *= 10;
        reversed_num += curr_num % 10;
        curr_num /= 10;
    }
    return num == reversed_num;
}

// Функция удаления палиндромов из массива, сдвинутого к правому краю, принимает массив и его длину, возвращает новую длину массива
size_t del_pal_from_arr_with_shift(int arr[], size_t len)
{
    size_t new_len = 0;
    for (size_t i = MAX_LEN - len; i < MAX_LEN; i++)
    {
        if (!is_palindrome(arr[i]))
            arr[new_len++] = arr[i];
    }
    return new_len;
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
    size_t length, new_length;

    printf("Введите длину массива до десяти:\n");
    if (scanf("%zu", &length) != 1 || length > MAX_LEN || length == 0)
    {
        printf("Длина должна быть целым положительным числом меньше десяти!\n");
        return INPUT_ERROR;
    }

    printf("Введите элементы массива: \n");
    if (!input_arr_with_shift(array, length))
    {
        printf("Массив целых чисел введен некорректно!\n");
        return INPUT_ERROR;
    }
    /*
    printf("Исходный массив: \n");
    output_array(array, length);
    */
    new_length = del_pal_from_arr_with_shift(array, length);
    if (new_length == 0)
    {
        printf("В массиве нет элементов, не являющихся числами-палиндромами!\n");
        return DATA_ERROR;
    }
    printf("Измененный массив: \n");
    output_array(array, new_length);

    return OK;
}
