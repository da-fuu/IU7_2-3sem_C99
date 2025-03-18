#include <stdio.h>
#include <stdlib.h>

#define NEW_COST 45
#define RETURN_COST 20

// Основная функция программы
int main(void)
{
    int money, bottles;

    // Блок ввода
    printf("Введите количество копеек:\n");
    scanf("%d", &money);

    // Вычисление по формуле
    bottles = abs(money - RETURN_COST) / (NEW_COST - RETURN_COST);

    // Блок вывода
    printf("Количество бутылок: %d \n", bottles);
    return 0;
}
