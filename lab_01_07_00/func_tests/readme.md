# Тесты для лабораторной работы No01_07
## Входные данные
1. Вещественное x - аргумент функции
2. Вещественное eps - погрешность в промежутке (0, 1]
## Выходные данные
1. Вещественное comp_val - вычисленное значение функции
2. Вещественное acc_val - точное значение функции
3. Вещественное abs_diff - абсолютная погрешность
4. Вещественное rel_diff - относительная погрешность
## Позитивные тесты
1. Положительный х, погрешность 1.0
2. Положительный х, нормальная погрешность(меньше единицы)
3. х = 0, обычная погрешность(меньше единицы)
4. Отрицательный х, обычная погрешность(меньше единицы)
5. х вводится как целое число, погрешность 1
## Негативные тесты
1. eps вне промежутка
2. Вместо первого числа буква
