#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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
            return false;
    }
    return true;
}

// Функция поиска среднего арифметического элементов массива, принимает массив и его длину, возвращает округленное вниз среднее
int find_int_avg(int arr[], size_t len)
{
    int sum = 0;
    for (size_t i = 0; i < len; i++)
        sum += arr[i];
    
    return (int)floor((double)sum / len);
}

// Функция заполнения нового массива new_arr элементами старого arr длины len, больших целого числа target
// Возвращает длину нового массива
size_t fill_array(int arr[], size_t len, int new_arr[], int target)
{
    size_t new_len = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (arr[i] > target)
            new_arr[new_len++] = arr[i];
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
    int array[MAX_LEN], new_array[MAX_LEN];
    size_t length, new_length;
    int average;

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

    average = find_int_avg(array, length);
    new_length = fill_array(array, length, new_array, average);
    if (new_length == 0)
    {
        printf("В массиве нет элементов больше среднего арифметического!\n");
        return DATA_ERROR;
    }
    
    /*
    printf("Исходный массив: \n");
    output_array(array, length);
    */
    printf("Новый массив: \n");
    output_array(new_array, new_length);

    return OK;
}
