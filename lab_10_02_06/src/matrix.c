#include <stdlib.h>

#include "list.h"
#include "matrix.h"
#include "errors.h"


// Функция сложения 2 матриц, входные матрицы опустошаются
node_t *add_matrices(node_t **head_a, node_t **head_b)
{
    node_t *new_head = NULL;
    node_t *end;
    node_t *cur;
    node_t *temp;
    int diff;

    if (head_a == NULL || head_b == NULL)
        return NULL;

    while (*head_a != NULL && *head_b != NULL)
    {
        diff = compare_elems(&(*head_a)->data, &(*head_b)->data);
        if (diff < 0)
        {
            cur = *head_a;
            *head_a = (*head_a)->next;
            cur->next = NULL;
        }
        else if (diff > 0)
        {
            cur = *head_b;
            *head_b = (*head_b)->next;
            cur->next = NULL;
        }
        else
        {
            (*head_a)->data.val += (*head_b)->data.val;
            if ((*head_a)->data.val != 0)
            {
                cur = *head_a;
                *head_a = (*head_a)->next;
                cur->next = NULL;
            }
            else
            {
                cur = NULL;
                temp = *head_a;
                *head_a = (*head_a)->next;
                free(temp);
            }

            temp = *head_b;
            *head_b = (*head_b)->next;
            free(temp);
            if (cur == NULL)
                continue;
        }
        if (new_head == NULL)
        {
            new_head = cur;
            end = cur;
        }
        else
        {
            end->next = cur;
            end = end->next;
        }
    }

    if (*head_a != NULL)
    {
        if (new_head == NULL)
            new_head = *head_a;
        else
            end->next = *head_a;
        *head_a = NULL;
    }
    else if (*head_b != NULL)
    {
        if (new_head == NULL)
            new_head = *head_b;
        else
            end->next = *head_b;
        *head_b = NULL;
    }

    return new_head;
}

// Функция умножения 2 матриц, входные матрицы не опустошаются
int mul_matrices(node_t *head_a, node_t *head_b, node_t **out_head)
{
    node_t *head_b_tmp;
    node_t *cur_row_head = NULL;
    node_t *cur_row_end = NULL;
    data_t cur_data;
    int cur_row;
    node_t *sum_row_head = NULL;

    if (out_head == NULL)
        return ERR_UNIT_FAIL;
    *out_head = NULL;

    while (head_a != NULL && head_b != NULL)
    {
        head_b_tmp = head_b;
        cur_row = head_a->data.row;
        while (head_a != NULL && head_a->data.row == cur_row && head_b_tmp != NULL)
        {
            while (head_b_tmp != NULL && head_b_tmp->data.row < head_a->data.col)
                head_b_tmp = head_b_tmp->next;

            while (head_b_tmp != NULL && head_b_tmp->data.row == head_a->data.col)
            {
                cur_data.val = head_a->data.val * head_b_tmp->data.val;
                cur_data.row = cur_row;
                cur_data.col = head_b_tmp->data.col;
                if (push_end(&cur_row_head, &cur_row_end, &cur_data) != OK)
                {
                    free_list(cur_row_head);
                    free_list(sum_row_head);
                    free_list(*out_head);
                    return ERR_NO_MEMORY;
                }
                head_b_tmp = head_b_tmp->next;
            }

            sum_row_head = add_matrices(&sum_row_head, &cur_row_head);

            head_a = head_a->next;
        }
        link_lists(out_head, &sum_row_head);
    }
    return OK;
}

// Функция удаления строки из матрицы
node_t *del_row(node_t *head, int row)
{
    node_t *new_head = NULL;
    node_t *cur_end = NULL;
    node_t *temp;

    while (head != NULL)
    {
        if (head->data.row != row)
        {
            if (cur_end == NULL)
            {
                new_head = head;
                cur_end = head;
            }
            else
            {
                cur_end->next = head;
                cur_end = cur_end->next;
            }
            head = head->next;
            cur_end->next = NULL;
        }
        else
        {
            temp = head;
            head = head->next;
            free(temp);
        }
    }
    return new_head;
}

// Функция поиска максимального элемента в матрице
data_t *find_max_elem(node_t *head)
{
    int n_max = 0;
    data_t *cur = NULL;
    while (head != NULL)
    {
        if (cur == NULL || head->data.val > cur->val)
        {
            n_max = 1;
            cur = &head->data;
        }
        else if (head->data.val == cur->val)
        {
            n_max++;
        }
        head = head->next;
    }
    if (n_max > 1)
        return NULL;
    return cur;
}

// Функция удаления из матрицы строки с максимальным элементом
int remove_row_with_max(node_t **head)
{
    data_t *max_el;
    if (head == NULL || *head == NULL)
        return ERR_UNIT_FAIL;

    max_el = find_max_elem(*head);
    if (max_el == NULL)
        return ERR_MANY_MAX;
    *head = del_row(*head, max_el->row);
    return OK;
}
