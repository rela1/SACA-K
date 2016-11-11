#include "helper.hpp"
#include <cstdio>

void store_suffix_empty(int * SA, int n1, int i, int c, int direction) {
    int neighbour = c + direction;
    if(neighbour < n1 && SA[neighbour] == EMPTY) {
        SA[neighbour] = i;
        SA[c] = -1;
    } else {
        SA[c] = i;
    }
}

void shift(int * SA, int start, int direction) {
    int neighbour_item = 0;
    do {
        int neighbour_item_index = start - direction;
        neighbour_item = SA[neighbour_item_index];
        SA[neighbour_item_index] = SA[start];
        start -= direction;
    } while (neighbour_item >= 0);
}

void store_suffix(int * SA, int n1, int i, int c, int direction) {
    fflush(stdout);
    printf("i=%d, SA_i=%d, c=%d, SA_c=%d\n", i, SA[i], c, SA[c]);
    int SA_c = SA[c];
    if(SA_c == EMPTY) {
        store_suffix_empty(SA, n1, i, c ,direction);
    } else if(SA_c >= 0) {
        shift(SA, c, direction);
        store_suffix_empty(SA, n1, i, c, direction);
    } else {
        int pos = c - SA_c * direction + direction;
        if(SA[pos] == EMPTY) {
            SA[pos] = i;
            SA[c] -= 1;
        } else {
            shift(SA, pos - direction, direction);
            SA[pos - direction] = i;
        }
    }
}

void induced_sort_LMS_1(int * SA, int n, int n1) {
    fill_array(SA, 0, n1, EMPTY);

    // find LMS substrings
	bool last_char_s = false;
    
    int length = n - n1;

    SA[0] = n1 - 1;
    int offset = n1 - 1;
	for(int i = n - 3; i >= length; --i) {
		if (last_char_s) {
			if (SA[i] > SA[i + 1]) {
				last_char_s = false;
				printf("i=%d, SA_i=%d, SA_i1=%d, offset=%d\n", i, SA[i], SA[i + 1], i - n1);
                store_suffix(SA, n1, i - offset, SA[i + 1], -1);
            }
		} else if (SA[i] < SA[i + 1]) {
			last_char_s = true;
		} else {
			last_char_s = false;
		}
	}
    return;
}

void induced_sort_SA_1(int * SA, int n, int n1) {
    fill_array(SA, n1, n, EMPTY);

    for(int i = n1 - 1; i >= 0; --i) {
        int j = SA[i];
        int c = SA[n - n1 + j];
        store_suffix(SA, n1, j, c, -1);
        SA[i] = EMPTY;
    }
}

void induced_sort_S_1(int * SA, int n, int n1) {
    printf("S sort\n");
    fflush(stdout);
    for(int i = n1 - 1, offset = n - n1; i >= 0; i--) {
        int SA_i = SA[i];
        if(SA_i > 0) {
            int j = SA[i] - 1;
            int T_j = SA[offset + j];
            int T_SA_i = SA[offset + SA_i];
            if((T_j < T_SA_i) || (T_j == T_SA_i && T_j > i)) {
                store_suffix(SA, n1, j, T_j, -1);
            }
        }
    }
    return;
}

void induced_sort_L_1(int * SA, int n, int n1) {
    printf("L sort\n");
    fflush(stdout);
    for(int i = 0, offset = n - n1, length = n1 - 1; i < length; i++) {
        int SA_i = SA[i];
        if(SA_i > 0) {
            int j = SA_i - 1;
            int T_j = SA[offset + j];
            if(T_j >= SA[offset + j + 1]) {
                store_suffix(SA, n1, j, T_j, 1);
            }
        }
    }
    return;
}