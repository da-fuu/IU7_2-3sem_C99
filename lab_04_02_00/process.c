#include <stdbool.h>
#include <string.h>
#include "process.h"
#include "errors.h"


// Функция проверки символа на то, является ли он разделителем
// Принимает символ, возвращает результат проверки
bool is_separator(const char chr)
{
    char separators[] = ",;:-.!?\n ";
    for (size_t i = 0; i < sizeof(separators); i++)
    {
        if (chr == separators[i])
            return true;
    }
    return false;
}

// Функция для разбиения строки на слова
// Принимает строку, принимает и изменяет по указателю массив слов и его длину
// Возвращает код ошибки
int split_string(const char string[], char words[][WORD_LEN + 1], size_t *words_num_out)
{
    size_t words_num = 0;
    size_t curr_word_pos = 0;
    bool is_word = false;
    do
    {
        if (is_separator(*string))
        {
            if (!is_word)
                continue;
            is_word = false;
            words[words_num - 1][curr_word_pos] = '\0';
            curr_word_pos = 0;
            continue;
        }
        if (!is_word)
        {
            is_word = true;
            words_num++;
        }
        if (curr_word_pos >= WORD_LEN)
            return ERR_WORD_TOO_LONG;
        words[words_num - 1][curr_word_pos++] = *string;
    }
    while (*string++);
    
    if (words_num == 0)
        return ERR_NO_WORDS;
    *words_num_out = words_num;

    return OK;
}

// Функция для удаления слова из массива слов
// Принимает массив слов, его длину, индекс слова для удаления
void del_word(char words[][WORD_LEN + 1], size_t words_num, size_t index)
{
    for (size_t i = index; i < words_num - 1; i++)
        strncpy(words[i], words[i + 1], WORD_LEN + 1);
}

// Функция подсчета частоты встречи слов в массиве и удаления дублей
// Принимает начальное кол-во слов, принимает и изменяет по указателю массив слов и массив количеств повторений слов
// Возвращает обновленное количество слов
size_t count_and_del_dup_words(char words[][WORD_LEN + 1], size_t num_of_each_word[], size_t words_num)
{
    size_t word_freq;
    for (size_t i = 0; i < words_num; i++)
    {
        word_freq = 1;
        for (size_t j = i + 1; j < words_num; j++)
            if (strncmp(words[i], words[j], WORD_LEN) == 0)
            {
                word_freq++;
                del_word(words, words_num, j);
                words_num--;
                j--;
            }
        num_of_each_word[i] = word_freq;
    }
    return words_num;
}
