#include "datafile.h"
#include "mark.h"
#include "subject.h"
#include "student.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
// *.exe and the "data" folder have to be in the same folder
#define STUDENT_FILE_PATH   "data/Student_Info.txt"
#define MARK_FILE_PATH      "data/Marks_Of_Student.txt"
#define SUBJECT_FILE_PATH   "data/Subject_Info.txt"

#define STUDENT_FILE_NUM_COLS    6
#define MARK_FILE_NUM_COLS       5
#define SUBJECT_FILE_NUM_COLS    5

int main()
{
    struct DataFile student_file;
    struct DataFile mark_file;
    struct DataFile subject_file;

    // Open Files
    if (!open_data_file(&student_file, STUDENT_FILE_PATH, STUDENT_FILE_NUM_COLS))
    {
        printf("Error: File \"%s\" not found.\n", STUDENT_FILE_PATH);
        return 0;
    }

    if (!open_data_file(&mark_file, MARK_FILE_PATH, MARK_FILE_NUM_COLS))
    {
        printf("Error: File \"%s\" not found.\n", MARK_FILE_PATH);
        return 0;
    }

    if (!open_data_file(&subject_file, SUBJECT_FILE_PATH, SUBJECT_FILE_NUM_COLS))
    {
        printf("Error: File \"%s\" not found.\n", SUBJECT_FILE_PATH);
        return 0;
    }

    assert(student_file.num_rows == 15);
    assert(mark_file.num_rows == 276);
    assert(subject_file.num_rows == 42);

    printf("Number of student file's rows: %d\n", student_file.num_rows);
    printf("Number of mark file's rows: %d\n",    mark_file.num_rows);
    printf("Number of subject file's rows: %d\n", subject_file.num_rows);

    int num_students = student_file.num_rows - 1;
    int num_marks    = mark_file.num_rows - 1;
    int num_subjects = subject_file.num_rows - 1;

    struct Student students[num_students];

    load_students(student_file, students, num_students);

    for (int i = 0; i < num_students; i++) {
        printf("%s\n", students[i].id);
    }

    struct Mark marks[mark_file.num_rows];

    load_marks(mark_file, marks, num_marks);

    for (int i = 0; i < num_marks; i++) {
        printf("%s\n", marks[i].student_id);
    }

    struct Subject subjects[num_subjects];

    load_subjects(subject_file, subjects, num_subjects);

    for (int i = 0; i < num_subjects; i++) {
        print_subject(subjects[i]);
    }

    while (1)
    {
        printf("Choose a function [1-4]:\n");
        printf("1. View grades of a student\n");
        printf("2. Find the student with highest/lowest score\n");
        printf("3. Show list of students eligible for graduation\n");
        printf("4. Quit\n");
        printf("-> ");

        char cmd[3];

        scanf("%s", cmd);
        printf("Command: %s\n", cmd);

        printf("====================================\n");

        if (strcmp(cmd, "1") == 0)
        {
            printf("Function: View grades of a student\n");

            while (1)
            {
                printf("Enter Student Identifier:\n");
                printf("-> ");

                char student_id[8];
                scanf("%s", student_id);
                printf("Student ID: %s\n", student_id);

                int index = find_student(student_id, students, num_students);

                if (index == -1)
                {
                    printf("Invalid student id \"%s\"", student_id);
                    continue;
                }

                for (int i = 0; i < num_marks; i++)
                {
                    if (strcmp(marks[i].student_id, student_id) == 0)
                    {
                        print_mark(marks[i]);
                    }
                }

                float average_mark = calc_average_mark(student_id, marks, num_marks, subjects, num_subjects);

                printf("Average Mark: %.2f\n", average_mark);

                break;
            }
        }
        else if (strcmp(cmd, "2") == 0)
        {
            printf("Function: Find the student with highest/lowest score\n");
            printf("Choose: [a, b]\n");
            printf("a. Find the student with highest score\n");
            printf("b. Find the student with lowest score\n");
            printf("-> ");

            char choice[3];

            scanf("%s", choice);
            printf("Command: %s\n", choice);

            while (1)
            {
                if (strcmp(choice, "a") == 0)
                {
                    printf("The student with the highest score:\n");

                    float highest_score = -1.0;
                    int highest_score_index = 0;

                    for (int i = 0; i < num_students; i++)
                    {
                        float score = calc_average_mark(students[i].id, marks, num_marks, subjects, num_subjects);

                        if (score > highest_score)
                        {
                            highest_score = score;
                            highest_score_index = i;
                        }
                    }

                    print_student(students[highest_score_index]);
                    printf("== Average Mark: %.2f\n", highest_score);
                }
                else if (strcmp(choice, "b") == 0)
                {
                    printf("The student with the lowest score:\n");

                    float lowest_score = 11.0;
                    int lowest_score_index = 0;

                    for (int i = 0; i < num_students; i++)
                    {
                        float score = calc_average_mark(students[i].id, marks, num_marks, subjects, num_subjects);

                        if (score < lowest_score)
                        {
                            lowest_score = score;
                            lowest_score_index = i;
                        }
                    }

                    print_student(students[lowest_score_index]);
                    printf("== Average Mark: %.2f\n", highest_score);
                }
                else
                {
                    printf("Invalid choice.\n");
                    printf("-> ");
                    continue;
                }
                break;
            }

        }
        else if (strcmp(cmd, "3") == 0)
        {
            printf("Function: Show list of students eligible for graduation\n");
            for (int i = 0; i < num_students; i++)
            {
                int num_general_credits = calc_general_credits(students[i].id, marks, num_marks, subjects, num_subjects);
                int num_specialized_credits = calc_specialized_credits(students[i].id, marks, num_marks, subjects, num_subjects);

                printf("%d - %d\n", num_general_credits, num_specialized_credits);
                if (num_general_credits >= 30 && num_specialized_credits >= 70)
                {
                    print_student(students[i]);
                }
            }
        }
        else if (strcmp(cmd, "4") == 0)
        {
            printf("Quitting...\n");
            break;
        }
        else
        {
            printf("Invalid command.\n");
        }

        break;
    }

    printf("Done\n");
    printf("Goodbye\n");

    return 0;
}
