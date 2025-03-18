#include "errors.h"
#include "args.h"
#include "file.h"
#include "matrix.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int rc;
    swap_t swap;
    int **matrix;
    int n;

    rc = process_args(argc, argv, &swap);
    if (rc != OK)
        return process_error(rc);

    rc = read_dimensions(argv[1], &n);
    if (rc != OK)
        return process_error(rc);

    matrix = create_sq_matrix(n);
    if (matrix == NULL)
        return process_error(ERR_NO_MEMORY);

    rc = read_matrix(argv[1], matrix, n);
    if (rc != OK)
    {
        free_sq_matrix(matrix);
        return process_error(rc);
    }

    if (swap == ROWS)
        swap_rows(matrix, n);
    else
        swap_cols(matrix, n);

    rc = write_sq_matrix(matrix, n, argv[2]);
    free_sq_matrix(matrix);
    return process_error(rc);
}
