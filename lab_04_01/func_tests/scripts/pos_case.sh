#!/bin/bash

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")/../..

# Проверка на существование исполняемого файла
if [ ! -f "$dir"/app.exe ]; then
    echo "No file app.exe in project directory!"
    exit 2
fi

# Проверка количества аргументов
if [ $# -lt 2 ]; then
    echo "Usage: ./func_tests/scripts/pos_case.sh file_stream_in file_stream_out_expect"
    exit 2
fi

# Проверка первого аргумента
if [ ! -f "$1" ] && [ ! -L "$1" ]; then
    echo "First param must be valid file!"
    exit 2
fi

# Проверка второго аргумента
if [ ! -f "$2" ] && [ ! -L "$2" ]; then
    echo "Second param must be valid file!"
    exit 2
fi

if ! "$dir"/app.exe < "$1" > /dev/null; then
    exit 1
fi

# Проверка компаратором вывода программы и целевого вывода
if ! "$dir"/func_tests/scripts/comparator.sh <("$dir"/app.exe < "$1") "$2"
then
    exit 1
fi
exit 0
