#include "helper.hpp"
#include <cstdio>

void induced_sort_LMS_0(char * T, int * SA, int * bkt, int n) {
	// SA is expected to be filled with -1 with memset
	// bkt is expected to point to end of each bucket
	fill_array(SA, 0, n, -1);
	calculate_bucket_end(T, bkt, K, n);
	print_array(SA, n, "SA");
	print_array(bkt, K, "bkt");

	// find LMS substrings
	bool last_char_s = true;
	for(int i = n - 2; i >= 0; --i) {
		if (last_char_s) {
			if (T[i] > T[i + 1]) {
				last_char_s = false;
				SA[bkt[T[i + 1]]--] = i + 1;
			}
		} else if (T[i] < T[i + 1]) {
			last_char_s = true;
		} else {
			last_char_s = false;
		}
	}

	return;
}

void induced_sort_SA_0(char * T, int * SA, int * bkt, int n, int n1) {
	// SA is expected to be filled with -1 from n1 to n-1
	// bkt is expected to point to end of each bucket
	fill_array(SA, n1, n, -1);
	calculate_bucket_end(T, bkt, K, n);

	// induced sort suffixes
	for (int i = n1 - 1; i >= 0; --i) {
		int j = SA[i];
		char c_j = T[j];
		SA[i] = -1;
		SA[bkt[c_j]--] = j;
	}

	return;
}

void induced_sort_L_0(char * T, int * SA, int * bkt, int n) {
	// SA is expected to hold indexes of sorted LMS substrings, all other elements are -1
	// bkt is expected to point to start of each bucket
	calculate_bucket_start(T, bkt, K, n);
	print_array(bkt, K, "bkt");

	// sort L suffixes
	for(int i = 0; i < n; ++i) {
		int SA_i = SA[i];
		if (SA_i > 0) {
			int j = SA_i - 1;
			char c_j = T[j];
			if (c_j >= T[SA_i]) {
				SA[bkt[c_j]++] = j;
			}
		}
	}

	return;
}

void induced_sort_S_0(char * T, int * SA, int * bkt, int n) {
	// SA is expected to hold indexes of sorted LMS substrings and L suffixes, all other elements are -1
	// bkt is expected to point to end of each bucket
	calculate_bucket_end(T, bkt, K, n);
	print_array(bkt, K, "bkt");

	// sort R suffixes
	for(int i = n - 1; i >= 0; --i) {
		int SA_i = SA[i];
		if (SA_i > 0) {
			int j = SA_i - 1;
			char c_j = T[j];
			char c_SA_i = T[SA_i];
			if (c_j < c_SA_i || (c_j == c_SA_i && bkt[c_j] < i)) {
				SA[bkt[c_j]--] = j;
			}
		}
	}

	return;
}