#include "induced_sorting_0.hpp"
#include "induced_sorting_1.hpp"
#include "lms_naming.hpp"
#include "saca_k.hpp"
#include "helper.hpp"
#include <cstdio>

void saca_k(char * T, int * SA, int K, int n) {
	int * bkt = new int[K];
	calculate_bucket_end(T, bkt, K, n);
	print_array(bkt, K, "bkt");
	induced_sort_LMS_0(T, SA, bkt, n);
	print_array(SA, n, "SA_LMS");
	calculate_bucket_start(T, bkt, K, n);
	print_array(bkt, K, "bkt");
	induced_sort_L_0(T, SA, bkt, n);
	print_array(SA, n, "SA_L");
	calculate_bucket_end(T, bkt, K, n);
	print_array(bkt, K, "bkt");
	induced_sort_S_0(T, SA, bkt, n);
	print_array(SA, n, "SA_S");

	int lms_count = count_and_set_lms(T, n);
	compact_lms(SA, T, n);
	print_array(SA, n, "SA_comp");
	int unique_lms_ranks = reduce_string(SA, T, n, lms_count);
	print_array(SA, n, "SA_red");
	unset_lms(T, n);
	int * T_1 = SA + n - lms_count;
	printf("%d %d\n", lms_count, unique_lms_ranks);
	if (unique_lms_ranks == lms_count) {
		for(int i = 0; i < lms_count; ++i) {
			SA[T_1[i]] = i;
		}
	} else {
		saca_k_1(T_1, SA, lms_count);
	}

	induce_lms(SA, T_1, lms_count, T, n);
	calculate_bucket_end(T, bkt, K, n);
	induced_sort_SA_0(T, SA, bkt, n, lms_count);
	calculate_bucket_start(T, bkt, K, n);
	induced_sort_L_0(T, SA, bkt, n);
	calculate_bucket_end(T, bkt, K, n);
	induced_sort_S_0(T, SA, bkt, n);
	delete [] bkt;
}

void saca_k_1(int * T, int * SA, int n) {
	induced_sort_LMS_1(T, SA, n);
	induced_sort_L_1(T, SA, n);
	induced_sort_S_1(T, SA, n);

	int lms_count = count_and_set_lms(T, n);

	compact_lms(SA, T, n);
	int unique_lms_ranks = reduce_string(SA, T, n, lms_count);
	unset_lms(T, n);
	int * T_1 = SA + n - lms_count;
	if (unique_lms_ranks == lms_count) {
		for(int i = 0; i < lms_count; ++i) {
			SA[T_1[i]] = i;
		}
	} else {
		saca_k_1(T_1, SA, lms_count);
	}

	induce_lms(SA, T_1, lms_count, T, n);
	induced_sort_SA_1(T, SA, n, lms_count);
	induced_sort_L_1(T, SA, n);
	induced_sort_S_1(T, SA, n);
}