#!/bin/bash

# Скрипт для полной проверки папки проекта
# Поддерживает ключ -v

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

# Проверка скриптов
if ! "$dir"/check_scripts.sh; then
    echo "Failed script check!"
    exit 1
fi
echo "Passed script check"

# Проверка существования файла исходного кода
if [ ! -f "$dir/main.c" ]; then
    echo "No file main.c in script directory!"
    exit 2
fi

# Проверка стиля кода
for file in "$dir"/*.c; do
    if ! CodeChecker.exe "$file"; then
        echo "Failed codestyle check!"
        exit 3
    fi
done
echo "Passed codestyle check"

# Очистка побочных файлов
"$dir/clean.sh"

# Функциональное тестирование с помощью сборок без санитайзеров
for build in build_debug.sh build_release.sh
do
    if [ ! -f "$dir/$build" ]; then
        echo "No default build scripts!"
        exit 4
    fi
    # Проверка сборки
    echo "Checking $build"
    if ! "$dir/$build"; then
        echo "Failed build with $build"
        exit 5
    fi
    # Проведение функционального тестирования
    if ! "$dir/func_tests/scripts/func_tests.sh" "$1"
    then 
        echo "Failed func testing with $build"
        exit 6
    fi
done

# Проверка сборок с санитайзерами
if ! "$dir/check_sanitizers.sh" "$1"; then
    exit 7
fi

# Проверка покрытия тестами
echo "Checking collect_coverage.sh"
if ! "$dir/collect_coverage.sh" "$1"; then
    exit 8
fi

# Очистка побочных файлов
"$dir/clean.sh"

echo FULL OK
