#include "helper.hpp"

void induced_sort_LMS_0(char * T, int * SA, int * bkt, int n) {
	// bkt is expected to point to end of each bucket
	fill_array(SA, 0, n, EMPTY);

	SA[0] = n - 1;
	bool last_char_s_type = false;
	for (int i = n - 3; i >= 0; --i) {
		bool this_char_s_type = (T[i] < T[i + 1] || (T[i] == T[i + 1] && last_char_s_type)) ? true : false;
		if (!this_char_s_type && last_char_s_type) {
			SA[bkt[T[i + 1]]--] = i + 1;
		}
		last_char_s_type = this_char_s_type;
	}
}

void induced_sort_SA_0(char * T, int * SA, int * bkt, int n, int lms_count) {
	// bkt is expected to point to end of each bucket
	fill_array(SA, lms_count, n, EMPTY);

	// induced sort suffixes
	SA[0] = n - 1;
	for (int i = lms_count - 1; i >= 1; --i) {
		int j = SA[i];
		char c_j = T[j];
		SA[i] = EMPTY;
		SA[bkt[c_j]--] = j;
	}
}

void induced_sort_L_0(char * T, int * SA, int * bkt, int n) {
	// SA is expected to hold indexes of sorted LMS substrings, all other elements are EMPTY
	// bkt is expected to point to start of each bucket
	
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
}

void induced_sort_S_0(char * T, int * SA, int * bkt, int n) {
	// SA is expected to hold indexes of sorted LMS substrings and L suffixes, all other elements are EMPTY
	// bkt is expected to point to end of each bucket

	// sort S suffixes
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
}