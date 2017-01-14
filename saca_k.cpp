#include "induced_sorting_0.hpp"
#include "induced_sorting_1.hpp"
#include "helper.hpp"
#include "lms_naming.hpp"
#include "saca_k.hpp"
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstring>
#include "test_helper.hpp"

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
	//print_array(T_1, lms_count, "T1");
	if (unique_lms_ranks == lms_count) {
		for(int i = 0; i < lms_count; ++i) {
			SA[T_1[i]] = i;
		}
	} else {
		saca_k_1(T_1, SA, lms_count);
	}

	//print_array(SA, n, "SA");

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
	printf("level++ n=%d\n", n);
	fflush(stdout);
	induced_sort_LMS_1(T, SA, n);
	//print_array(SA, n, "SA_LMS");
	induced_sort_L_1(T, SA, n);
	//print_array(SA, n, "SA_L");
	induced_sort_S_1(T, SA, n);

	//print_array(SA, n, "SA_S");
	//print_array(SA, n, "SA");

	//print_array(T, n, "T_before_set");
	int lms_count = count_and_set_lms(T, n);
	//print_array(T, n, "T_after_set");
	printf("lms count %d\n", lms_count);
	fflush(stdout);
	compact_lms(SA, T, n);
	printf("compact\n");
	fflush(stdout);
	int unique_lms_ranks = reduce_string(SA, T, n, lms_count);
	printf("reduce\n");
	fflush(stdout);
	unset_lms(T, n);
	int * T_1 = SA + n - lms_count;
	if (unique_lms_ranks == lms_count) {
		for(int i = 0; i < lms_count; ++i) {
			SA[T_1[i]] = i;
		}
	} else {
		saca_k_1(T_1, SA, lms_count);
	}

	//print_array(SA, n, "SA");	
	induce_lms(SA, T_1, lms_count, T, n);
	printf("induce\n");
	fflush(stdout);
	induced_sort_SA_1(T, SA, n, lms_count);
	printf("induce SA\n");
	//print_array(SA, n, "SA");	
	fflush(stdout);
	induced_sort_L_1(T, SA, n);
	printf("L\n");
	//print_array(SA, n, "SA");	
	fflush(stdout);
	induced_sort_S_1(T, SA, n);
	printf("S\n");
	fflush(stdout);
}

bool test_suffixes(char * T, int s1_start, int s2_start, int n) {
	int cmp = strcmp(T + s1_start, T + s2_start);
	return cmp < 0;
}

int main() {
/*
	const char * test_ = "baabaabac";
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
	printf("\n");
	for(int i = 0; i < n; ++i) {
		int ind = sa[i];
		printf("suffix %d = %s\n", i, test + ind);
	}
	for(int i = 0; i < n - 1; ++i) {
		if (!test_suffixes(test, sa[i], sa[i + 1], n)) printf("test error: SA[%d]=%d, SA[%d]=%d, suffix(%s)>suffix(%s)\n", i, sa[i], i+1, sa[i+1], test + sa[i], test + sa[i+1]);
	}

	long t1 = time(NULL);
	if (test_random_sa(1, 500000000)) {
		printf("POLOŽIO BOGU U OVOLKO MILISEKUNDI:%ld\n", (time(NULL) - t1));
	}
*/
	test_create_sa_from_file("test.txt");
}