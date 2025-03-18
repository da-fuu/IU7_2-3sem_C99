#include <stdio.h>
#include <math.h>

// Функция для обновления подкоренной суммы
// Вещественные sum, x, denom - текущие сумма, аргумент и знаменатель
// Вещественный результат - обновленная сумма
double upd_sum(double sum, double x, double denom)
{
    return sum + x / denom;
}

// Основная функция программы
int main(void)
{
    double sum = 0, res, x = 0;
    int scanf_res;
    unsigned int denom = 1;

    // Блок ввода
    printf("Введите элементы последовательности чисел(отрицательное число завершает ввод):\n");
    scanf_res = scanf("%lf", &x);
    // Проверка на ввод отрицательного числа первым
    if (x < 0 && scanf_res == 1)
    {
        printf("Последовательность должна быть непустой!\n");
        return 1;
    }
    // Цикл жо первого отрицательного элемента
    while (!(x < 0))
    {
        // Остановка и выход с ошибкой при вводе не-числа
        if (scanf_res != 1)
        {
            printf("Введено не число!\n");
            return 2;
        }
        // Обновление суммы и знаменателя
        sum = upd_sum(sum, x, denom);
        denom++;
        // Считывание нового элемента
        scanf_res = scanf("%lf", &x);
    }
    // Вычисление корня суммы
    res = sqrt(sum);

    // Блок вывода
    printf("Значение функции: %f \n", res);
    return 0;
}
