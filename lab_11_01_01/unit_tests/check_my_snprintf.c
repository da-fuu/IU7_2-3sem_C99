#include <stdio.h>

#include "check_obfuscation.h"
#include "my_snprintf.h"
#include "check_my_snprintf.h"

#define LEN 100


START_TEST(all_nullptr)
{
    const char *format = ret_char_p("%s%ho");
    int size = ret_size(0);
    
    int len_1 = snprintf(ret_char_p(NULL), size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(ret_char_p(NULL), size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
}
END_TEST

START_TEST(all_equal)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s%ho");
    int size = ret_size(17);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_equal_add_sym)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s%hoqwert");
    int size = ret_size(25);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_less_cutoff_sym)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%ho%sertyuiohugfdgdfghiljkojlhk");
    int size = ret_size(30);
    
    int len_1 = snprintf(buf_1, size, format, 10, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, 10, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_less_cutoff_s)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%ho%s");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 10, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, 10, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_less_cutoff_ho)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s%ho");
    int size = ret_size(14);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_no_spec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("xgdfchjv");
    int size = ret_size(14);
    
    int len_1 = snprintf(buf_1, size, format);
    int len_2 = my_snprintf(buf_2, size, format);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_width_star)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%*s%*ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, 20, "Hello, world!", 5, 10);
    int len_2 = my_snprintf(buf_2, size, format, 20, "Hello, world!", 5, 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_width_star_neg)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%*s%*ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, -20, "Hello, world!", -5, 10);
    int len_2 = my_snprintf(buf_2, size, format, -20, "Hello, world!", -5, 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_prec_star)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%.*s%.*ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, 7, "Hello, world!", 5, 10);
    int len_2 = my_snprintf(buf_2, size, format, 7, "Hello, world!", 5, 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_prec_star_neg)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%.*s%.*ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, -7, "Hello, world!", -5, 10);
    int len_2 = my_snprintf(buf_2, size, format, -7, "Hello, world!", -5, 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_all_star)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%*.*s%*.*ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, 10, 7, "Hello, world!", 7, 5, 10);
    int len_2 = my_snprintf(buf_2, size, format, 10, 7, "Hello, world!", 7, 5, 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_many_flags)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%--   -- --s%00+++++0###000ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_only_dot_prec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%.s%.ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_only_minus_zero)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%-0s%0-ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_only_plus_space)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%+ s% +ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_many_spec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s%ho%ho%s%ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10, 123, "bye\n", 0);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10, 123, "bye\n", 0);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_excess_args)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s%ho");
    int size = ret_size(50);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10, 123, "bye\n", 0);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10, 123, "bye\n", 0);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(all_size_zero)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s%ho");
    int size = ret_size(0);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!", 10);
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!", 10);
    ck_assert_int_eq(len_1, len_2);
}
END_TEST

START_TEST(all_less_cutoff_ho_end)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s%ho");
    int size = ret_size(2);

    int len_1 = snprintf(buf_1, size, format, "H", 1);
    int len_2 = my_snprintf(buf_2, size, format, "H", 1);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST



START_TEST(s_equal)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s");
    int size = ret_size(14);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_equal_add_sym)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("qwe%sewq");
    int size = ret_size(20);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_less_cutoff_width)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%-20s");
    int size = ret_size(20);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_less_cutoff_padded)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%20s");
    int size = ret_size(20);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_less_cutoff_sym)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%sqwertyhgf");
    int size = ret_size(15);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_less_cutoff_before_spec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("qwertyhgf%s");
    int size = ret_size(5);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_empty_str)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%s");
    int size = ret_size(5);
    
    int len_1 = snprintf(buf_1, size, format, "");
    int len_2 = my_snprintf(buf_2, size, format, "");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_not_zero_term)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%.5s");
    int size = ret_size(15);
    char string[] = { 'H', 'e', 'l', 'l', 'o' };
    
    int len_1 = snprintf(buf_1, size, format, string);
    int len_2 = my_snprintf(buf_2, size, format, string);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_left_pad)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%-17s");
    int size = ret_size(25);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_right_pad)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%17s");
    int size = ret_size(25);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_big_prec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%.17s");
    int size = ret_size(25);
    
    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(s_small_prec_right_pad)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%17.5s");
    int size = ret_size(25);

    int len_1 = snprintf(buf_1, size, format, "Hello, world!");
    int len_2 = my_snprintf(buf_2, size, format, "Hello, world!");
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST



