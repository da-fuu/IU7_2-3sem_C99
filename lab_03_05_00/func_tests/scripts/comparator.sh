#!/bin/bash

# Проверка количества аргументов
if [ $# -lt 2 ]; then
    echo "Usage: ./func_tests/scripts/comparator.sh file_in_1 file_in_2"
    exit 2
fi

# Проверка первого аргумента
if [ ! -f "$1" ] && [ ! -L "$1" ]; then
    echo "First arg must be valid file!"
    exit 2
fi

# Проверка второго аргумента
if [ ! -f "$2" ] && [ ! -L "$2" ]; then
    echo "Second arg must be valid file!"
    exit 2
fi

# Функция для выделения последовательности целых чисел
function get_program_out {
	# Построчное чтение файла
	while read -r line; do
		# Разбиение на слова
		for word in $line; do
			# Вывод удовлетворяющего числа
			if [[ $word =~ ^[+-]?[0-9]+$ ]]
			then
				echo "$word"
			fi
		done
	done < "$1"
}

# Сравнение искомых последовательностей чисел
if ! diff -q <(get_program_out "$1") <(get_program_out "$2") > /dev/null
then
	exit 1
fi
exit 0
