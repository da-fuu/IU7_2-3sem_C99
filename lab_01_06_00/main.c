#include <stdio.h>
#include <math.h>

// Точность сравнения чисел с ЧПТ
#define EPS 0.000001

// Функция вычисления вещественного расстояния между 2 точками с вещественными координатами (x1, y1) и (x2, y2)
double compute_dist(double x1, double y1, double x2, double y2)
{
    double dist;
    dist = hypot(fabs(x1 - x2), fabs(y1 - y2));
    return dist;
}

// Функция поиска максимального вещественного значения из трех вещественных a, b, c
double get_max(double a, double b, double c)
{
    return fmax(fmax(a, b), c);
}

// Функция поиска минимального вещественного значения из трех вещественных a, b, c
double get_min(double a, double b, double c)
{
    return fmin(fmin(a, b), c);
}

// Основная функция программы
int main(void)
{
    double xa, ya, xb, yb, xc, yc;
    double ab_dist, bc_dist, ac_dist;
    double hyp_sqr, sqr_sum, max_dist, min_dist, mid_dist;
    int result = -1;

    // Блок ввода
    printf("Введите координаты вершин треугольника:\n");
    if (scanf("%lf%lf%lf%lf%lf%lf", &xa, &ya, &xb, &yb, &xc, &yc) != 6)
    {
        printf("Нужно ввести шесть чисел-координат вершин треугольника!\n");
        return -1;
    }

    // Вычисление расстояний и их сортировка
    ab_dist = compute_dist(xa, ya, xb, yb);
    bc_dist = compute_dist(xc, yc, xb, yb);
    ac_dist = compute_dist(xa, ya, xc, yc);
    max_dist = get_max(ab_dist, bc_dist, ac_dist);
    min_dist = get_min(ab_dist, ac_dist, bc_dist);
    mid_dist = ac_dist + ab_dist + bc_dist - min_dist - max_dist;
    // Проверка на вырожденность
    if ((min_dist + mid_dist - max_dist) < EPS)
    {
        printf("Треугольник вырожденный!\n");
        return -2;
    }
    // Расчет квадрата "гипотенузы" и суммы квадратов "катетов"
    sqr_sum = mid_dist * mid_dist + min_dist * min_dist;
    hyp_sqr = max_dist * max_dist;
    // Определение типа треугольника
    if (fabs(sqr_sum - hyp_sqr) < EPS)
        result = 1;
    else if (sqr_sum < hyp_sqr)
        result = 2;
    else
        result = 0;

    // Блок вывода
    printf("Результат: %d \n", result);
    return 0;
}
