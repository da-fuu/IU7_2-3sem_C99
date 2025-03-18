#ifndef IO_H__
#define IO_H__

// Заголовочный файл файла для работы с вводом-выводом

#include "struct.h"


// Перечислимый тип для режима работы
typedef enum
{
    OUT,
    ADD,
    MUL,
    LIN
} mode_t;

// Функция чтения режима работы
int read_mode(mode_t *mode);

// Функция печати матрицы
int print_matrix(node_t *head);

// Функция чтения матрицы из потока ввода
int read_matrix(node_t **head);


#endif // #ifndef IO_H__
