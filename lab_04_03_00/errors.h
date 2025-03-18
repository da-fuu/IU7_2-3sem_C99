#ifndef ERRORS_H__

#define ERRORS_H__

// Заголовочный файл файла для обработки ошибок

#define OK 0
#define ERR_INPUT 1
#define ERR_STR_TOO_LONG 2
#define ERR_WORD_TOO_LONG 3
#define ERR_NO_WORDS 4
#define ERR_EMPTY_OUT_STR 5


// Функция обработки кода ошибки и печати соответствующего сообщения
// Принимает и возвращает код ошибки (позволяет при необходимости реализовать
// предупреждения - обработать ошибку, но не прекратить выполнение main)
int process_error(int err_code);


#endif	// #ifndef ERRORS_H__
