#!/bin/bash

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(readlink -f "$(dirname "$(readlink -f "$0")")/../..")

# Проверка на существование исполняемого файла
if [ ! -f "$dir/app.exe" ]; then
    echo "No file app.exe in project directory!"
    exit 2
fi

# Проверка количества аргументов
if [ $# -lt 1 ]; then
    echo "Usage: ./func_tests/scripts/neg_case.sh file_stream_in"
    exit 2
fi

# Проверка первого аргумента
if [ ! -f "$1" ] && [ ! -L "$1" ]; then
    echo "First param must be valid file!"
    exit 2
fi

# Проверка кода возврата программы при переданном вводе
if "$dir/app.exe" < "$1" > /dev/null; then
    exit 1
fi
exit 0
