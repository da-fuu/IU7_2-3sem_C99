#include <stdlib.h>

#include "errors.h"
#include "struct.h"
#include "list.h"


// Функция освобождения студента
void free_student(student_t *student)
{
    free(student->name);
    free(student);
}

// Функция освобождения списка
void free_list(node_t *head)
{
    node_t *temp;
    while (head != NULL)
    {
        free_student(head->data);
        temp = head->next;
        free(head);
        head = temp;
    }
}

// Функция компаратора студентов по оценкам
int compare_marks(const void *student_ptr1, const void *student_ptr2)
{
    const student_t *student_1 = student_ptr1;
    const student_t *student_2 = student_ptr2;
    return student_1->mark - student_2->mark;
}

// Функция вставки элемента в конец списка
int push_end(node_t **end, void *data)
{
    if (*end == NULL)
        *end = malloc(sizeof(node_t));
    else
    {
        (*end)->next = malloc(sizeof(node_t));
        *end = (*end)->next;
    }
    if (*end == NULL)
        return ERR_NO_MEMORY;
    (*end)->data = data;
    (*end)->next = NULL;
    return OK;
}
