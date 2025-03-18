#ifndef MY_SNPRINTF_H__
#define MY_SNPRINTF_H__

#include <stddef.h>

#define ERROR (-1)

// Аналог функции snprintf для спецификаторов ho и s, обрабатывает спецификатор полностью, в соответствии со стандартом С99 
int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...);


#endif // #ifndef MY_SNPRINTF_H__
