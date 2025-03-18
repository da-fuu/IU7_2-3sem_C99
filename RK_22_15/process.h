#include <stdio.h>
#include "errors.h"

#ifndef PROCESS_H__
#define PROCESS_H__

int get_words(FILE *file, char words[][STR_LEN + 1], size_t *words_num);
int del_words_same_as_max(char words[][STR_LEN + 1], size_t *words_num);
void del_chars(char words[][STR_LEN + 1], size_t words_num);


#endif



