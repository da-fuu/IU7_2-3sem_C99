#ifndef MATRIX_H__
#define MATRIX_H__

// Заголовочный файл файла для работы с матрицами

#include "struct.h"


// Функция сложения 2 матриц, входные матрицы опустошаются
node_t *add_matrices(node_t **head_a, node_t **head_b);

// Функция умножения 2 матриц, входные матрицы не опустошаются
int mul_matrices(node_t *head_a, node_t *head_b, node_t **out_head);

// Функция удаления из матрицы строки с максимальным элементом
int remove_row_with_max(node_t **head);


#endif // #ifndef MATRIX_H__
