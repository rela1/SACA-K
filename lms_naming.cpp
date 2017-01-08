int reduce_string_1(int *SA, int n, int n1){


	return 0;
}

int reduce_string_0(int *SA, char *T, int n){
	

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