#ifndef MARK_H
#define MARK_H

#include "datafile.h"

struct Mark
{
    char  student_id[8];
    char  subject_id[7];
    char  semester[4];
    int   year;
    float mark;
};

void load_marks(struct DataFile mark_file, struct Mark marks[], int num_marks);
void print_mark(struct Mark mark);

#endif // MARK_H
