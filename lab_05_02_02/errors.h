#ifndef ERRORS_H__

#define ERRORS_H__

// Заголовочный файл файла для обработки ошибок


#define OK 0
#define ERR_INPUT 1
#define ERR_FILE 2
#define ERR_ARGS 3
#define ERR_FILE_CONTENT 4

// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code);


#endif	// #ifndef ERRORS_H__
