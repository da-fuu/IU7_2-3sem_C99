# Тесты для лабораторной работы No04_03
## Входные данные
1. Строка не больше 256 символов, (включая символ новой строки), содержащая как минимум одно слово, слова имеют макс длину в 16 символов
## Выходные данные
1. Cтрока из слов, отличных от последнего, взятых в обратном порядке из массива, с оставленным первым вхождением первой буквы
## Позитивные тесты
1. Строка из 256 символов
2. Строка из слов по 16 символов
3. Строка из двух разных слов из 1 символа
4. Строка со словами из одной и и той же буквы
5. Ни одно слово строки не совпадает с последним, но некоторые из обработанных слов совпадают с ним
6. Строка начинается и заканчивается разделителями
7. Строка начинается и заканчивается символами-не-разделителями
## Негативные тесты
1. Пустой файл
2. Пустой текстовый файл(один символ переноса строки)
3. Строка из разделителей
4. Корректная строчка является второй в файле
5. Строка из 257 символов
6. Строка с словом из 17 символов
7. Результирующая строка пустая