START_TEST(ho_equal)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%ho");
    int size = ret_size(4);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_equal_add_sym)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("qwe%hoeww");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_less_cutoff_width)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("qwe%10ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_less_cutoff_padded)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("qwe%-10ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_less_cutoff_sym)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%hosdfgnxcfdsdv");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_less_cutoff_before_spec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("sdfgnxcsdfgfdsdv%ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_zero)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 0);
    int len_2 = my_snprintf(buf_2, size, format, 0);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_zero_prec_zero)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%.0ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 0);
    int len_2 = my_snprintf(buf_2, size, format, 0);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_left_pad)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%-7ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_right_pad)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%7ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_zero_pad)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%07ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_zero_pad_zero)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%07ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 0);
    int len_2 = my_snprintf(buf_2, size, format, 0);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_add_zero)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%#ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_add_zero_prec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%#.5ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 20);
    int len_2 = my_snprintf(buf_2, size, format, 20);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_add_zero_prec_inc)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%#.2ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 9);
    int len_2 = my_snprintf(buf_2, size, format, 9);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_zero_right_pad)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%07ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 9);
    int len_2 = my_snprintf(buf_2, size, format, 9);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_zero_right_pad_prec)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%-07.3ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 9);
    int len_2 = my_snprintf(buf_2, size, format, 9);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(ho_short_overflow)
{
    char buf_1[LEN], buf_2[LEN];
    const char *format = ret_char_p("%ho");
    int size = ret_size(10);
    
    int len_1 = snprintf(buf_1, size, format, 900000);
    int len_2 = my_snprintf(buf_2, size, format, 900000);
    ck_assert_int_eq(len_1, len_2);
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST


// Функция объединения тестов всех спецификаторов в набор
Suite *all_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("all");

    tc_pos = tcase_create("positives");
    // Указатель на NULL
    tcase_add_test(tc_pos, all_nullptr);
    // Только 2 спецификатора
    tcase_add_test(tc_pos, all_equal);
    // Оба спецификатора и символы
    tcase_add_test(tc_pos, all_equal_add_sym);
    // Оба спецификатора, размер заканчивается на символах
    tcase_add_test(tc_pos, all_less_cutoff_sym);
    // Оба спецификатора, размер заканчивается на s
    tcase_add_test(tc_pos, all_less_cutoff_s);
    // Оба спецификатора, размер заканчивается на ho
    tcase_add_test(tc_pos, all_less_cutoff_ho);
    // Нет спецификаторов
    tcase_add_test(tc_pos, all_no_spec);
    // Оба спецификатора, ширина через *
    tcase_add_test(tc_pos, all_width_star); 
    // Оба спецификатора, ширина через *, отрицательная
    tcase_add_test(tc_pos, all_width_star_neg);
    // Оба спецификатора, точность через *
    tcase_add_test(tc_pos, all_prec_star);
    // Оба спецификатора, точность через *, отрицательная
    tcase_add_test(tc_pos, all_prec_star_neg);
    // Оба спецификатора, ширина и точность через *
    tcase_add_test(tc_pos, all_all_star);
    // Оба спецификатора, повторяющиеся флаги
    tcase_add_test(tc_pos, all_many_flags);
    // Оба спецификатора, точность задана только точкой
    tcase_add_test(tc_pos, all_only_dot_prec);
    // Оба спецификатора, флаги - и 0 одновременно
    tcase_add_test(tc_pos, all_only_minus_zero);
    // Оба спецификатора, флаги + и пробел одновременно
    tcase_add_test(tc_pos, all_only_plus_space);
    // Несколько спецификаторов
    tcase_add_test(tc_pos, all_many_spec);
    // Лишние аргументы
    tcase_add_test(tc_pos, all_excess_args);
    // Размер 0
    tcase_add_test(tc_pos, all_size_zero);
    // Размер обрезает ровно в конце ho(проверка на вставку терм нуля)
    tcase_add_test(tc_pos, all_less_cutoff_ho_end);
    suite_add_tcase(s, tc_pos);

    return s;
}

