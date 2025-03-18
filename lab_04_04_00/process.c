#include <stdlib.h>
#include <ctype.h>
#include "process.h"
#include "errors.h"


// Функция для разбиения строки на числа ip-адреса
// Принимает строку по указателю, принимает и изменяет по указателю массив чисел
// Возвращает успешность разбиения на правильное количество чисел
bool extact_ip_nums_from_str(char *string, long long nums[])
{
    char *end_num_ptr;

    while (isspace(*string))
        string++;

    for (size_t i = 0; i < NUM_BYTES_IN_IP; i++)
    {
        if (*string == '+' || *string == '-' || *string == '.')
            return false;
        nums[i] = strtoll(string, &end_num_ptr, 10);
        if (end_num_ptr - string > 3 || end_num_ptr == string)
            return false;
        if (i < NUM_BYTES_IN_IP - 1 && *end_num_ptr != '.')
            return false;
        string = end_num_ptr + 1;
    }

    while (isspace(*end_num_ptr))
        end_num_ptr++;
    
    return *end_num_ptr == '\0';
}

// Функция проверки массива чисел - составляющих адреса на принадлежность промежутку
// Принимает принимает по указателю массив чисел
// Возвращает результат проверки
bool validate_numbers(long long nums[])
{
    for (size_t i = 0; i < NUM_BYTES_IN_IP; i++)
        if (nums[i] > 255 || nums[i] < 0)
            return false;
    return true; 
}
