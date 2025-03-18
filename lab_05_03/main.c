#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "file.h"
#include "io.h"
#include "binwork.h"


/*
Выбранный целочисленный тип - uint32_t
Алгоритм сортировки - сортировка пузырьком
Направление сортировки - по возрастанию
*/

// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    enum mode_e mode;
    long nums_len;
    char *end_num;

    ret_code = process_args(argc, argv, &mode);
    if (ret_code != OK)
        return process_error(ret_code);
        
    switch (mode)
    {
        case CREATE:
            nums_len = strtol(argv[2], &end_num, 10);
            if (*end_num != '\0')
                return process_error(ERR_CREATE_ARGS);
            ret_code = create_file_with_num(argv[3], nums_len);
            break;
        case PRINT:
            ret_code = print_file(argv[2]);
            break;
        case SORT:
            ret_code = sort_file(argv[2]);
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
