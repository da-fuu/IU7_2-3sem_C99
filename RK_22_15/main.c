#include <stdio.h>
#include "errors.h"
#include "io.h"
#include "process.h"

int main(void)
{
    int rc; 
    char filename[STR_LEN + 1];
    char words[STR_LEN / 2][STR_LEN + 1];
    size_t words_num;

    rc = input_filename(filename);
    if (rc != OK)
    {
        process_error(rc);
        return rc;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        process_error(FILE_ERROR);
        return FILE_ERROR;
    }

    rc = get_words(file, words, &words_num);
    if (rc != OK)
    {
        process_error(rc);
        return rc;
    }

    rc = del_words_same_as_max(words, &words_num);
    if (rc != OK)
    {
        process_error(rc);
        return rc;
    }

    del_chars(words, words_num);

    print_words(words, words_num);

    fclose(file);
    return OK;
}
