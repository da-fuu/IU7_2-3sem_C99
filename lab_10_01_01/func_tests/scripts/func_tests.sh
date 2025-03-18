#!/bin/bash

# Скрипт прогона функциональных тестов
# Поддерживает ключ -v для подробной выдачи и -m для проверки работы с памятью с помощью valgrind

# Нахождение абсолютного пути к скрипту для обеспечения работы при запуске из любой папки
dir=$(dirname "$(readlink -f "$0")")/../..

# Проверка на существование исполняемого файла
if [ ! -f "$dir"/app.exe ]; then
    echo "No file app.exe in project directory!"
    exit 100
fi

if [[ "$1" = "-v" || "$2" = "-v" ]]; then
    verbose=1
fi
if [[ "$1" = "-m" || "$2" = "-m" ]]; then
    valgr="-m"
else
    valgr=
fi


total=0
fails=0

# Проверка позитивных случаев
for file_args in "$dir"/func_tests/data/pos_*_args.txt; do
    if [ ! -f "$file_args" ]; then
        if [ "$verbose" ]; then
            echo "No pos_args files!"
        fi
        break
    fi

    file_out=${file_args/%args.txt/out.txt}
    short_name="$(basename "$file_args")"
    # Проверка на существование соответствующего выходного файла
    if [ ! -f "$file_out" ]; then
        echo "No pos_out file for $short_name!"
        continue
    fi
    short_name=${short_name#pos_}
    short_name=${short_name%_args.txt}

    total=$((total + 1))
    # Проверка позитивного тестового случая
    if "$dir"/func_tests/scripts/pos_case.sh "$file_args" "$file_out" "$file_args" "$valgr"
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
for file_args in "$dir"/func_tests/data/neg_*_args.txt; do
    if [ ! -f "$file_args" ]; then
        if [ "$verbose" ]; then
            echo "No neg_args files!"
        fi
        break
    fi
    short_name="$(basename "$file_args")"
    short_name=${short_name#neg_}
    short_name=${short_name%_args.txt}

    total=$((total + 1))
    # Проверка негативного тестового случая
    if "$dir"/func_tests/scripts/neg_case.sh "$file_args" "$file_args" "$valgr"
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
