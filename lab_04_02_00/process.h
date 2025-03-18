#ifndef PROCESS_H__

#define PROCESS_H__

// Заголовочный файл файла для выполнения основного задания (работы со строками)

#include <stddef.h>
#include "io.h"


// Функция для разбиения строки на слова
// Принимает строку, принимает и изменяет по указателю массив слов и его длину
// Возвращает код ошибки
int split_string(const char string[], char words[][WORD_LEN + 1], size_t *words_num);

// Функция подсчета частоты встречи слов в массиве и удаления дублей
// Принимает начальное кол-во слов, принимает и изменяет по указателю массив слов и массив количеств повторений слов
// Возвращает обновленное количество слов
size_t count_and_del_dup_words(char words[][WORD_LEN + 1], size_t num_of_each_word[], size_t words_num);


#endif	// #ifndef PROCESS_H__
