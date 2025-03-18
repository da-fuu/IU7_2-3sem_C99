#include <stdio.h>
#include <math.h>

// Расчет вещественного приближенного значения функции e^x с вещественными аргументом x и точностью eps с помощью ряда Маклорена
double compute_func(double x, double eps)
{
    double sum = 1.0, new_val = 1.0;
    unsigned int denom = 1;

    while (fabs(new_val) > eps)
    {
        new_val *= x;
        new_val /= denom;
        denom += 1;
        sum += new_val;
    }

    return sum;
}

// Основная функция программы
int main(void)
{
    double x, eps;
    double acc_val, comp_val, abs_diff, rel_diff;

    // Блок ввода
    printf("Введите число x(аргумент функции) и число eps(погрешность):\n");
    if (scanf("%lf%lf", &x, &eps) != 2)
    {
        printf("Нужно ввести два корректных числа!\n");
        return 1;
    }
    if (!(eps > 0.0) || eps > 1.0)
    {
        printf("eps должен быть в пределах от нуля до единицы!\n");
        return 2;
    }

    // Расчет приближенного, точного значения функции и абсолютной, относительной точности
    comp_val = compute_func(x, eps);
    acc_val = exp(x);
    abs_diff = fabs(comp_val - acc_val);
    rel_diff = abs_diff / fabs(acc_val);

    // Блок вывода
    printf("Вычисленное значение функции: %f \n", comp_val);
    printf("Точное значение функции: %f \n", acc_val);
    printf("Абсолютная погрешность: %f \n", abs_diff);
    printf("Относительная погрешность: %f \n", rel_diff);

    return 0;
}
