#!/bin/bash

# Скрипт проверки покрытия функциональными тестами
# Ожидает покрытие минимум 70 процентов

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")
cd "$dir" || exit 99

make -s clean

# Сборка программы
if ! make -s cov; then
    echo "Failed build with make coverage"
    exit 1
fi

# Проведение функционального тестирования
if ! "./func_tests/scripts/func_tests.sh" > /dev/null
then 
    echo "Failed func testing with coverage"
    exit 1
fi

# Проверка результатов
result=$(cd ./out && gcov -s "$dir"/src ./*.o | grep -E "^(Lines)|(File)")

echo "$result" | head -n -1

result=$(echo "$result" | tail -n 1 | grep -Eo -m 1 "[0-9]+\.[0-9]+%")
echo "Full coverage: $result"

# Проверка покрытия на то, больше ли оно 70 процентов
result="${result%%.*}"
if [ "$result" -lt 70 ]; then
    exit 1
fi
exit 0
