#include "sort.h"
#include "check_operations.h"
#include "check_sort.h"


// Указатель на NULL вместо выходного списка
START_TEST(front_back_split_nullptr_back)
{
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *initial = create_list_int(arr, ARR_LEN(arr));

    front_back_split(head, NULL);
    assert_list_eq(head, initial, compare_int);

    free_int_list(head);
    free_int_list(initial);
}
END_TEST

// Пустой входной список
START_TEST(front_back_split_empty)
{
    node_t *back;
    node_t *head = NULL;

    front_back_split(head, &back);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(back);
}
END_TEST


// Входной список из 1 элемента
START_TEST(front_back_split_one_elem)
{
    int arr[] = { 2 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *head_res = create_list_int(arr, ARR_LEN(arr));
    node_t *back;

    front_back_split(head, &back);
    assert_list_eq(head, head_res, compare_int);
    ck_assert_ptr_null(back);

    free_int_list(head);
    free_int_list(head_res);
}
END_TEST

// Входной список из нечетного количества элементов
START_TEST(front_back_split_even)
{
    int arr[] = { 2, 3, 5, -5 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *head_res = create_list_int(arr, 2);
    node_t *back;
    node_t *back_res = create_list_int(arr + 2, 2);

    front_back_split(head, &back);
    assert_list_eq(head, head_res, compare_int);
    assert_list_eq(back, back_res, compare_int);

    free_int_list(head);
    free_int_list(head_res);
    free_int_list(back);
    free_int_list(back_res);
}
END_TEST

// Входной список из четного количества элементов
START_TEST(front_back_split_odd)
{
    int arr[] = { 2, 3, 5, -5, 0 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *head_res = create_list_int(arr, 3);
    node_t *back;
    node_t *back_res = create_list_int(arr + 3, 2);

    front_back_split(head, &back);
    assert_list_eq(head, head_res, compare_int);
    assert_list_eq(back, back_res, compare_int);

    free_int_list(head);
    free_int_list(head_res);
    free_int_list(back);
    free_int_list(back_res);
}
END_TEST

// Функция объединения тестов разбиения в набор
Suite *front_back_split_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("front_back_split");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо выходного списка
    tcase_add_test(tc_neg, front_back_split_nullptr_back);
    // Пустой входной список
    tcase_add_test(tc_neg, front_back_split_empty);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Входной список из 1 элемента
    tcase_add_test(tc_pos, front_back_split_one_elem);
    // Входной список из нечетного количества элементов
    tcase_add_test(tc_pos, front_back_split_even);
    // Входной список из четного количества элементов
    tcase_add_test(tc_pos, front_back_split_odd);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Указатель на NULL вместо списка 1
START_TEST(sorted_merge_nullptr_head_1)
{
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *initial = create_list_int(arr, ARR_LEN(arr));
    node_t *sorted;

    sorted = sorted_merge(NULL, &head, compare_int);
    ck_assert_ptr_null(sorted);
    assert_list_eq(head, initial, compare_int);

    free_int_list(head);
    free_int_list(initial);
}
END_TEST

// Указатель на NULL вместо списка 2
START_TEST(sorted_merge_nullptr_head_2)
{
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *initial = create_list_int(arr, ARR_LEN(arr));
    node_t *sorted;

    sorted = sorted_merge(&head, NULL, compare_int);
    ck_assert_ptr_null(sorted);
    assert_list_eq(head, initial, compare_int);

    free_int_list(head);
    free_int_list(initial);
}
END_TEST

// Указатель на NULL вместо функции компаратора
START_TEST(sorted_merge_nullptr_comparator)
{
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *initial = create_list_int(arr, ARR_LEN(arr));
    int arr_2[] = { -1, 100 };
    node_t *head_2 = create_list_int(arr_2, ARR_LEN(arr_2));
    node_t *initial_2 = create_list_int(arr_2, ARR_LEN(arr_2));
    node_t *sorted;

    sorted = sorted_merge(&head, &head_2, NULL);
    ck_assert_ptr_null(sorted);
    assert_list_eq(head, initial, compare_int);
    assert_list_eq(head_2, initial_2, compare_int);

    free_int_list(head);
    free_int_list(initial);
    free_int_list(head_2);
    free_int_list(initial_2);
}
END_TEST

// Оба списка пустые
START_TEST(sorted_merge_both_empty)
{
    node_t *head = NULL;
    node_t *head_2 = NULL;
    node_t *sorted;

    sorted = sorted_merge(&head, &head_2, compare_int);
    ck_assert_ptr_null(sorted);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(head_2);
}
END_TEST


// Список 1 пустой
START_TEST(sorted_merge_head_1_empty)
{
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *head_2 = NULL;
    node_t *sorted;
    node_t *out = create_list_int(arr, ARR_LEN(arr));

    sorted = sorted_merge(&head, &head_2, compare_int);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(head_2);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Список 2 пустой
START_TEST(sorted_merge_head_2_empty)
{
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *head_2 = NULL;
    node_t *sorted;
    node_t *out = create_list_int(arr, ARR_LEN(arr));

    sorted = sorted_merge(&head_2, &head, compare_int);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(head_2);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Все элементы списка 1 меньше всех элементов списка 2
START_TEST(sorted_merge_entire_head_1_less_than_2)
{
    int arr[] = { 2, 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    int arr_2[] = { 6, 13 };
    node_t *head_2 = create_list_int(arr_2, ARR_LEN(arr_2));
    node_t *sorted;
    int ans[] = { 2, 3, 6, 13 };
    node_t *out = create_list_int(ans, ARR_LEN(ans));

    sorted = sorted_merge(&head, &head_2, compare_int);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(head_2);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Список 1 из одного элемента
START_TEST(sorted_merge_head_1_one_elem)
{
    int arr[] = { 3 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    int arr_2[] = { -6, 13 };
    node_t *head_2 = create_list_int(arr_2, ARR_LEN(arr_2));
    node_t *sorted;
    int ans[] = { -6, 3, 13 };
    node_t *out = create_list_int(ans, ARR_LEN(ans));

    sorted = sorted_merge(&head, &head_2, compare_int);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(head_2);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Список 2 из одного элемента
START_TEST(sorted_merge_head_2_one_elem)
{
    int arr[] = { 30 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    int arr_2[] = { -6, 13 };
    node_t *head_2 = create_list_int(arr_2, ARR_LEN(arr_2));
    node_t *sorted;
    int ans[] = { -6, 13, 30 };
    node_t *out = create_list_int(ans, ARR_LEN(ans));

    sorted = sorted_merge(&head_2, &head, compare_int);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(head_2);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Список 1 из четных элементов, 2 из нечетных
START_TEST(sorted_merge_head_1_even_head_2_odd)
{
    int arr[] = { -2, 0, 6, 60 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    int arr_2[] = { -7, -1, 5, 33 };
    node_t *head_2 = create_list_int(arr_2, ARR_LEN(arr_2));
    node_t *sorted;
    int ans[] = { -7, -2, -1, 0, 5, 6, 33, 60 };
    node_t *out = create_list_int(ans, ARR_LEN(ans));

    sorted = sorted_merge(&head_2, &head, compare_int);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(head_2);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Функция объединения тестов слияния в набор
Suite *sorted_merge_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("sorted_merge");

    tc_neg = tcase_create("negatives");
    // Указатель на NULL вместо списка 1
    tcase_add_test(tc_neg, sorted_merge_nullptr_head_1);
    // Указатель на NULL вместо списка 2
    tcase_add_test(tc_neg, sorted_merge_nullptr_head_2);
    // Указатель на NULL вместо функции компаратора
    tcase_add_test(tc_neg, sorted_merge_nullptr_comparator);
    // Оба списка пустые
    tcase_add_test(tc_neg, sorted_merge_both_empty);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Список 1 пустой
    tcase_add_test(tc_pos, sorted_merge_head_1_empty);
    // Список 2 пустой
    tcase_add_test(tc_pos, sorted_merge_head_2_empty);
    // Все элементы списка 1 меньше всех элементов списка 2
    tcase_add_test(tc_pos, sorted_merge_entire_head_1_less_than_2);
    // Список 1 из одного элемента
    tcase_add_test(tc_pos, sorted_merge_head_1_one_elem);
    // Список 2 из одного элемента
    tcase_add_test(tc_pos, sorted_merge_head_2_one_elem);
    // Список 1 из четных элементов, 2 из нечетных
    tcase_add_test(tc_pos, sorted_merge_head_1_even_head_2_odd);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Сортировка пустого списка
START_TEST(sort_empty)
{
    node_t *head = NULL;
    node_t *sorted;

    sorted = sort(head, compare_int);
    ck_assert_ptr_null(sorted);
}
END_TEST

// Указатель на NULL вместо списка
START_TEST(sort_nullptr_comparator)
{
    int arr[] = { 2, -5 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *sorted;

    sorted = sort(head, NULL);
    ck_assert_ptr_null(sorted);

    free_int_list(head);
}
END_TEST


// Список из одного элемента
START_TEST(sort_one_elem)
{
    int arr[] = { 2 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *sorted;
    node_t *out = create_list_int(arr, ARR_LEN(arr));

    sorted = sort(head, compare_int);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Сортированный список
START_TEST(sort_sorted)
{
    int arr[] = { 2, 5, 8, 111 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *sorted;
    node_t *out = create_list_int(arr, ARR_LEN(arr));

    sorted = sort(head, compare_int);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Сортированный в обратном порядке список
START_TEST(sort_reversed)
{
    int arr[] = { -2, -5, -8, -111 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *sorted;
    int arr_2[] = { -111, -8, -5, -2 };
    node_t *out = create_list_int(arr_2, ARR_LEN(arr_2));

    sorted = sort(head, compare_int);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Перемешанный список
START_TEST(sort_random)
{
    int arr[] = { 2, -5, 10, -8, -111 };
    node_t *head = create_list_int(arr, ARR_LEN(arr));
    node_t *sorted;
    int arr_2[] = { -111, -8, -5, 2, 10 };
    node_t *out = create_list_int(arr_2, ARR_LEN(arr_2));

    sorted = sort(head, compare_int);
    assert_list_eq(sorted, out, compare_int);

    free_int_list(sorted);
    free_int_list(out);
}
END_TEST

// Функция объединения тестов сортировки в набор
Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("sort");

    tc_neg = tcase_create("negatives");
    // Сортировка пустого списка
    tcase_add_test(tc_neg, sort_empty);
    // Указатель на NULL вместо списка
    tcase_add_test(tc_neg, sort_nullptr_comparator);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Список из одного элемента
    tcase_add_test(tc_pos, sort_one_elem);
    // Сортированный список
    tcase_add_test(tc_pos, sort_sorted);
    // Сортированный в обратном порядке список
    tcase_add_test(tc_pos, sort_reversed);
    // Перемешанный список
    tcase_add_test(tc_pos, sort_random);
    suite_add_tcase(s, tc_pos);

    return s;
}