// Функция объединения тестов спецификатора s в набор
Suite *s_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("s");

    tc_pos = tcase_create("positives");
    // Только спецификатор
    tcase_add_test(tc_pos, s_equal);
    // Спецификатор и простые символы
    tcase_add_test(tc_pos, s_equal_add_sym);
    // Размер заканчивается на выравнивании шириной
    tcase_add_test(tc_pos, s_less_cutoff_width);
    // Размер заканчивается на выровненной шириной строке
    tcase_add_test(tc_pos, s_less_cutoff_padded);
    // Размер заканчивается на символах
    tcase_add_test(tc_pos, s_less_cutoff_sym);
    // Размер заканчивается до спецификатора
    tcase_add_test(tc_pos, s_less_cutoff_before_spec);
    // Пустая строка для вставки
    tcase_add_test(tc_pos, s_empty_str);
    // Строка не ноль-терминирована при указанной точности
    tcase_add_test(tc_pos, s_not_zero_term);
    // Выравнивание по левому краю
    tcase_add_test(tc_pos, s_left_pad);
    // Выравнивание по правому краю
    tcase_add_test(tc_pos, s_right_pad);
    // Точность больше строки
    tcase_add_test(tc_pos, s_big_prec);
    // Выравнивание по правому краю и ограниченная точностью строка
    tcase_add_test(tc_pos, s_small_prec_right_pad);
    suite_add_tcase(s, tc_pos);

    return s;
}

// Функция объединения тестов спецификатора ho в набор
Suite *ho_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("ho");

    tc_pos = tcase_create("positives");
    // Только спецификатор
    tcase_add_test(tc_pos, ho_equal);
    // Спецификатор и простые символы
    tcase_add_test(tc_pos, ho_equal_add_sym);
    // Размер заканчивается на выравнивании шириной
    tcase_add_test(tc_pos, ho_less_cutoff_width);
    // Размер заканчивается на выровненном шириной числе
    tcase_add_test(tc_pos, ho_less_cutoff_padded);
    // Размер заканчивается на символах
    tcase_add_test(tc_pos, ho_less_cutoff_sym);
    // Размер заканчивается до спецификатора
    tcase_add_test(tc_pos, ho_less_cutoff_before_spec);
    // Число 0
    tcase_add_test(tc_pos, ho_zero);
    // Число 0 c нулевой точностью
    tcase_add_test(tc_pos, ho_zero_prec_zero);
    // Выравнивание по левому краю
    tcase_add_test(tc_pos, ho_left_pad);
    // Выравнивание по правому краю
    tcase_add_test(tc_pos, ho_right_pad);
    // Выравнивание нулями
    tcase_add_test(tc_pos, ho_zero_pad);
    // Выравнивание нулями нуля
    tcase_add_test(tc_pos, ho_zero_pad_zero);
    // Доп ноль
    tcase_add_test(tc_pos, ho_add_zero);
    // Доп ноль при точности
    tcase_add_test(tc_pos, ho_add_zero_prec);
    // Доп ноль увеличивает точность
    tcase_add_test(tc_pos, ho_add_zero_prec_inc);
    // Левое выравнивание нулями
    tcase_add_test(tc_pos, ho_zero_right_pad);
    // Правое выравнивание нулями при данной точности
    tcase_add_test(tc_pos, ho_zero_right_pad_prec);
    // Переполнение short
    tcase_add_test(tc_pos, ho_short_overflow);
    
    suite_add_tcase(s, tc_pos);

    return s;
}
