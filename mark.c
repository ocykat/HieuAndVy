#include "mark.h"
#include "datafile.h"
#include <stdlib.h>
#include <string.h>

void load_marks(struct DataFile mark_file, struct Mark marks[], int num_marks)
{
    char row[5][128];
    parse_row(mark_file.ptr, row, mark_file.num_cols);

    for (int i = 0; i < num_marks; i++)
    {
        parse_row(mark_file.ptr, row, mark_file.num_cols);

        strcpy(marks[i].student_id, row[0]);
        strcpy(marks[i].subject_id, row[1]);
        strcpy(marks[i].semester, row[2]);
        marks[i].year = atoi(row[3]);
        marks[i].mark = atof(row[4]);
    }
}

void print_mark(struct Mark mark)
{
    printf("Student ID: %s - ", mark.student_id);
    printf("Subject ID: %s - ", mark.subject_id);
    printf("Semester: %s - ", mark.semester);
    printf("Year: %d - ", mark.year);
    printf("Mark: %.2f\n", mark.mark);
}
