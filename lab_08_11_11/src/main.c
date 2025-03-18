#include "errors.h"
#include "args.h"
#include "matrix.h"
#include "file.h"
#include "operations.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    mode_t mode;
    char *out_filename = NULL;
    matrix_t matrix_in_1, matrix_in_2, matrix_out;

    ret_code = process_args(argc, argv, &mode);
    if (ret_code != OK)
        return process_error(ret_code);

    switch (mode)
    {
        case ADD:
            ret_code = read_matrix(argv[2], &matrix_in_1);
            if (ret_code != OK)
                return process_error(ret_code);
            ret_code = read_matrix(argv[3], &matrix_in_2);
            if (ret_code != OK)
            {
                free_matrix(matrix_in_1.elements);
                return process_error(ret_code);
            }

            ret_code = add_matrices(matrix_in_1, matrix_in_2, &matrix_out);
            free_matrix(matrix_in_1.elements);
            free_matrix(matrix_in_2.elements);
            if (ret_code != OK)
                return process_error(ret_code);

            out_filename = argv[4];
            break;
        case MULTIPLY:
            ret_code = read_matrix(argv[2], &matrix_in_1);
            if (ret_code != OK)
                return process_error(ret_code);
            ret_code = read_matrix(argv[3], &matrix_in_2);
            if (ret_code != OK)
            {
                free_matrix(matrix_in_1.elements);
                return process_error(ret_code);
            }

            ret_code = multiply_matrices(matrix_in_1, matrix_in_2, &matrix_out);
            free_matrix(matrix_in_1.elements);
            free_matrix(matrix_in_2.elements);
            if (ret_code != OK)
                return process_error(ret_code);

            out_filename = argv[4];
            break;
        case SOLVE:
            ret_code = read_matrix(argv[2], &matrix_in_1);
            if (ret_code != OK)
                return process_error(ret_code);

            ret_code = solve_sle(matrix_in_1, &matrix_out);
            free_matrix(matrix_in_1.elements);
            if (ret_code != OK)
                return process_error(ret_code);

            out_filename = argv[3];
            break;
    }
    ret_code = write_matrix(matrix_out, out_filename);
    free_matrix(matrix_out.elements);

    return process_error(ret_code);
}
