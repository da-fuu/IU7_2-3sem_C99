#!/bin/bash

# Скрипт для полной проверки папки проекта
# Поддерживает ключ -v

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")
cd "$dir" || exit 99

# Проверка стиля кода
for file in ./src/*.c ./lib/*.c; do
    if ! CodeChecker.exe "$file"; then
        echo "Failed codestyle check!"
        exit 4
    fi
done
echo "Passed codestyle check"

# Очистка побочных файлов
make -s clean

# Проверка сборок
if ! ./test_builds.sh "$1"; then
    exit 1
fi

# Очистка побочных файлов
make -s clean

echo -e "\n\t\033[1;92m FULL OK \033[0m\n"
exit 0
