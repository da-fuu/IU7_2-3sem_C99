#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "errors.h"

// Получение слов из файла
int get_words(FILE *file, char words[][STR_LEN + 1], size_t *words_num)
{
    char line[STR_LEN + 1];
    char *word;

    if (fgets(line, STR_LEN + 1, file) == NULL)
        return ERR_NO_WORDS;

    if (line[strlen(line) - 1] != '\n')
        return ERR_TOO_LONG_STR;
    
    word = strtok(line, " \n");
    *words_num = 0;
    if (word == NULL)
        return ERR_NO_WORDS;
    do
    {
        for (size_t i = 0; i < strlen(word); i++)
            if (!islower(word[i]))
                return ERR_INCORRECT_CHARS;
        strncpy(words[(*words_num)++], word, STR_LEN + 1);
    }
    while ((word = strtok(NULL, " \n")) != NULL);
    
    return OK;
}

// Удаление слова по индексу
void del_word(char words[][STR_LEN + 1], size_t words_num, size_t index)
{
    for (size_t i = index; i < words_num - 1; i++)
        strncpy(words[i], words[i + 1], STR_LEN + 1);
}

// Удаление слов таких же как и максимальное
int del_words_same_as_max(char words[][STR_LEN + 1], size_t *words_num)
{
    char max_word[STR_LEN + 1];
    size_t max_len = 0;

    for (size_t i = 0; i < *words_num; i++)
        if (strlen(words[i]) > max_len)
        {
            max_len = strlen(words[i]);
            strncpy(max_word, words[i], STR_LEN + 1);
        }

    for (size_t i = 0; i < *words_num; i++)
        if (strncmp(words[i], max_word, STR_LEN + 1) == 0)
        {
            if (--*words_num == 0)
                return ERR_EMPTY_OUT_STR;
            del_word(words, *words_num, i);
        }
    
    return OK;
}

// Удаление вхождений последней буквы
void del_chars(char words[][STR_LEN + 1], size_t words_num)
{
    char last_chr;
    size_t word_len;
    for (size_t i = 0; i < words_num; i++)
    {
        word_len = strlen(words[i]);
        last_chr = words[i][word_len - 1];
        for (size_t j = 0; j < word_len - 1; j++)
            if (words[i][j] == last_chr)
                for (size_t k = j; k < word_len; k++)
                    words[i][k] = words[i][k + 1];
    }
}
