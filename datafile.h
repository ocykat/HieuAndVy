#ifndef DATAFILE_H
#define DATAFILE_H

#include <stdio.h>

struct DataFile
{
    FILE* ptr;
    char format[256];
    int num_rows;
    int num_cols;
};

int open_data_file(struct DataFile* data_file, char* path, int num_cols);
void get_file_format(char* format, int num_cols);
int  count_num_rows(FILE* file_ptr);
void parse_row(FILE* file_ptr, char row[][128], int num_cols);

#endif // DATAFILE_H
