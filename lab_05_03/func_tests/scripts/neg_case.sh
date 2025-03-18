#!/bin/bash

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
if [ $# -lt 2 ]; then
    echo "Usage: ./func_tests/scripts/neg_case.sh file_stream_in file_args"
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

# Импорт в случае необходимости
if [ "${args[0]}" = "p" ] || [ "${args[0]}" = "s" ]; then
    if ! ./app.exe import "$1" "${args[1]}" > /dev/null; then
        exit 0
    fi
fi

# Проверка кода возврата программы при переданном вводе аргументов командной строки
if ./app.exe "${args[@]}" < "$1" > /dev/null; then
    exit 1
fi
exit 0
