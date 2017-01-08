#include "lms_naming.hpp"

int reduce_string_1(int *SA, int n, int n1, int lms_count){


	return 0;
}

int reduce_string_0(int *SA, char *T, int n, int lms_count){
	int last_lms_start = n - 1;
	int last_lms_length = 1;
	int current_lms_rank = 1;
	int index = n - lms_count;
	SA[index++] = 0;
	for(int i = 1; i < lms_count; ++i) {
		int T_index = SA[i];
		int lms_length = get_lms_length_0(T_index, T);
		if (last_lms_length != lms_length) {
			SA[index++] = current_lms_rank++;
		} else {
			bool lms_substrings_equal = true;
			for(int j = 0; j < lms_length; ++j) {
				if (T[last_lms_start + j] != T[T_index + j]) {
					lms_substrings_equal = false;
					break;
				}
			}
		}
	}
	return 0;
}

int count_and_set_lms_0(char * T, int n){
	int count = 1;
	// find LMS substrings
	bool last_char_s = false;
	for(int i = n - 3; i >= 0; --i) {
		if (last_char_s) {
			if (T[i] > T[i + 1]) {
				last_char_s = false;
				T[i + 1] = -T[i + 1];
				count++;
			}
		} else if (T[i] < T[i + 1]) {
			last_char_s = true;
		} else {
			last_char_s = false;
		}
	}
	return count;
}

int count_and_set_lms_1(int * SA, int n, int n1){
	int count = 1;
	// find LMS substrings
	bool last_char_s = false;
	for(int i = n - 3; i >= n - n1; --i) {
		if (last_char_s) {
			if (SA[i] > SA[i + 1]) {
				last_char_s = false;
				SA[i + 1] = -SA[i + 1];
				count++;
			}
		} else if (SA[i] < SA[i + 1]) {
			last_char_s = true;
		} else {
			last_char_s = false;
		}
	}
	return count;
}

void compact_SA_0(int * SA, char * T, int n){
	int index = 1;
	SA[0] = n - 1;
	for(int i = 1; i < n; ++i){
		int T_index = SA[i];
		if(T[T_index] < 0){
			SA[index++] = T_index;
		} 
	}
}

void compact_SA_1(int * SA, int n, int n1){
	int index = 1;
	SA[0] = n1 - 1;
	for(int i = 1; i < n1; ++i){
		int T_index = SA[i];
		if(SA[n - n1 + T_index] < 0){
			SA[index++] = T_index;
		} 
	}
}

int get_lms_length_0(int start_index, char * T) {
	int length = 2;
	start_index++;
	while (T[start_index++] > 0) length++;
	return length;
}

int get_lms_length_1(int start_index, int * SA, int n, int n1) {
	int length = 2;
	start_index = n - n1 + start_index + 1;
	while (SA[start_index++] > 0) length++;
	return length;
}