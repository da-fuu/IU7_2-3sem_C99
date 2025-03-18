#include <stdio.h>
#include "errors.h"
#include "args.h"
#include "struct.h"
#include "array.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    enum mode_e mode;
    enum field_e field;
    struct film_s films_arr[MAX_FILE_LEN];
    size_t arr_len;
    int index_finded;

    ret_code = process_args(argc, argv, &mode, &field);
    if (ret_code != OK)
        return process_error(ret_code);

    ret_code = read_file(argv[1], films_arr, &arr_len, field);
    if (ret_code != OK)
        return process_error(ret_code);

    if (mode == PRINT) 
        print_arr(films_arr, arr_len);
    else if (mode == FIND)
    {
        ret_code = find_film(films_arr, arr_len, field, argv[3], &index_finded);
        if (ret_code != OK)
            return process_error(ret_code);

        if (index_finded >= 0)
            print_film(&films_arr[index_finded]);
        else
            printf("Not found\n");
    }

    return OK;
}
