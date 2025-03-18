#ifndef ERRORS_H__

#define ERRORS_H__

// Заголовочный файл файла для обработки ошибок


#define OK 0
#define ERR_ARGS 1
#define ERR_IMPORT 2
#define ERR_EXPORT 3
#define ERR_CREATE_ARGS 4
#define ERR_PRINT_ARGS 5
#define ERR_SORT_ARGS 6
#define ERR_FILE_ACCESS 7
#define ERR_FILE_READ 8

// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости 
// изменить код ошибки)
int process_error(int err_code);


#endif	// #ifndef ERRORS_H__
