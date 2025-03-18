#include <check.h>

#include "check_my_snprintf.h"


// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    SRunner *runner;

    runner = srunner_create(all_suite());
    srunner_add_suite(runner, s_suite());
    srunner_add_suite(runner, ho_suite());

    srunner_run_all(runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return 1;
    return 0;
}
