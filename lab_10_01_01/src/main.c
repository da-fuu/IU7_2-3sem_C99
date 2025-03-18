#include <stddef.h>

#include "errors.h"
#include "struct.h"
#include "list.h"
#include "file.h"
#include "operations.h"
#include "sort.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    node_t *list;
    student_t *first_student;
    node_t *first_student_in_sorted;

    if (argc != 3)
        return process_error(ERR_CMD_ARGS);

    ret_code = read_students(argv[1], &list);
    if (ret_code != OK)
        return process_error(ret_code);

    first_student = list->data;
    list = sort(list, compare_marks);
    first_student_in_sorted = find(list, first_student, compare_marks);
    free_list(first_student_in_sorted->next);
    first_student_in_sorted->next = NULL;
    list = reverse(list);
    free_student(pop_front(&list));
    if (list == NULL)
        return process_error(ERR_EMPTY_OUT);
    ret_code = write_students(list, argv[2]);
    free_list(list);

    return process_error(ret_code);
}
