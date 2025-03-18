#include <stdbool.h>
#include <stdlib.h>
#ifdef DYNLOAD
#include <dlfcn.h>
#endif // #ifdef DYNLOAD

#include "args.h"
#include "errors.h"
#include "libarr.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    bool filter_flag;
    int *ptr_beg, *ptr_end;
    int *new_ptr_beg, *new_ptr_end;
    size_t file_len;

#ifdef DYNLOAD
    find_file_len_t find_file_len;
    read_file_t read_file;
    key_t key;
    mysort_t mysort;
    compar_t compare_int;
    write_file_t write_file;
    void *lib = dlopen("libarr.so", RTLD_NOW);
    if (lib == NULL)
        return process_error(ERR_LIB_OPEN);

    find_file_len = dlsym(lib, "find_file_len");
    if (find_file_len == NULL)
    {
        dlclose(lib);
        return process_error(ERR_FUNC_LOAD);
    }
    read_file = dlsym(lib, "read_file");
    if (read_file == NULL)
    {
        dlclose(lib);
        return process_error(ERR_FUNC_LOAD);
    }
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
    write_file = dlsym(lib, "write_file");
    if (write_file == NULL)
    {
        dlclose(lib);
        return process_error(ERR_FUNC_LOAD);
    }
    
#endif // #ifdef DYNLOAD
    
    ret_code = process_args(argc, argv, &filter_flag);
    if (ret_code != OK)
    {
#ifdef DYNLOAD
        dlclose(lib);
#endif // #ifdef DYNLOAD
        return process_error(ret_code);
    }
    
    ret_code = find_file_len(argv[1], &file_len);
    if (ret_code != OK)
    {
#ifdef DYNLOAD
        dlclose(lib);
#endif // #ifdef DYNLOAD
        return process_error(ret_code);
    }
    
    ptr_beg = malloc(sizeof(int) * file_len);
    if (ptr_beg == NULL)
    {
#ifdef DYNLOAD
        dlclose(lib);
#endif // #ifdef DYNLOAD
        return process_error(ERR_NO_MEMORY);
    }
    ptr_end = ptr_beg + file_len;
    
    read_file(argv[1], ptr_beg, ptr_end);

    if (filter_flag)
    {
        new_ptr_beg = malloc(sizeof(int) * (ptr_end - ptr_beg));
        if (new_ptr_beg == NULL)
        {
#ifdef DYNLOAD
            dlclose(lib);
#endif // #ifdef DYNLOAD
            free(ptr_beg);
            return process_error(ERR_NO_MEMORY);
        }
        ret_code = key(ptr_beg, ptr_end, new_ptr_beg, &new_ptr_end);
        free(ptr_beg);
        if (ret_code != OK)
        {
#ifdef DYNLOAD
            dlclose(lib);
#endif // #ifdef DYNLOAD
            free(new_ptr_beg);
            return process_error(ret_code);
        }
    }
    else
    {
        new_ptr_beg = ptr_beg;
        new_ptr_end = ptr_end;
    }

    mysort(new_ptr_beg, new_ptr_end - new_ptr_beg, sizeof(int), compare_int);

    ret_code = write_file(argv[2], new_ptr_beg, new_ptr_end);
#ifdef DYNLOAD
    dlclose(lib);
#endif // #ifdef DYNLOAD
    free(new_ptr_beg);
    return process_error(ret_code);
}
