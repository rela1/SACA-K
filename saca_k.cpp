#include "induced_sorting_0.hpp"
#include <cstring>
#include <cstdio>

void fill_array(int * arr, int n, int value) {
	for(int i = 0; i < n; ++i) {
		arr[i] = value;
	}
}

void calculate_bucket_start(char * T, int * bkt, int K, int n) {
	fill_array(bkt, K, 0);
	for(int i = 0; i < n; ++i) {
		bkt[T[i]]++;
	}
	int current_index = 0;
	for(int i = 0; i < K; ++i) {
		int char_number = bkt[i];
		bkt[i] = current_index;
		current_index += char_number;
	}

	return;
}

void calculate_bucket_end(char * T, int * bkt, int K, int n) {
	fill_array(bkt, K, 0);
	for(int i = 0; i < n; ++i) {
		bkt[T[i]]++;
	}
	int current_index = -1;
	for(int i = 0; i < K; ++i) {
		current_index += bkt[i];
		bkt[i] = current_index;
	}

	return;
}

void print_array(int * arr, int n, char * name) {
	printf("%s={", name);
	for(int i = 0, length = n -1; i < length; ++i) {
		printf("%d, ", arr[i]);
	}
	printf("%d}\n", arr[n - 1]);
	return;
}

void saca_k(char * T, int * SA, int K, int n, int level) {
	int * bkt;
	if (level == 0) {
		bkt = new int[K];
		fill_array(bkt, K, 0);
		fill_array(SA, n, -1);
		print_array(SA, n, "SA");
		calculate_bucket_end(T, bkt, K, n);
		print_array(bkt, K, "bkt");
		induced_sort_LMS_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		calculate_bucket_start(T, bkt, K, n);
		print_array(bkt, K, "bkt");
		induced_sort_L_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		calculate_bucket_end(T, bkt, K, n);
		print_array(bkt, K, "bkt");
		induced_sort_S_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
	}

	// TODO

	if (level == 0) {
		delete [] bkt;
	}
}

int main() {
	char T[] = {'c', 'a', 'b', 'b', 'a', 'g', 'e', '\0', '\0'};
	int SA[8];
	printf("sizeof SA %ld\n", sizeof(SA));
	saca_k(T, SA, 127, 8, 0);
	return 0;
}