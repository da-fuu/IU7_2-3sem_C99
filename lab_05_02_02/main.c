#include <stdio.h>
#include "errors.h"
#include "file.h"


// Основная функция программы
int main(int argc, char **argv)
{
    int ret_code;
    double dispersion;
    FILE *f;

    if (argc != 2)
        return process_error(ERR_ARGS);

    f = fopen(argv[1], "r");
    if (f == NULL)
        return process_error(ERR_FILE);

    ret_code = find_disp(f, &dispersion);
    if (ret_code != OK)
    {
        fclose(f);
        return process_error(ret_code);
    }
    fclose(f);
    
    printf("Дисперсия чисел: %f \n", dispersion);

    return OK;
}
