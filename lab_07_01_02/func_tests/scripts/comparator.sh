#!/bin/bash

# Скрипт компаратора для целых чисел

# Проверка количества аргументов
if [ $# -lt 2 ]; then
    echo "Usage: ./func_tests/scripts/comparator.sh file_in_1 file_in_2"
    exit 2
fi

# Проверка первого аргумента
if [ ! -f "$1" ] && [ ! -L "$1" ]; then
    echo "First arg must be valid file!"
    exit 2
fi

# Проверка второго аргумента
if [ ! -f "$2" ] && [ ! -L "$2" ]; then
    echo "Second arg must be valid file!"
    exit 2
fi

# Сравнение искомых последовательностей чисел
if ! diff -q "$1" "$2" > /dev/null
then
    exit 1
fi
exit 0
