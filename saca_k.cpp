#include "induced_sorting_0.hpp"
#include "induced_sorting_1.hpp"
#include "helper.hpp"
#include "lms_naming.hpp"
#include "saca_k.hpp"
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>

void saca_k(char * T, int * SA, int K, int n) {
	int * bkt = new int[K];
	calculate_bucket_end(T, bkt, K, n);
	induced_sort_LMS_0(T, SA, bkt, n);
	calculate_bucket_start(T, bkt, K, n);
	induced_sort_L_0(T, SA, bkt, n);
	calculate_bucket_end(T, bkt, K, n);
	induced_sort_S_0(T, SA, bkt, n);

	int lms_count = count_and_set_lms(T, n);
	printf("%s\n", T);
	compact_lms(SA, T, n);
	print_array(SA, n, "SA");
	int unique_lms_ranks = reduce_string(SA, T, n, lms_count);
	unset_lms(T, n);
	int * T_1 = SA + n - lms_count;

	printf("n=%d, lms count = %d, unique_lms=%d\n", n, lms_count, unique_lms_ranks);

	if (unique_lms_ranks == lms_count) {
		for(int i = 0; i < lms_count; ++i) {
			SA[T_1[i]] = i;
		}
	} else {
		saca_k_1(T_1, SA, lms_count);
	}
	print_array(SA, n, "SA");
	induce_lms(SA, T_1, lms_count, T, n);
	print_array(SA, n, "SA");
	printf("%s\n", T);

	calculate_bucket_end(T, bkt, K, n);
	induced_sort_SA_0(T, SA, bkt, n, lms_count);
	print_array(SA, n, "SA");
	calculate_bucket_start(T, bkt, K, n);
	induced_sort_L_0(T, SA, bkt, n);
	print_array(SA, n, "SA");
	calculate_bucket_end(T, bkt, K, n);
	induced_sort_S_0(T, SA, bkt, n);
	print_array(SA, n, "SA");
	delete [] bkt;
}

void saca_k_1(int * T, int * SA, int n) {
	printf("in lvl1\n");
	print_array(SA, n, "SA");
	print_array(T, n, "T");
	fflush(stdout);
	induced_sort_LMS_1(T, SA, n);
	induced_sort_L_1(T, SA, n);
	induced_sort_S_1(T, SA, n);

	int lms_count = count_and_set_lms(T, n);
	compact_lms(SA, T, n);
	int unique_lms_ranks = reduce_string(SA, T, n, lms_count);
	unset_lms(T, n);
	int * T_1 = SA + n - lms_count;
	printf("n=%d, lms count = %d, unique_lms=%d\n", n, lms_count, unique_lms_ranks);
	print_array(T_1, lms_count, "T_1");
	if (unique_lms_ranks == lms_count) {
		for(int i = 0; i < lms_count; ++i) {
			SA[T_1[i]] = i;
		}
	} else {
		saca_k_1(T_1, SA, lms_count);
	}
	print_array(SA, n, "SA");
	print_array(T, n, "T");
	induce_lms(SA, T_1, lms_count, T, n);
print_array(SA, n, "SA");
	print_array(T, n, "T");
	induced_sort_SA_1(T, SA, n, lms_count);
	print_array(SA, n, "SA");
	print_array(T, n, "T");
	induced_sort_L_1(T, SA, n);
	print_array(SA, n, "SA");
	print_array(T, n, "T");
	induced_sort_S_1(T, SA, n);
	print_array(SA, n, "SA");
	print_array(T, n, "T");
}

int main() {
	const char * test_ = "mmiissiissiippii";
	char test[strlen(test_) + 1];
	for(int i = 0; i < strlen(test_); ++i) {
		test[i] = test_[i];
	}
	test[strlen(test_)] = 0;
	int n = 17;
	int sa[n];
	printf("%s\n", test);
	saca_k(test, sa, 128, n);
	for(int i = 0; i < n; ++i) {
		printf("%d, ", sa[i]);
	}
	printf("\n");
	for(int i = 0; i < n; ++i) {
		int ind = sa[i];
		if (ind >= 0) {
			for(int j = ind; j < n; ++j) {
				printf("%c", test[j]);
			}
			printf("\n");
		}
	}
}