# Тесты для лабораторной работы No03_02
## Входные данные
1. Целые положительные rows и columns - размерности матрицы от 1 до 10
2. {rows*columns} целых чисел - элементов матрицы matrix
3. Целая положительная цифра digit
## Выходные данные
1. Исходная матрица с вставленными строками из чисел 100
## Позитивные тесты
1. Ввод целевой цифры равной 0
2. Ввод целевой цифры равной 9
3. Все строки в матрице состоят из элементов, не начинающихся на целевую цифру
4. Все строки в матрице состоят из элементов, не заканчивающихся на целевую цифру
5. Все строки в матрице состоят из элементов, не начинающихся и не заканчивающихся на целевую цифру
6. Матрица размером 10х10 со всеми удовлетворяющими условию строками
7. Матрица размером 10х1 со всеми удовлетворяющими условию строками
8. Матрица размером 1х10
9. Матрица размером 1х1
10. Матрица с произвольными не удовлетворяющими условию строками
11. Матрица с произвольными строками из тестов 3-6, 10 (в том числе из отрицателных элементов)
## Негативные тесты
1. Ввод количества строк меньше 1
2. Ввод количества столбцев меньше 1
3. Ввод буквы вместо количества строк
4. Ввод буквы вместо количества столбцов
5. Ввод количества строк больше 10
6. Ввод количества столбцев больше 10
7. Попытка ввести не целое число вместо количества строк
8. Попытка ввести не целое число вместо количества столбцов
9. Ввод буквы вместо элемента матрицы
10. Попытка ввести не целый элемент матрицы
11. Ввод буквы вместо целевой цифры
12. Ввод целевой цифры как вещественное без целой части
13. Ввод целевой цифры меньше 0
14. Ввод целевой цифры больше 9
