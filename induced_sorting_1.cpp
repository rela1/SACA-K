#include "helper.hpp"

void store_suffix_empty(int * SA, int n, int i, int c, int direction) {
    int neighbour = c + direction;
    if(neighbour < n && neighbour > 0 && SA[neighbour] == EMPTY) {
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

void store_suffix(int * SA, int n, int i, int c, int direction) {
    int SA_c = SA[c];
    if(SA_c == EMPTY) {
        store_suffix_empty(SA, n, i, c ,direction);
    } else if(SA_c >= 0) {
        shift(SA, c, direction);
        store_suffix_empty(SA, n, i, c, direction);
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

void induced_sort_LMS_1(int * T, int * SA, int n) {
    fill_array(SA, 0, n, EMPTY);

    SA[0] = n - 1;
    bool last_char_s_type = false;
    for (int i = n - 3; i >= 0; --i) {
        bool this_char_s_type = (T[i] < T[i + 1] || (T[i] == T[i + 1] && last_char_s_type)) ? true : false;
        if (!this_char_s_type && last_char_s_type) {
            store_suffix(SA, n, i, T[i], -1);
        }
        last_char_s_type = this_char_s_type;
    }
}

void induced_sort_SA_1(int * T, int * SA, int n, int lms_count) {
    fill_array(SA, n - lms_count, n, EMPTY);

    SA[0] = n - 1;
    for(int i = lms_count - 1; i >= 0; --i) {
        int j = SA[i];
        int c_j = T[j];
        SA[c_j] = j;//store_suffix(SA, n, j, c_j, -1);
        SA[i] = EMPTY;
    }
}

void induced_sort_S_1(int * T, int * SA, int n) {
    for(int i = n - 1; i >= 0; --i) {
        int SA_i = SA[i];
        if(SA_i > 0) {
            int j = SA[i] - 1;
            int T_j = T[j];
            int T_SA_i = T[SA_i];
            if((T_j < T_SA_i) || (T_j == T_SA_i && T_j > i)) {
                store_suffix(SA, n, j, T_j, -1);
            }
        }
    }
}

void induced_sort_L_1(int * T, int * SA, int n) {
    for(int i = 0; i < n; ++i) {
        int SA_i = SA[i];
        if(SA_i > 0) {
            int j = SA_i - 1;
            int T_j = T[j];
            if(T_j >= T[j + 1]) {
                store_suffix(SA, n, j, T_j, 1);
            }
        }
    }
}