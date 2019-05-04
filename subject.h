#ifndef SUBJECT_H
#define SUBJECT_H

#include "datafile.h"

struct Subject
{
    char id[7];
    char name[128];
    char type[12];
    char major[64];
    int  credits;
};

void load_subjects(struct DataFile subject_file, struct Subject subjects[], int num_subjects);
void print_subject(struct Subject subject);
int  get_num_credits(char* subject_id, struct Subject subjects[], int num_subjects);
int get_num_general_credits(char* subject_id, struct Subject subjects[], int num_subjects);
int  is_general_subject(char* subject_id, struct Subject subjects[], int num_subjects);

#endif // SUBJECT_H

