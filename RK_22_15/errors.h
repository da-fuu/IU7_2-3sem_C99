#ifndef ERRORS_H__
#define ERRORS_H__

#define STR_LEN 100

#define OK 0
#define FILE_ERROR 1
#define ERR_INPUT_FILENAME 2
#define ERR_TOO_LONG_FILENAME 3
#define ERR_NO_WORDS 4
#define ERR_EMPTY_OUT_STR 5
#define ERR_TOO_LONG_STR 6

void process_error(int rc);

#endif



