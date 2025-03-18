#include "errors.h"
#include "struct.h"
#include "io.h"
#include "list.h"
#include "matrix.h"


// Основная функция программы
int main(void)
{
    int ret_code;
    node_t *matrix_1, *matrix_2, *matrix_out;
    mode_t mode;

    ret_code = read_mode(&mode);
    if (ret_code != OK)
        return process_error(ret_code);

    switch (mode)
    {
        case OUT:
            ret_code = read_matrix(&matrix_out);
            if (ret_code != OK)
                return process_error(ret_code);
            break;
        case ADD:
            ret_code = read_matrix(&matrix_1);
            if (ret_code != OK)
                return process_error(ret_code);
            ret_code = read_matrix(&matrix_2);
            if (ret_code != OK)
            {
                free_list(matrix_1);
                return process_error(ret_code);
            }
            matrix_out = add_matrices(&matrix_1, &matrix_2);
            break;
        case MUL:
            ret_code = read_matrix(&matrix_1);
            if (ret_code != OK)
                return process_error(ret_code);
            ret_code = read_matrix(&matrix_2);
            if (ret_code != OK)
            {
                free_list(matrix_1);
                return process_error(ret_code);
            }
            ret_code = mul_matrices(matrix_1, matrix_2, &matrix_out);
            free_list(matrix_1);
            free_list(matrix_2);
            if (ret_code != OK)
                return process_error(ret_code);
            break;
        case LIN:
            ret_code = read_matrix(&matrix_out);
            if (ret_code != OK)
                return process_error(ret_code);
            ret_code = remove_row_with_max(&matrix_out);
            if (ret_code != OK)
            {
                free_list(matrix_out);
                return process_error(ret_code);
            }
            break;
    }
    ret_code = print_matrix(matrix_out);
    free_list(matrix_out);
    return process_error(ret_code);
}
