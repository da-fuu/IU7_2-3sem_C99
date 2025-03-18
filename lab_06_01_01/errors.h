#ifndef ERRORS_H__

#define ERRORS_H__

// Заголовочный файл файла для обработки ошибок


#define OK 0
#define ERR_ARGS 1
#define ERR_FILE_STRUCT 2
#define ERR_FIND_ARG 4
#define ERR_FILE_ACCESS 5
#define ERR_FILE_TOO_LONG 6
#define ERR_EMPTY_FILE 7


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code);


#endif	// #ifndef ERRORS_H__
