#!/bin/bash

# Поддерживает ключ -v
# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

# Проверка на существование файла с исходным кодом
if [ ! -f "$dir/main.c" ]; then
    echo "No file main.c in script directory!"
    exit 2
fi

# Функциональное тестирование с помощью всех сборок
for build in "$dir"/build_debug_*san.sh 
do
    if [ ! -f "$build" ]; then
        echo No sanitizers build scripts!
        exit 2
    fi
    # Сборка
    short_name="$(basename "$build")"
    echo "Checking $short_name"
    if ! "$build"; then
        echo "Failed build with $short_name"
        exit 1
    fi
    # Проведение функционального тестирования
    if ! "$dir/func_tests/scripts/func_tests.sh" "$1"
    then 
        echo "Failed func testing with $short_name"
        exit 1
    fi
done
