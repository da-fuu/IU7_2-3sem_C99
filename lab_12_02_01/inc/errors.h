#ifndef ERRORS_H__
#define ERRORS_H__

// Заголовочный файл файла для обработки ошибок


#define OK 0
#define ERR_ARGS 1
#define ERR_FILE_STRUCT 2
#define ERR_FILE_EMPTY 3
#define ERR_FILE_IN_ACCESS 4
#define ERR_NO_MEMORY 5
#define ERR_EMPTY_OUT 6
#define ERR_FILE_OUT_ACCESS 7
#define ERR_NULLPTR 8
#define ERR_INVALID_ARR 9
#define ERR_UNIT_FAIL 10
#define ERR_LIB_OPEN 11
#define ERR_FUNC_LOAD 12

// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code);


#endif	// #ifndef ERRORS_H__
