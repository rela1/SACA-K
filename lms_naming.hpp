#include "helper.hpp"

#ifndef LMS_NAMING_H
#define LMS_NAMING_H

template <typename type>
int reduce_string(int * SA, type T, int n, int lms_count);

template <typename type>
int count_and_set_lms(type T, int n);

template <typename type>
void unset_lms(type T, int n);

template <typename type>
void compact_lms(int * SA, type T, int n);

template <typename type>
bool lms_substrings_equal(int lms1_start_index, int lms2_start_index, int lms_length, type T);

template <typename type>
int get_lms_length(int start_index, type T);

template <typename type>
int reduce_string(int * SA, type T, int n, int lms_count) {
	int last_lms_start = n - 1;
	int last_lms_length = 1;
	int current_lms_rank = 0;
	int unique_lms_ranks = 0;
	int lms_start_pos = n - n / 2;
	for(int i = lms_start_pos; i < n; ++i) {
		SA[i] = EMPTY;
	}
	SA[n - 1] = current_lms_rank;
	SA[0] = 1;
	unique_lms_ranks++;
	for(int i = 1; i < lms_count; ++i) {
		int T_index = SA[i];
		int lms_length = get_lms_length(T_index, T);
		int lms_position = lms_start_pos + (T_index - n % 2) / 2;
		if (last_lms_length == lms_length && lms_substrings_equal(last_lms_start, T_index, lms_length, T)) {
			SA[lms_position] = current_lms_rank;
			SA[current_lms_rank]++;
		} else {
			current_lms_rank += SA[current_lms_rank];
			SA[current_lms_rank] = 1;
			SA[lms_position] = current_lms_rank;
			unique_lms_ranks++;
		}
		last_lms_start = T_index;
		last_lms_length = lms_length;
	}
	int shift_count = 0;
	for(int i = n - 2; i >= lms_start_pos; --i) {
		if (SA[i] == EMPTY) {
			shift_count++;
		} else {
			SA[i + shift_count] = SA[i];
		}
	}
	bool last_char_s_type = false;
	for (int i = n - 3, limit = n - lms_count; i >= limit; --i) {
		bool this_char_s_type = (T[i] < T[i + 1] || (T[i] == T[i + 1] && last_char_s_type)) ? true : false;
		if (this_char_s_type) {
			int lms_rank = SA[i];
			int lms_count = SA[lms_rank];
			SA[i] += (lms_count - 1);
		}
		last_char_s_type = this_char_s_type;
	}
	return unique_lms_ranks;
}

template <typename type>
int count_and_set_lms(type T, int n) {
	int count = 1;
	bool last_char_s_type = false;
	for (int i = n - 3; i >= 0; --i) {
		bool this_char_s_type = (T[i] < T[i + 1] || (T[i] == T[i + 1] && last_char_s_type)) ? true : false;
		if (!this_char_s_type && last_char_s_type) {
			T[i + 1] = - T[i + 1];
			count++;
		}
		last_char_s_type = this_char_s_type;
	}
	return count;
}

template <typename type>
void unset_lms(type T, int n) {
	for (int i = n - 3; i >= 0; --i) {
		if (T[i] < 0) {
			T[i] = - T[i];
		}
	}
}

template <typename type>
void compact_lms(int * SA, type T, int n) {
	SA[0] = n - 1;
	int index = 1;
	for(int i = 1; i < n; ++i) {
		int T_index = SA[i];
		if (T[T_index] < 0) {
			SA[index++] = T_index;
		}
	}
}

template <typename type>
bool lms_substrings_equal(int lms1_start_index, int lms2_start_index, int lms_length, type T) {
	for(int i = 0; i < lms_length; ++i) {
		if (T[lms1_start_index + i] != T[lms2_start_index + i]) return false;
	}
	return true;
}

template <typename type>
int get_lms_length(int start_index, type T) {
	int length = 2;
	start_index++;
	while(T[start_index++] > 0) length++;
	return length;
}

template <typename type>
void induce_lms(int * SA, int * T_1, int lms_count, type T, int n) {
	int index = lms_count - 2;
	bool last_char_s_type = false;
	for (int i = n - 3; i >= 0; --i) {
		bool this_char_s_type = (T[i] < T[i + 1] || (T[i] == T[i + 1] && last_char_s_type)) ? true : false;
		if (!this_char_s_type && last_char_s_type) {
			T_1[index--] = i + 1;
		}
		last_char_s_type = this_char_s_type;
	}
	for(int i = 1; i < lms_count; ++i) {
		SA[i] = T_1[SA[i]];
	}
}

#endif