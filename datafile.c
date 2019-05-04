#include "datafile.h"
#include <string.h>

int open_data_file(struct DataFile* data_file, char* path, int num_cols)
{
    data_file->ptr      = fopen(path, "r");

    if (data_file->ptr == NULL)
    {
        return 0;
    }

    data_file->num_cols = num_cols;
    get_file_format(data_file->format, num_cols);
    data_file->num_rows = count_num_rows(data_file->ptr);

    fclose(data_file->ptr);

    // Reopen
    data_file->ptr      = fopen(path, "r");

    return 1;
}

void get_file_format(char* format, int num_cols)
{
    for (int i = 0; i < num_cols - 1; i++)
    {
        strcat(format, "\[^,],");
    }

    strcat(format, "\[^\n]\n");
}

int count_num_rows(FILE* file_ptr)
{
    int num_rows = 0;

    while(!feof(file_ptr))
    {
        char c = fgetc(file_ptr);

        if (c == '\n')
        {
            num_rows++;
        }
    }

    return num_rows;
}

void parse_row(FILE* file_ptr, char row[][128], int num_cols)
{
    int i;

    for (i = 0; i < num_cols - 1; i++)
    {
        fscanf(file_ptr, "%[^,],", row[i]);
    }

    fscanf(file_ptr, "%[^\n]\n", row[i]);
}
