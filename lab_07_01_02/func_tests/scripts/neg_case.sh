#!/bin/bash

# Скрипт проверки негативного тестового случая
# Поддерживает ключ -m для проверки работы с памятью с помощью valgrind

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")/../..

# Переход в папку проекта для корректной работы с файлами-аргументами командной строки
cd "$dir" || exit 99

# Проверка на существование исполняемого файла
if [ ! -f ./app.exe ]; then
    echo "No file app.exe in project directory!"
    exit 2
fi

# Проверка количества аргументов
if [[ $# -lt 2 || ( $# == 3 && "$3" != "-m" && "$3" != "" ) ]]; then
    echo "Usage: ./func_tests/scripts/neg_case.sh file_stream_in file_args [-m]"
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

# Чтение файла с аргументами командной строки
read -r -a args < "$2"

# Проверка кода возврата программы при переданном вводе аргументов командной строки
if [[ "$3" != "-m" ]]; then
    if ./app.exe "${args[@]}" < "$1" > /dev/null; then
        exit 1
    fi
else
    if valgrind -q --error-exitcode=1 --leak-check=yes ./app.exe "${args[@]}" < "$1" > /dev/null; then
        exit 1
    fi
fi
exit 0
