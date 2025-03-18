#include <stdio.h>
#include <string.h>
#include "io.h"
#include "errors.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int ret_code;
    char string[STR_LEN+1];
    char words[STR_LEN / 2][WORD_LEN + 1];
    size_t words_num;
    char new_str[STR_LEN+1];

    ret_code = input_string(string);
    if (process_error(ret_code) != OK)
        return ret_code;

    ret_code = split_string(string, words, &words_num);
    if (process_error(ret_code) != OK)
        return ret_code;

    ret_code = form_new_string(words, words_num, new_str);
    if (process_error(ret_code) != OK)
        return ret_code;

    printf("Result: %s\n", new_str);
    return OK;
}
