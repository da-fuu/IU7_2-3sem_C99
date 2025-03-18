#include <stdbool.h>
#include <malloc.h>
#include "errors.h"
#include "args.h"
#include "array.h"
#include "file.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    bool filter_flag;
    int *ptr_beg, *ptr_end;
    int *new_ptr_beg, *new_ptr_end;

    ret_code = process_args(argc, argv, &filter_flag);
    if (ret_code != OK)
        return process_error(ret_code);

    ret_code = read_file(argv[1], &ptr_beg, &ptr_end);
    if (ret_code != OK)
        return process_error(ret_code);

    if (filter_flag)
    {
        ret_code = key(ptr_beg, ptr_end, &new_ptr_beg, &new_ptr_end);
        free(ptr_beg);
        if (ret_code != OK)
            return process_error(ret_code);
    }
    else
    {
        new_ptr_beg = ptr_beg;
        new_ptr_end = ptr_end;
    }

    mysort(new_ptr_beg, new_ptr_end - new_ptr_beg, sizeof(int), compare_int);

    ret_code = write_file(argv[2], new_ptr_beg, new_ptr_end);
    free(new_ptr_beg);
    return process_error(ret_code);
}
