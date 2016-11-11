#ifndef HELPER_H
#define HELPER_H

extern int EMPTY;

void fill_array(int * arr, int start, int end, int value);

void calculate_bucket_start(char * T, int * bkt, int K, int n);

void calculate_bucket_end(char * T, int * bkt, int K, int n);

void print_array(int * arr, int n, char * name);

#endif