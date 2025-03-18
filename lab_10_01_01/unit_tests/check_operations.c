#include <stdlib.h>

#include "operations.h"
#include "list.h"
#include "check_operations.h"


// Функция создания списка с заданным содержимым
node_t *create_list_int(int arr[], int len)
{
    node_t *head = NULL;
    node_t *end = NULL;
    for (int i = 0; i < len; i++)
    {
        push_end(&end, &arr[i]);
        if (i == 0)
            head = end;
    }
    return head;
}

// Функция проверки равенства списков
void assert_list_eq(node_t *in1, node_t *in2, int (*comparator)(const void *, const void *))
{
    while (in1 != NULL && in2 != NULL)
    {
        ck_assert_int_eq(comparator(in1->data, in2->data), 0);
        in1 = in1->next;
        in2 = in2->next;
    }
    ck_assert_ptr_null(in1);
    ck_assert_ptr_null(in2);
}

// Компаратор целых чисел
int compare_int(const void *in1, const void *in2)
{
    const int *num_1 = in1;
    const int *num_2 = in2;
    return *num_1 - *num_2;
}

// Функция освобождения списка без динамических полей
void free_int_list(node_t *head)
{
    node_t *temp;
    while (head != NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
}

// Пустой список
START_TEST(find_empty)
{
    int tmp = 3;
    node_t *found;
    node_t *head = NULL;

    found = find(head, &tmp, compare_int);
    ck_assert_ptr_null(found);
}
END_TEST

// Указатель на NULL вместо компаратора
START_TEST(find_null_comparator)
{
    int tmp = 3;
    node_t *found;
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    found = find(head, &tmp, NULL);
    ck_assert_ptr_null(found);
    free_int_list(head);
}
END_TEST

// Нет искомого элемента
START_TEST(find_no_elem)
{
    int tmp = 4;
    node_t *found;
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    found = find(head, &tmp, compare_int);
    ck_assert_ptr_null(found);
    free_int_list(head);
}
END_TEST


// Список из одного элемента
START_TEST(find_one_elem)
{
    int tmp = 2;
    node_t *found;
    int arr[] = { 2 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    found = find(head, &tmp, compare_int);
    ck_assert_ptr_eq(found, head);
    free_int_list(head);
}
END_TEST

// Искомый элемент в начале
START_TEST(find_at_head)
{
    int tmp = 2;
    node_t *found;
    int arr[] = { 2, 4, 7, -6 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    found = find(head, &tmp, compare_int);
    ck_assert_ptr_eq(found, head);
    free_int_list(head);
}
END_TEST

// Искомый элемент в конце
START_TEST(find_at_tail)
{
    int tmp = -6;
    node_t *found;
    int arr[] = { 2, 4, 7, -6 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    found = find(head, &tmp, compare_int);
    ck_assert_ptr_eq(found, head->next->next->next);
    free_int_list(head);
}
END_TEST

// Искомый элемент в середине
START_TEST(find_in_middle)
{
    int tmp = 7;
    node_t *found;
    int arr[] = { 2, 4, 7, -6, 8 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    found = find(head, &tmp, compare_int);
    ck_assert_ptr_eq(found, head->next->next);
    free_int_list(head);
}
END_TEST

// Несколько искомых элементов
START_TEST(find_same_elems)
{
    int tmp = 7;
    node_t *found;
    int arr[] = { 2, 4, 7, -6, 8, 7, 2, 7 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    found = find(head, &tmp, compare_int);
    ck_assert_ptr_eq(found, head->next->next);
    free_int_list(head);
}
END_TEST

// Функция объединения тестов поиска в набор
Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("find");

    tc_neg = tcase_create("negatives");
    // Пустой список
    tcase_add_test(tc_neg, find_empty);
    // Указатель на NULL вместо компаратора
    tcase_add_test(tc_neg, find_null_comparator);
    // Нет искомого элемента
    tcase_add_test(tc_neg, find_no_elem);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Список из одного элемента
    tcase_add_test(tc_pos, find_one_elem);
    // Искомый элемент в начале
    tcase_add_test(tc_pos, find_at_head);
    // Искомый элемент в конце
    tcase_add_test(tc_pos, find_at_tail);
    // Искомый элемент в середине
    tcase_add_test(tc_pos, find_in_middle);
    // Несколько искомых элементов
    tcase_add_test(tc_pos, find_same_elems);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Пустой список
START_TEST(pop_front_empty)
{
    void *popped;
    node_t *head = NULL;

    popped = pop_front(&head);
    ck_assert_ptr_null(popped);
}
END_TEST

// Указатель на NULL вместо списка
START_TEST(pop_front_nullptr)
{
    void *popped;

    popped = pop_front(NULL);
    ck_assert_ptr_null(popped);
}
END_TEST


// Список из одного элемента
START_TEST(pop_front_one_elem)
{
    void *popped;
    int arr[] = { 2 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    popped = pop_front(&head);
    ck_assert_ptr_eq(popped, &arr[0]);
    ck_assert_ptr_null(head);
    free_int_list(head);
}
END_TEST

// Список из нескольких элементов
START_TEST(pop_front_many_elem)
{
    void *popped;
    node_t *next;
    int arr[] = { 2 , 4, 6};
    node_t *head = create_list_int(arr, ARR_LEN(arr));

    next = head->next;
    popped = pop_front(&head);
    ck_assert_ptr_eq(popped, &arr[0]);
    ck_assert_ptr_eq(head, next);
    free_int_list(head);
}
END_TEST

// Функция объединения тестов удаления элемента из начала в набор
Suite *pop_front_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("pop_front");

    tc_neg = tcase_create("negatives");
    // Пустой список
    tcase_add_test(tc_neg, pop_front_empty);
    // Указатель на NULL вместо списка
    tcase_add_test(tc_neg, pop_front_nullptr);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Список из одного элемента
    tcase_add_test(tc_pos, pop_front_one_elem);
    // Список из нескольких элементов
    tcase_add_test(tc_pos, pop_front_many_elem);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Пустой список
START_TEST(reverse_empty)
{
    node_t *reversed;
    node_t *head = NULL;

    reversed = reverse(head);
    ck_assert_ptr_null(reversed);
}
END_TEST


// Список из одного элемента
START_TEST(reverse_one_elem)
{
    int arr[] = { 2 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *reversed = create_list_int(arr, ARR_LEN(arr));

    head = reverse(head);
    assert_list_eq(head, reversed, compare_int);
    free_int_list(head);
    free_int_list(reversed);
}
END_TEST

// Список из нескольких элементов
START_TEST(reverse_many_elem)
{
    int arr[] = { 2 , 3, 7, -4 };
    int arr_reversed[] = { -4, 7, 3, 2 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *reversed = create_list_int(arr_reversed, ARR_LEN(arr_reversed));

    head = reverse(head);
    assert_list_eq(head, reversed, compare_int);
    free_int_list(head);
    free_int_list(reversed);
}
END_TEST

// Список из одинаковых элементов
START_TEST(reverse_same_elem)
{
    int arr[] = { 3 , 3, 3, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *reversed = create_list_int(arr, ARR_LEN(arr));

    head = reverse(head);
    assert_list_eq(head, reversed, compare_int);
    free_int_list(head);
    free_int_list(reversed);
}
END_TEST

// Функция объединения тестов разворота в набор
Suite *reverse_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("reverse");

    tc_neg = tcase_create("negatives");
    // Пустой список
    tcase_add_test(tc_neg, reverse_empty);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Список из одного элемента
    tcase_add_test(tc_pos, reverse_one_elem);
    // Список из нескольких элементов
    tcase_add_test(tc_pos, reverse_many_elem);
    // Список из одинаковых элементов
    tcase_add_test(tc_pos, reverse_same_elem);
    suite_add_tcase(s, tc_pos);

    return s;
}
