#include <stdio.h>
#include "io.h"
#include "errors.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int rc;
    char string[STR_LEN+1];
    char words[STR_LEN / 2][WORD_LEN + 1];
    size_t num_of_each_word[STR_LEN / 2];
    size_t words_num;

    rc = input_string(string);
    if (process_error(rc) != OK)
        return rc;

    rc = split_string(string, words, &words_num);
    if (process_error(rc) != OK)
        return rc;

    words_num = count_and_del_dup_words(words, num_of_each_word, words_num);
    
    printf("Result: ");
    print_word_num_pairs(words, num_of_each_word, words_num);

    return OK;
}
