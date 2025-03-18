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
if [ $# -lt 3 ]; then
    echo "Usage: ./func_tests/scripts/pos_case.sh file_stream_in file_stream_out_expect file_args"
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

# Проверка третьего аргумента
if [ ! -f "$3" ] && [ ! -L "$3" ]; then
    echo "Third param must be valid file!"
    exit 2
fi

# Чтение файла с аргументами командной строки
read -r -a args < "$3"

# Получение вывода программы
if ! ./app.exe "${args[@]}" > ./out.tmp; then
    exit 1
fi

# Проверка компаратором вывода программы и целевого вывода
if ! ./func_tests/scripts/comparator.sh ./out.tmp "$2"
then
    exit 1
fi
exit 0
