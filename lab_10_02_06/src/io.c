#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "list.h"
#include "io.h"

#define ARG_LEN 4


// Функция чтения режима работы
int read_mode(mode_t *mode)
{
    char str[ARG_LEN + 1];
    if (fgets(str, ARG_LEN + 1, stdin) == NULL)
        return ERR_ARGS;
    if (strcmp(str, "out\n") == 0)
    {
        *mode = OUT;
        return OK;
    }
    if (strcmp(str, "add\n") == 0)
    {
        *mode = ADD;
        return OK;
    }
    if (strcmp(str, "mul\n") == 0)
    {
        *mode = MUL;
        return OK;
    }
    if (strcmp(str, "lin\n") == 0)
    {
        *mode = LIN;
        return OK;
    }
    return ERR_ARGS;
}

// Функция печати матрицы
int print_matrix(node_t *head)
{
    if (head == NULL)
        return ERR_EMPTY_OUT;
    while (head != NULL)
    {
        printf("%d %d %d ", head->data.row, head->data.col, head->data.val);
        head = head->next;
    }
    printf("\n");
    return OK;
}

// Функция чтения матрицы из потока ввода
int read_matrix(node_t **head)
{
    int rows, cols;
    int tmp;
    node_t *list_end = NULL;
    *head = NULL;
    data_t data;


    if (scanf("%d%d", &rows, &cols) != 2)
        return ERR_DIMENSIONS;

    if (rows < 1 || cols < 1)
        return ERR_DIMENSIONS;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            if (scanf("%d", &tmp) != 1)
            {
                free_list(*head);
                return ERR_INPUT;
            }
            if (tmp != 0)
            {
                data.val = tmp;
                data.row = i;
                data.col = j;
                if (push_end(head, &list_end, &data) != OK)
                {
                    free_list(*head);
                    return ERR_NO_MEMORY;
                }
            }
        }
    return OK;
}
