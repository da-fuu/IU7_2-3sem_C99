#ifndef ERRORS_H__
#define ERRORS_H__

// Заголовочный файл файла для обработки ошибок


#define OK 0
#define ERR_ARGS 1
#define ERR_FILE_STRUCT 2
#define ERR_FILE_DIMENSIONS 3
#define ERR_FILE_IN_ACCESS 4
#define ERR_NO_MEMORY 5
#define ERR_FILE_OUT_ACCESS 6
#define ERR_DIMENSIONS_ADD 7
#define ERR_DIMENSIONS_MULTIPLY 8
#define ERR_DIMENSIONS_SOLVE 9
#define ERR_SOLVE 10
#define ERR_UNIT_FAIL 11


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code);


#endif	// #ifndef ERRORS_H__
