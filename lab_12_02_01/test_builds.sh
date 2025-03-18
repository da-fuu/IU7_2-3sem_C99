#!/bin/bash

# Скрипт прогона всех сборок (кроме модульного тестирования)
# Поддерживает ключ -v

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")
cd "$dir" || exit 99

# Функциональное тестирование с помощью всех сборок
for build in stat dyn_link dyn_load
do
    make -s clean
    # Сборка
    echo "Checking $build"
    if ! make -s "$build"; then
        echo "Failed build with make $build"
        exit 2
    fi
    
    # Проведение функционального тестирования
    if ! ./func_tests/scripts/func_tests.sh "$1"
    then 
        echo "Failed func testing with $build"
        exit 1
    fi

    echo "Checking valgrind $build"
    if ! ./func_tests/scripts/func_tests.sh "$1" "-m"
    then
        echo "Failed func testing with valgrind $build"
        exit 1
    fi
    
    if ! ./unit_tests.exe; then
        echo "Failed unit testing with $build"
        exit 1
    fi
    if ! valgrind -q --error-exitcode=1 --leak-check=yes ./unit_tests.exe; then
        echo "Failed unit testing with valgrind $build"
        exit 1
    fi
done
