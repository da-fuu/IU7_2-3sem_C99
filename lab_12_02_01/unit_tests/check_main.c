#include <check.h>

#include "errors.h"
#include "check_lib_array.h"
#ifdef DYNLOAD
#include <dlfcn.h>
#include "libarr.h"

key_t key;
mysort_t mysort;
compar_t compare_int;

#endif // #ifdef DYNLOAD

// Основная функция для прогона модульных тестов
int main(void)
{
    int failed_tests = 0;
    Suite *s_key, *s_mysort;
    SRunner *runner;
    
#ifdef DYNLOAD
    void *lib = dlopen("libarr.so", RTLD_NOW);
    if (lib == NULL)
        return process_error(ERR_LIB_OPEN);
    
    key = dlsym(lib, "key");
    if (key == NULL)
    {
        dlclose(lib);
        return process_error(ERR_FUNC_LOAD);
    }
    mysort = dlsym(lib, "mysort");
    if (mysort == NULL)
    {
        dlclose(lib);
        return process_error(ERR_FUNC_LOAD);
    }
    compare_int = dlsym(lib, "compare_int");
    if (compare_int == NULL)
    {
        dlclose(lib);
        return process_error(ERR_FUNC_LOAD);
    }
#endif // #ifdef DYNLOAD
    
    s_key = key_suite();
    s_mysort = mysort_suite();

    runner = srunner_create(s_key);
    srunner_add_suite(runner, s_mysort);

    srunner_run_all(runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (failed_tests > 0)
    {
#ifdef DYNLOAD
        dlclose(lib);
#endif // #ifdef DYNLOAD
        return ERR_UNIT_FAIL;
    }
    return OK;
}
