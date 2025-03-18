#!/bin/bash

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

# Проверка на существование файла с исходным кодом
if [ ! -f "$dir/main.c" ]; then
    echo "No file main.c in script directory!"
    exit 2
fi

# Компиляция программы с ключами сборки для работы с утилитой gcov
if ! gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -O0 -g --coverage -c -o "$dir/main.o" "$dir/main.c"
then
    exit 1
fi

# Компоновка исполняемого файла в случае успешной компиляции
gcc --coverage -o "$dir/app.exe" "$dir/main.o" -lm
