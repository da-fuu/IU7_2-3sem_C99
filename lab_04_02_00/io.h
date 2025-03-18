#ifndef IO_H__

#define IO_H__

// Заголовочный файл файла для работы с вводом-выводом

#define STR_LEN 256
#define WORD_LEN 16


// Функция ввода строки - возвращает код ошибки и изменяет по указателю строку
int input_string(char string[]);

// Функция печати пар (слово число)
// Принимает массивы слов и чисел по указателю и количество пар
void print_word_num_pairs(char words[][WORD_LEN + 1], const size_t numbers[], size_t len);


#endif	// #ifndef IO_H__
