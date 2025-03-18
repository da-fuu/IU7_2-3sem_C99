#include <check.h>

#include "lib_array.h"
#include "check_lib_array.h"


// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    SRunner *runner;

    runner = srunner_create(fill_fib_suite());
    srunner_add_suite(runner, copy_uniq_elems_suite());

    srunner_run_all(runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return ERR_UNIT_FAIL;
    return OK;
}
