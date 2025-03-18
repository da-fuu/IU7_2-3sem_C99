#include <stdio.h>
#include <string.h>
#include "errors.h"

int input_filename(char string[])
{
    size_t str_len;

    if (fgets(string, STR_LEN + 1, stdin) == NULL)
        return ERR_INPUT_FILENAME;

    str_len = strlen(string);
    if (string[str_len - 1] != '\n')
        return ERR_TOO_LONG_FILENAME;
    
    string[--str_len] = '\0';

    if (str_len == 0)
        return ERR_INPUT_FILENAME;

    return OK;
}

void print_words(char words[][STR_LEN + 1], size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%s ", words[i]);
    
    printf("\n");
}

