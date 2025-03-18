#include <stdio.h>

#include "errors.h"
#include "struct.h"
#include "args.h"
#include "array.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    enum mode_e mode;
    enum field_e field;
    struct film_s *films_arr;
    int arr_len;
    int index_found;

    ret_code = process_args(argc, argv, &mode, &field);
    if (ret_code != OK)
        return process_error(ret_code);

    ret_code = read_file(argv[1], field, &films_arr, &arr_len);
    if (ret_code != OK)
        return process_error(ret_code);

    if (mode == PRINT) 
        print_arr(films_arr, arr_len);
    if (mode == FIND)
    {
        ret_code = find_film(films_arr, arr_len, field, argv[3], &index_found);
        if (ret_code != OK)
        {
            free_arr(films_arr, arr_len);
            return process_error(ret_code);
        }

        if (index_found >= 0)
            print_film(&films_arr[index_found]);
        else
            printf("Not found\n");
    }
    free_arr(films_arr, arr_len);
    return OK;
}
