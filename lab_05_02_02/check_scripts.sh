#!/bin/bash

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

failed=0
# Проверка всех скриптов в папке с помощью утилиты shellcheck
for file in "$dir"/*.sh "$dir"/func_tests/scripts/*.sh; do
    if [ ! -f "$file" ]; then
        continue
    fi
    if ! shellcheck "$file"; then
        failed=$((failed + 1))
    fi
done

exit "$failed"
