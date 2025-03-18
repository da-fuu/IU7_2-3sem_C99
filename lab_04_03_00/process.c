#include <stdbool.h>
#include <string.h>
#include "process.h"
#include "errors.h"


// Функция для разбиения строки на слова
// Принимает и изменяет(портит) строку, принимает и изменяет по указателю массив слов и его длину
// Возвращает код ошибки
int split_string(char string[], char words[][WORD_LEN + 1], size_t *words_num)
{
    char *separators = ",;:-.!? \n";
    char *word = strtok(string, separators);
    
    *words_num = 0;
    if (word == NULL)
        return ERR_NO_WORDS;

    do
    {
        if (strlen(word) > WORD_LEN)
            return ERR_WORD_TOO_LONG;
        strncpy(words[(*words_num)++], word, WORD_LEN + 1);
    }
    while ((word = strtok(NULL, separators)) != NULL);
    
    return OK;
}

// Функция удаления из слова всех последующих вхождений первой буквы
// Принимает и изменяет по указателю слово
void del_chrs_same_as_first(char word[])
{
    size_t len;
    for (size_t i = 1; i < (len = strlen(word)); i++)
        if (word[i] == word[0])
        {
            for (size_t j = i; j < len; j++)
                word[j] = word[j + 1];
            i--;
        }
}

// Функция формирования строки из слов, отличных от последнего, взятых в обратном порядке из массива, с оставленным первым вхождением первой буквы
// Принимает принимает по указателю массив слов и его длину и принимает и изменяет по указателю строку
// Возвращает код ошибки
int form_new_string(char words[][WORD_LEN + 1], size_t words_num, char string[])
{
    bool is_empty = true;

    string[0] = '\0';
    for (size_t i = words_num - 1; i > 0; i--)
    {
        if (strncmp(words[i - 1], words[words_num - 1], WORD_LEN) == 0)
            continue;
        if (is_empty)
            is_empty = false;
        else
            strncat(string, " ", 2);

        del_chrs_same_as_first(words[i - 1]);
        strncat(string, words[i - 1], WORD_LEN);
    }

    if (is_empty)
        return ERR_EMPTY_OUT_STR;

    return OK; 
}
