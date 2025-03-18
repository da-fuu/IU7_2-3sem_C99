#include <stdio.h>
#include "errors.h"
#include "file.h"


// Основная функция программы
int main(void)
{
    int ret_code;
    int changed_times;

    ret_code = process(stdin, &changed_times);
    if (ret_code != OK)
        return process_error(ret_code);

    printf("Количество смен знака: %d \n", changed_times);
    
    return OK;
}
