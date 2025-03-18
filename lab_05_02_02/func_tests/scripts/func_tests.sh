#!/bin/bash

# Поддерживает ключ -v
# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")/../..

# Проверка на существование исполняемого файла
if [ ! -f "$dir"/app.exe ]; then
    echo No file app.exe in project directory!
    exit 100
fi

# Обработка ключа -v
if [ "$1" = "-v" ]; then
    verbose=1
fi

total=0
fails=0

# Проверка позитивных случаев
for file_in in "$dir"/func_tests/data/pos_*_in.txt; do
    if [ ! -f "$file_in" ]; then
        if [ "$verbose" ]; then
            echo No pos_in files!
        fi
        break
    fi

    file_out=${file_in/%in.txt/out.txt}
    file_args=${file_in/%in.txt/args.txt}
    short_name="$(basename "$file_in")"
    # Проверка на существование соответствующего выходного файла
    if [ ! -f "$file_out" ]; then
        echo "No pos_out file for $short_name!"
        continue
    fi
    # Проверка на существование соответствующего файла c аргументами
    if [ ! -f "$file_args" ]; then
        echo "No pos_args file for $short_name!"
        continue
    fi
    short_name=${short_name#pos_}
    short_name=${short_name%_in.txt}

    total=$((total + 1))
    # Проверка позитивного тестового случая
    if "$dir"/func_tests/scripts/pos_case.sh "$file_in" "$file_out" "$file_args"
    then
        if [ "$verbose" ]; then
            echo "Pos test $short_name OK"
        fi
    else
        fails=$((fails + 1))
        if [ "$verbose" ]; then
            echo "Pos test $short_name FAIL!"
        fi
    fi
done

# Проверка негативных случаев
for file_in in "$dir"/func_tests/data/neg_*_in.txt; do
    if [ ! -f "$file_in" ]; then
        if [ "$verbose" ]; then
            echo No neg_in files!
        fi
        break
    fi
    file_args=${file_in/%in.txt/args.txt}
    short_name="$(basename "$file_in")"
    # Проверка на существование соответствующего файла c аргументами
    if [ ! -f "$file_args" ]; then
        echo "No neg_args file for $short_name!"
        continue
    fi
    short_name=${short_name#neg_}
    short_name=${short_name%_in.txt}

    total=$((total + 1))
    # Проверка негативного тестового случая
    if "$dir"/func_tests/scripts/neg_case.sh "$file_in" "$file_args"
    then
        if [ "$verbose" ]; then
            echo "Neg test $short_name OK"
        fi
    else
        fails=$((fails + 1))
        if [ "$verbose" ]; then
            echo "Neg test $short_name FAIL!"
        fi
    fi
done

echo "$fails out of $total tests failed"

# Возврат количества проваленных тестов
exit $fails
