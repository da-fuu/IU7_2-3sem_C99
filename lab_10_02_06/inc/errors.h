#ifndef ERRORS_H__
#define ERRORS_H__

// Заголовочный файл файла для обработки ошибок


#define OK 0
#define ERR_ARGS 1
#define ERR_INPUT 2
#define ERR_DIMENSIONS 3
#define ERR_NO_MEMORY 4
#define ERR_EMPTY_OUT 5
#define ERR_MANY_MAX 6
#define ERR_UNIT_FAIL 7


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code);


#endif	// #ifndef ERRORS_H__
