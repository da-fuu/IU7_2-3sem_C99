#include <stdio.h>

// Основная функция программы
int main(void)
{
    double height, t_chest, mass, mass_normal, bmi;

    // Блок ввода
    printf("Введите рост в см, обхват грудной клетки в см и массу тела в кг:\n");
    (void)scanf("%lf%lf%lf", &height, &t_chest, &mass);

    // Вычисления параметров
    mass_normal = height * t_chest / 240.0;
    height = height / 100.0;
    bmi = mass / (height * height);

    // Блок вывода
    printf("Нормальный вес: %f \n", mass_normal);
    printf("Индекс массы тела: %f \n", bmi);
    return 0;
}
