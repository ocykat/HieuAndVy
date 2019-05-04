#ifndef STUDENT_H
#define STUDENT_H

#include "datafile.h"
#include "mark.h"
#include "subject.h"

struct Student
{
    char full_name[64];
    char id[8];
    int  entrance_year;
    char birthday[11];
    char place_of_birth[32];
    char major[32];
};

void load_students(struct DataFile student_file, struct Student students[], int num_students);
void print_student(struct Student student);
int find_student(char* student_id, struct Student students[], int num_students);
float calc_average_mark(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects);
int calc_total_credits(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects);
int calc_general_credits(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects);
int calc_specialized_credits(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects);

#endif // STUDENT_H

