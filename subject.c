#include "subject.h"
#include "datafile.h"
#include <stdlib.h>
#include <string.h>

void load_subjects(struct DataFile subject_file, struct Subject subjects[], int num_subjects)
{
    char row[5][128];
    parse_row(subject_file.ptr, row, subject_file.num_cols);

    for (int i = 0; i < num_subjects; i++)
    {
        parse_row(subject_file.ptr, row, subject_file.num_cols);

        strcpy(subjects[i].id, row[0]);
        strcpy(subjects[i].name, row[1]);
        strcpy(subjects[i].type, row[2]);
        strcpy(subjects[i].major, row[3]);
        subjects[i].credits = atoi(row[4]);
    }
}

void print_subject(struct Subject subject)
{
    printf("ID: %s - ", subject.id);
    printf("Name: %s - ", subject.name);
    printf("Type: %s - ", subject.type);
    printf("Major: %s - ", subject.major);
    printf("Credits: %d\n", subject.credits);
}

int get_num_credits(char* subject_id, struct Subject subjects[], int num_subjects)
{
    for (int i = 0; i < num_subjects; i++)
    {
        if (strcmp(subjects[i].id, subject_id) == 0)
        {
            return subjects[i].credits;
        }
    }

    return 0;
}

int get_num_general_credits(char* subject_id, struct Subject subjects[], int num_subjects)
{
    for (int i = 0; i < num_subjects; i++)
    {
        if (strcmp(subjects[i].id, subject_id) == 0 && strcmp(subjects[i].type, "general"))
        {
            return subjects[i].credits;
        }
    }

    return 0;
}

int is_general_subject(char* subject_id, struct Subject subjects[], int num_subjects)
{
    for (int i = 0; i < num_subjects; i++)
    {
        if (strcmp(subject_id, subjects[i].id) == 0)
        {
            if (strcmp(subjects[i].type, "general"))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    return 0;
}
