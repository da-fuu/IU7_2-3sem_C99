#include <stdio.h>
#include "errors.h"
#include "filesort.h"
#include "file_filter.h"
#include "io.h"
#include "binwork.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    enum mode_e mode;

    ret_code = process_args(argc, argv, &mode);
    if (ret_code != OK)
        return process_error(ret_code);
        
    switch (mode)
    {
        case FILTER:
            ret_code = filter_file(argv[2], argv[3], argv[4]);
            break;
        case SORT:
            ret_code = sort_file(argv[2]);
            if (ret_code == OK)
                print_file(argv[2]);
            break;
        case IMPORT:
            ret_code = import_file(argv[2], argv[3]);
            break;
        case EXPORT:
            ret_code = export_file(argv[2], argv[3]);
            break;
    }

    if (ret_code != OK)
        return process_error(ret_code);

    return OK;
}
