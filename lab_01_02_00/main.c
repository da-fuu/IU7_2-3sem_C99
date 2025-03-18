#include <stdio.h>
#include <math.h>

// Основная функция программы
int main(void)
{
    double a, b, h, p;

    // Блок вычислений
    printf("Введите длины двух оснований и высоты:\n");
    (void)scanf("%lf%lf%lf", &a, &b, &h);

    // Вычисление периметра трапеции по формуле
    p = a + b + 2 * (sqrt(pow(fabs(a - b) / 2.0, 2) + h * h));

    // Блок вывода
    printf("Периметр: %f \n", p);
    return 0;
}
