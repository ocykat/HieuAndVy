#include "student.h"
#include "datafile.h"
#include "mark.h"
#include "subject.h"
#include <stdlib.h>
#include <string.h>

void load_students(struct DataFile student_file, struct Student students[], int num_students)
{
    char row[6][128];
//    fscanf(student_file.ptr, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    parse_row(student_file.ptr, row, student_file.num_cols);

    for (int i = 0; i < num_students; i++)
    {
//        fscanf(student_file.ptr, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", row[0], row[1], row[2], row[3], row[4], row[5]);
        parse_row(student_file.ptr, row, student_file.num_cols);

        strcpy(students[i].full_name     , row[0]);
        strcpy(students[i].id            , row[1]);
        students[i].entrance_year = atoi(row[2]);
        strcpy(students[i].birthday      , row[3]);
        strcpy(students[i].place_of_birth, row[4]);
        strcpy(students[i].major         , row[5]);
    }
}

void print_student(struct Student student)
{
    printf("Full name: %s - ", student.full_name);
    printf("ID: %s - ", student.id);
    printf("Entrance year: %d - ", student.entrance_year);
    printf("Birthday: %s - ", student.birthday);
    printf("Place of birth: %s - ", student.place_of_birth);
    printf("Major: %s\n", student.major);
}

int find_student(char* student_id, struct Student students[], int num_students)
{
    int index = -1;

    for (int i = 0; i < num_students; i++)
    {
        if (strcmp(students[i].id, student_id) == 0)
        {
            index = i;
            break;
        }
    }

    return index;
}

float calc_average_mark(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects)
{
    int sum_mark = 0;
    int sum_credits = 0;

    for (int i = 0; i < num_marks; i++)
    {
        if (strcmp(marks[i].student_id, student_id) == 0)
        {
            print_mark(marks[i]);
            int credits = get_num_credits(marks[i].subject_id, subjects, num_subjects);
            sum_mark += marks[i].mark * credits;
            sum_credits += credits;
        }
    }

    float average_mark = (float) sum_mark / sum_credits;

    return average_mark;
}

int calc_total_credits(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects)
{
    int sum_credits = 0;

    for (int i = 0; i < num_marks; i++)
    {
        if (marks[i].mark >= 5 && strcmp(marks[i].student_id, student_id) == 0)
        {
            int credits = get_num_credits(marks[i].subject_id, subjects, num_subjects);
            sum_credits += credits;
        }
    }

    return sum_credits;
}

int calc_general_credits(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects)
{
    int sum_credits = 0;

    for (int i = 0; i < num_marks; i++)
    {
        if (marks[i].mark >= 5 && strcmp(marks[i].student_id, student_id) == 0 && is_general_subject(marks[i].subject_id, subjects, num_subjects))
        {
            sum_credits += get_num_credits(marks[i].subject_id, subjects, num_subjects);
        }
    }

    return sum_credits;
}

int calc_specialized_credits(char* student_id, struct Mark marks[], int num_marks, struct Subject subjects[], int num_subjects)
{
    return calc_total_credits(student_id, marks, num_marks, subjects, num_subjects)
         - calc_general_credits(student_id, marks, num_marks, subjects, num_subjects);
}
