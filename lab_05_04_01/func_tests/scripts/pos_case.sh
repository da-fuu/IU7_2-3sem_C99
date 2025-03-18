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

# Импорт в случае необходимости
if [ "${args[0]}" = "sb" ] || [ "${args[0]}" = "fb" ]; then
    if ! ./app.exe import "$1" "${args[1]}" > /dev/null; then
        exit 1
    fi
fi

# Получение вывода программы в зависимости от ключа
if [ "${args[0]}" = "fb" ]; then
    if ! ./app.exe "${args[@]}" > /dev/null; then
        exit 1
    fi
    # При необходимости экспортирование данных
    if ! ./app.exe export "${args[2]}" ./out.tmp > /dev/null; then
        exit 1
    fi
else
    if ! ./app.exe "${args[@]}" > ./out.tmp; then
        exit 1
    fi
fi

# Проверка компаратором вывода программы и целевого вывода
if ! ./func_tests/scripts/comparator.sh ./out.tmp "$2"
then
    exit 1
fi
exit 0
