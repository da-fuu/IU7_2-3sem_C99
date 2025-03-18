#include "struct.h"
#include "array.h"
#include "errors.h"
#include "check_array.h"


// Функция проверки равенства массивов
void assert_arrays_eq(struct film_s *film_1, int len_1, struct film_s *film_2, int len_2)
{
    ck_assert(len_1 == len_2);
    for (int i = 0; i < len_1; i++)
    {
        ck_assert_str_eq(film_1[i].title, film_2[i].title);
        ck_assert_str_eq(film_1[i].name, film_2[i].name);
        ck_assert_int_eq(film_1[i].year, film_2[i].year);
    }
}


// Вставка в пустой массив
START_TEST(insert_empty_arr)
{
    struct film_s films_arr[1];
    int arr_len = 0;
    enum field_e field = TITLE;
    struct film_s film;
    film.title = "Saw";
    film.name = "Van";
    film.year = 1000;
    struct film_s films_arr_target[1];
    films_arr_target[0] = film;

    insert_film_in_arr(&film, field, films_arr, arr_len++);

    assert_arrays_eq(films_arr, arr_len, films_arr_target, 1);
}
END_TEST

// Вставка в конец массива по названию
START_TEST(insert_end_title)
{
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    int arr_len = 2;
    enum field_e field = TITLE;
    struct film_s film;
    film.title = "Saw";
    film.name = "Van";
    film.year = 1000;
    struct film_s films_arr_target[3];
    films_arr_target[0] = films_arr[0];
    films_arr_target[1] = films_arr[1];
    films_arr_target[2] = film;

    insert_film_in_arr(&film, field, films_arr, arr_len++);

    assert_arrays_eq(films_arr, arr_len, films_arr_target, 3);
}
END_TEST

// Вставка в начало массива по имени
START_TEST(insert_start_name)
{
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    int arr_len = 2;
    enum field_e field = NAME;
    struct film_s film;
    film.title = "Saw";
    film.name = "Aan";
    film.year = 1000;
    struct film_s films_arr_target[3];
    films_arr_target[0] = film;
    films_arr_target[1] = films_arr[0];
    films_arr_target[2] = films_arr[1];

    insert_film_in_arr(&film, field, films_arr, arr_len++);

    assert_arrays_eq(films_arr, arr_len, films_arr_target, 3);
}
END_TEST

// Вставка в середину массива по году
START_TEST(insert_middle_year)
{
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    int arr_len = 2;
    enum field_e field = YEAR;
    struct film_s film;
    film.title = "Saw";
    film.name = "Aan";
    film.year = 1100;
    struct film_s films_arr_target[3];
    films_arr_target[0] = films_arr[0];
    films_arr_target[1] = film;
    films_arr_target[2] = films_arr[1];

    insert_film_in_arr(&film, field, films_arr, arr_len++);

    assert_arrays_eq(films_arr, arr_len, films_arr_target, 3);
}
END_TEST

// Вставка в массив дубликата по ключу
START_TEST(insert_double_elem)
{
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    int arr_len = 2;
    enum field_e field = NAME;
    struct film_s film;
    film.title = "Saw";
    film.name = "GAaa";
    film.year = 1100;
    struct film_s films_arr_target[3];
    films_arr_target[0] = films_arr[0];
    films_arr_target[1] = film;
    films_arr_target[2] = films_arr[1];

    insert_film_in_arr(&film, field, films_arr, arr_len++);

    assert_arrays_eq(films_arr, arr_len, films_arr_target, 3);
}
END_TEST

// Функция объединения тестов вставки в массив в набор
Suite *insert_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("insert");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, insert_empty_arr);
    tcase_add_test(tc_pos, insert_end_title);
    tcase_add_test(tc_pos, insert_start_name);
    tcase_add_test(tc_pos, insert_middle_year);
    tcase_add_test(tc_pos, insert_double_elem);
    suite_add_tcase(s, tc_pos);

    return s;
}


// Отрицательный год к поиску
START_TEST(find_neg_year)
{
    int rc;
    struct film_s films_arr[2];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    enum field_e field = YEAR;
    char *str = "-123";
    int index;

    rc = find_film(films_arr, 2, field, str, &index);

    ck_assert_int_eq(rc, ERR_FIND_ARG);
}
END_TEST

// Нечисловой год к поиску
START_TEST(find_incorrect_year)
{
    int rc;
    struct film_s films_arr[2];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    enum field_e field = YEAR;
    char *str = "eeee";
    int index;

    rc = find_film(films_arr, 2, field, str, &index);

    ck_assert_int_eq(rc, ERR_FIND_ARG);
}
END_TEST


// Поиск по имени, нужный элемент - первый
START_TEST(find_start_name)
{
    int rc;
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    films_arr[2].title = "Erm";
    films_arr[2].name = "Zov";
    films_arr[2].year = 2000;
    enum field_e field = NAME;
    char *str = "GAaa";
    int index;

    rc = find_film(films_arr, 3, field, str, &index);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(index, 0);
}
END_TEST

// Поиск по году, нужный элемент - в середине
START_TEST(find_middle_year)
{
    int rc;
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    films_arr[2].title = "Erm";
    films_arr[2].name = "Zov";
    films_arr[2].year = 2000;
    enum field_e field = YEAR;
    char *str = "1200";
    int index;

    rc = find_film(films_arr, 3, field, str, &index);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(index, 1);
}
END_TEST

// Поиск по названию, нужный элемент - в конце
START_TEST(find_end_title)
{
    int rc;
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    films_arr[2].title = "Erm";
    films_arr[2].name = "Zov";
    films_arr[2].year = 2000;
    enum field_e field = TITLE;
    char *str = "Erm";
    int index;

    rc = find_film(films_arr, 3, field, str, &index);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(index, 2);
}
END_TEST

// Поиск по названию, нет совпадения
START_TEST(find_no_match)
{
    int rc;
    struct film_s films_arr[3];
    films_arr[0].title = "Aa";
    films_arr[0].name = "GAaa";
    films_arr[0].year = 1000;
    films_arr[1].title = "Bb";
    films_arr[1].name = "Reda";
    films_arr[1].year = 1200;
    films_arr[2].title = "Erm";
    films_arr[2].name = "Zov";
    films_arr[2].year = 2000;
    enum field_e field = NAME;
    char *str = "Red";
    int index;

    rc = find_film(films_arr, 3, field, str, &index);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(index, -1);
}
END_TEST

// Функция объединения тестов поиска в массиве в набор
Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("find");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, find_neg_year);
    tcase_add_test(tc_neg, find_incorrect_year);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, find_start_name);
    tcase_add_test(tc_pos, find_middle_year);
    tcase_add_test(tc_pos, find_end_title);
    tcase_add_test(tc_pos, find_no_match);
    suite_add_tcase(s, tc_pos);

    return s;
}
