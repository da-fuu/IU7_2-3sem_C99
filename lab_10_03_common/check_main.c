#include <check.h>

#include "check_create_clear_destroy.h"
#include "check_insert_find_remove.h"
#include "check_min_max_each.h"


// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    SRunner *runner;

    runner = srunner_create(create_suite());
    srunner_add_suite(runner, clear_suite());
    srunner_add_suite(runner, destroy_suite());
    srunner_add_suite(runner, insert_suite());
    srunner_add_suite(runner, find_suite());
    srunner_add_suite(runner, remove_suite());
    srunner_add_suite(runner, min_suite());
    srunner_add_suite(runner, max_suite());
    srunner_add_suite(runner, each_suite());

    srunner_run_all(runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return 1;
    return 0;
}
