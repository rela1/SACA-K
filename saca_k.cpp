#include "induced_sorting_0.hpp"
#include "induced_sorting_1.hpp"
#include "helper.hpp"
#include "lms_naming.hpp"
#include "saca_k.hpp"
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstring>

void saca_k(char * T, int * SA, int K, int n) {
	int * bkt = new int[K];
	calculate_bucket_end(T, bkt, K, n);
	induced_sort_LMS_0(T, SA, bkt, n);
	calculate_bucket_start(T, bkt, K, n);
	induced_sort_L_0(T, SA, bkt, n);
	calculate_bucket_end(T, bkt, K, n);
	induced_sort_S_0(T, SA, bkt, n);

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

bool test_suffixes(char * T, int s1_start, int s2_start, int n) {
	int cmp = strcmp(T + s1_start, T + s2_start);
	return cmp < 0;
}

int main() {
	const char * test_ = "abracadabra0AbRa4Cad14abra";
	char test[strlen(test_) + 1];
	for(int i = 0; i < strlen(test_); ++i) {
		test[i] = test_[i];
	}
	test[strlen(test_)] = 0;
	int n = strlen(test) + 1;
	int sa[n];
	printf("%s\n", test);
	saca_k(test, sa, 128, n);
	for(int i = 0; i < n; ++i) {
		printf("%d, ", sa[i]);
	}
	for(int i = 0; i < n; ++i) {
		int ind = sa[i];
		printf("%s\n", test + ind);
	}
	for(int i = 0; i < n - 1; ++i) {
		if (!test_suffixes(test, sa[i], sa[i + 1], n)) printf("test error: SA[%d]=%d, SA[%d]=%d, suffix(%s)>suffix(%s)\n", i, sa[i], i+1, sa[i+1], test + sa[i], test + sa[i+1]);
	}
}