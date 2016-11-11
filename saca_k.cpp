#include "induced_sorting_0.hpp"
#include "induced_sorting_1.hpp"
#include "helper.hpp"
#include <cstring>
#include <cstdio>

void saca_k(char * T, int * SA, int K, int n, int n1, int level) {
	int * bkt;
	if (level == 0) {
		bkt = new int[K];
		calculate_bucket_end(T, bkt, K, n);
		induced_sort_LMS_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		calculate_bucket_start(T, bkt, K, n);
		induced_sort_L_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		calculate_bucket_end(T, bkt, K, n);
		induced_sort_S_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
	}

	// TODO

	if (level == 0) {
		calculate_bucket_end(T, bkt, K, n);
		induced_sort_SA_0(T, SA, bkt, n, n1);
		print_array(SA, n, "SA");
		calculate_bucket_start(T, bkt, K, n);
		induced_sort_L_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		calculate_bucket_end(T, bkt, K, n);
		induced_sort_S_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		delete [] bkt;
	}

	return;
}

int main() {
	int SA[] = { EMPTY, EMPTY, EMPTY, EMPTY, 2, 2, 3, 0 };
	induced_sort_LMS_1(SA, 8, 4);
	print_array(SA, 8, "SA");
	induced_sort_L_1(SA, 8, 4);
	print_array(SA, 8, "SA");
	induced_sort_S_1(SA, 8, 4);
	print_array(SA, 8, "SA");
	//saca_k(T, SA, 127, 8, 0, 0);
	return 0;
}