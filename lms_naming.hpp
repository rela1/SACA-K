#ifndef LMS_NAMING_H
#define LMS_NAMING_H

int reduce_string_1(int *SA, int n, int n1, int lms_count);

int reduce_string_0(int *SA, char *T, int n, int lms_count);

int count_and_set_lms_0(char * T, int n);

int count_and_set_lms_1(int * SA, int n, int n1);

int get_lms_length_0(int start_index, char * T);

int get_lms_length_1(int start_index, int * SA, int n, int n1);

bool lms_substrings_equal_0(int last_lms_start_index, int this_lms_start_index, int lms_length);

void compact_SA_0(int * SA, char * T, int n);

void compact_SA_1(int * SA, int n, int n1);

#endif