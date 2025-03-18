#include <stdio.h>
#include <stdbool.h>
#include "io.h"
#include "errors.h"
#include "process.h"


// Основная функция программы
int main(void)
{
    int ret_code;
    bool is_valid;
    char string[STR_LEN+1];
    long long numbers[NUM_BYTES_IN_IP];

    ret_code = input_string(string);
    if (process_error(ret_code) != OK)
        return ret_code;

    is_valid = extact_ip_nums_from_str(string, numbers);

    if (is_valid)
        is_valid = validate_numbers(numbers);

    if (is_valid)
        puts("YES");
    else
        puts("NO");
    return OK;
}
