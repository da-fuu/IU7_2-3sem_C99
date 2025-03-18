#include <stdio.h>

#define NUM_BITS 32

// Функция печати беззнакового 32-битного числа
void print_uint(unsigned int num)
{
    for (int i = NUM_BITS - 1; i >= 0; i--)
    {
        printf("%u", (num >> i) & 1);
    }
    printf(" \n");
}

// Функция циклического сдвига вправо беззнакового 32битного числа number на целое положительное bits битов
unsigned int cycle_right(unsigned int number, int bits)
{
    unsigned int tmp;
    for (int i = 0; i < bits; i++)
    {
        tmp = number & 1;
        number >>= 1;
        number |= tmp << (NUM_BITS - 1);
    }
    return number;
}

// Основная функция программы
int main(void)
{
    unsigned int a;
    int n;

    // Блок ввода
    printf("Введите беззнаковое целое длиной четыре байта и целое неотрицательное число(величину сдвига):\n");
    if (scanf("%u%d", &a, &n) != 2)
    {
        printf("Error: Нужно ввести беззнаковое целое длиной четыре байта и целое неотрицательное число!\n");
        return 1;
    }
    if (n < 0)
    {
        printf("Error: Второе число должно быть целым неотрицательным!");
        return 2;
    }

    // Выполнение сдвига
    a = cycle_right(a, n);

    // Блок вывода
    printf("Result: ");
    print_uint(a);
    return 0;
}
