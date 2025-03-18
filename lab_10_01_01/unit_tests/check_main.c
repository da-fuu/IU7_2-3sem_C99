#include <check.h>

#include "errors.h"
#include "check_operations.h"
#include "check_sort.h"


// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    SRunner *runner;

    runner = srunner_create(find_suite());
    srunner_add_suite(runner, pop_front_suite());
    srunner_add_suite(runner, reverse_suite());
    srunner_add_suite(runner, front_back_split_suite());
    srunner_add_suite(runner, sorted_merge_suite());
    srunner_add_suite(runner, sort_suite());

    srunner_run_all(runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return ERR_UNIT_FAIL;
    return OK;
}
