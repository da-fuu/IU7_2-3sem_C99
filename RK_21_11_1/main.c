#include <stdio.h>

#define INPUT_ERROR 1
#define OK 0

// Заменить в числе все нечетные цифры на 2
long long replace_odd_digits(long long number)
{
    long long new_number = 0, shifter = 1;
    int digit;
    
    while (number)
    {
        digit = number % 10;

        if (digit % 2 != 0)
            digit = 2;

        new_number += digit * shifter;

        shifter *= 10;
        number /= 10;
    }

    return new_number;
}

// Основная функция программы
int main(void)
{
    long long number;

    printf("Введите натуральное число: ");
    if (scanf("%lld", &number) != 1)
    {
        printf("Нужно ввести одно целое положительное(натуральное) число!\n");
        return INPUT_ERROR;
    }
 
    if (number <= 0)
    {
        printf("Число должно быть целым положительным(натуральным)!\n");
        return INPUT_ERROR;
    }

    number = replace_odd_digits(number);

    printf("Измененное число: %lld \n", number);
    return OK;
}
