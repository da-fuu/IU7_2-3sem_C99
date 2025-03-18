#include <stdio.h>
#include <stdbool.h>

#define INPUT_ERROR 2
#define OK 0
#define MAX_LEN 10

// Функция ввода массива, принимает указатель на первый и на запоследний элемент
bool input_arr(int *p_start, const int *p_stop)
{
    while (p_start < p_stop)
    {
        if (scanf("%d", p_start++) != 1)
        {
            return false;
        }
    }
    return true;
}

// Функция поиска элемента с индексом m в массиве по условию
// Принимает указатель на первый и на запоследний элемент
// Возвращает указатель на искомый элемент(первый отрицательный или последний в массиве)
int *find_stop_term(int *p_start, const int *p_stop)
{
    while (p_start < p_stop)
    {
        if (*p_start < 0)
            return p_start;
        p_start++;
    }
    return (int*)p_stop - 1;
}

// Функция поиска факториальной суммы, принимает указатель на первый и на запоследний элемент
// Возвращает искомое значение факториальной суммы
int find_fact_sum(int *p_start, const int *p_stop)
{
    int sum = 0;
    int last_term = 1;
    const int *stop_term_ptr = find_stop_term(p_start, p_stop);
    while (p_start <= stop_term_ptr)
    {
        last_term *= *p_start;
        sum += last_term;
        p_start++;
    }
    return sum;
}

// Основная функция программы
int main(void)
{
    int array[MAX_LEN];
    int *p_start = array;
    int *p_stop; 
    size_t tmp_len;
    int sum;

    printf("Введите длину массива до десяти:\n");
    if (scanf("%zu", &tmp_len) != 1 || tmp_len > MAX_LEN || tmp_len == 0)
    {
        printf("Длина должна быть целым положительным числом меньше десяти!\n");
        return INPUT_ERROR;
    }
    p_stop = p_start + tmp_len;

    printf("Введите элементы массива: \n");
    if (!input_arr(p_start, p_stop))
    {
        printf("Массив целых чисел введен некорректно!\n");
        return INPUT_ERROR;
    }

    sum = find_fact_sum(p_start, p_stop);
    printf("Искомая факториальная сумма: %d \n", sum);
    return OK;
}
