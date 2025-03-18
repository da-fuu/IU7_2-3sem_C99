#include <check.h>

#include "errors.h"
#include "check_matrix.h"


// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    SRunner *runner;

    runner = srunner_create(add_matrices_suite());
    srunner_add_suite(runner, mul_matrices_suite());
    srunner_add_suite(runner, remove_row_with_max_suite());

    srunner_run_all(runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return ERR_UNIT_FAIL;
    return OK;
}
