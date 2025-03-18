#include <check.h>

#include "errors.h"
#include "check_operations.h"


// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    Suite *s_add, *s_multiply, *s_solve;
    SRunner *runner;

    s_add = addition_suite();
    s_multiply = multiplication_suite();
    s_solve = solve_suite();

    runner = srunner_create(s_add);
    srunner_add_suite(runner, s_multiply);
    srunner_add_suite(runner, s_solve);

    srunner_run_all(runner, CK_VERBOSE);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return ERR_UNIT_FAIL;
    return OK;
}
