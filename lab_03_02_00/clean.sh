#!/bin/bash

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")

# Удаление исполняемых и других побочных файлов
for file in "$dir"/*.exe "$dir"/*.o "$dir"/*.gcov "$dir"/*.gcda "$dir"/*.gcno
do
    if [ -f "$file" ]; then
        rm "$file"
    fi
done
