#!/bin/bash

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
if ! "$dir/func_tests/scripts/func_tests.sh" > /dev/null
then 
    echo "Failed func testing with build_debug_cov.sh"
    exit 1
fi

# Проверка результатов
result=$(cd "$dir" && gcov "$dir"/*.c | grep -E "^(Lines)|(File)")

echo "$result" | head -n -1

result=$(echo "$result" | tail -n 1 | grep -Eo -m 1 "[0-9]+\.[0-9]+%")
echo "Full coverage: $result"

# Проверка покрытия на то, больше ли оно 70 процентов
result="${result%%.*}"
if [ "$result" -lt 70 ]; then
    exit 1
fi
