#ifndef IO_H__
#define IO_H__


#define STR_LEN 100

#define OK 0
#define FILE_ERROR 1

int input_filename(char string[]);
void print_words(char words[][STR_LEN + 1], size_t len);


#endif
