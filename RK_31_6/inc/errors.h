#ifndef ERRORS_H__
#define ERRORS_H__


#define OK 0
#define ERR_ARGS 1
#define ERR_FILE_IN 2
#define ERR_FILE_EMPTY 3
#define ERR_FILE_DIMENSIONS 4
#define ERR_FILE_STRUCT 5
#define ERR_FILE_OUT 6
#define ERR_NO_MEMORY 7


int process_error(int err_code);

#endif // #ifndef ERRORS_H__
