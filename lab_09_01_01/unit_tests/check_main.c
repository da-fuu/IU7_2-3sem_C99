#include <check.h>

#include "errors.h"
#include "check_array.h"


// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    Suite *s_insert, *s_find;
    SRunner *runner;

    s_insert = insert_suite();
    s_find = find_suite();

    runner = srunner_create(s_insert);
    srunner_add_suite(runner, s_find);

    srunner_run_all(runner, CK_VERBOSE);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
        return ERR_UNIT_FAIL;
    return OK;
}
