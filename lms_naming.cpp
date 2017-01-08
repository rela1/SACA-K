#include "lms_naming.hpp"
#include "helper.hpp"

int reduce_string_1(int *SA, int n, int n1, int lms_count){


	return 0;
}

int reduce_string_0(int *SA, char *T, int n, int lms_count){
	int last_lms_start = n - 1;
	int last_lms_length = 1;
	int current_lms_rank = 0;
	int n1 = n - n / 2;
	for(int i = n1; i < n; ++i) {
		SA[i] = EMPTY;
	}
	SA[n - 1] = current_lms_rank;
	SA[0] = 1;
	for(int i = 1; i < lms_count; ++i) {
		int T_index = SA[i];
		int lms_length = get_lms_length_0(T_index, T);
		int lms_position = n1 + (T_index - n % 2) / 2;
		if (last_lms_length == lms_length && lms_substrings_equal_0(last_lms_start, T_index, lms_length)) {
			SA[lms_position] = current_lms_rank;
			SA[current_lms_rank]++;
		} else {
			current_lms_rank++;
			SA[current_lms_rank] = 1;
			SA[lms_position] = current_lms_rank;
		}
	}
	int shift_count = 0;
	for(int i = n - 2; i >= n1; --i) {
		if (SA[i] == EMPTY) {
			shift_count++;
		} else {
			SA[i + shift_count] = SA[i];
		}
	}
	bool last_char_s = false;
	for(int i = n - 3, limit = n - lms_count; i >= limit; --i) {
		if (SA[i] < SA[i + 1] || (SA[i] == SA[i + 1] && last_char_s)) {
			int lms_rank = SA[i];
			int lms_count = SA[lms_rank];
			SA[i] = 
			last_char_s = true;
		} else {
			last_char_s = false;
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

bool lms_substrings_equal_0(int last_lms_start_index, int this_lms_start_index, int lms_length) {
	for(int j = 0; j < lms_length; ++j) {
		if (T[last_lms_start + j] != T[T_index + j]) {
			return false;
		}
	}
	return true;
}