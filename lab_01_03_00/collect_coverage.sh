#!/bin/bash

# Поддерживает ключ -v
# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

# Проверка на существование файла с исходным кодом
if [ ! -f "$dir/main.c" ]; then
    echo "No file main.c in script directory!"
    exit 2
fi

# Проверка на существование файла с исходным кодом
if [ ! -f "$dir/build_debug_cov.sh" ]; then
    echo "No build script for gcov in script directory!"
    exit 2
fi

# Сборка программы
if ! "$dir/build_debug_cov.sh"; then
    echo "Failed build with build_debug_cov.sh"
    exit 1
fi

# Проведение функционального тестирования
if ! "$dir/func_tests/scripts/func_tests.sh" "$1"
then 
    echo "Failed func testing with build_debug_cov.sh"
    exit 1
fi

# Проверка результатов
result=$(cd "$dir" && gcov "$dir/main.c" | grep -Eo -m 1 "[0-9]+\.[0-9]+%")
echo "Coverage: $result"
if [ ! "$result" = "100.00%" ]; then
    exit 1
fi
exit 0
