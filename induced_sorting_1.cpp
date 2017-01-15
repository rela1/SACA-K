#include "helper.hpp"
#include <cstdio>

/**
    Used for storing the suffix on empty place in suffix array.

    @param SA output array for storing the suffix array
    @param n size of input and output arrays
    @param i index to be stored
    @param c bucket start/end depending on type of suffix that is to be stored
    @param direction direction where to go while storing suffixes - direction is 1 for storing the S type sufixes and it's 0 for storing the L type suffixes
    @author Goran Golub, Ivan Relic
*/
void store_suffix_empty(int * SA, int n, int i, int c, int direction) {
    int neighbour = c + direction;
    if(neighbour < n && neighbour > 0 && SA[neighbour] == EMPTY) {
        SA[neighbour] = i;
        SA[c] = -1;
    } else {
        SA[c] = i;
    }
}
/**
    Used for shifting the elements in given suffix array from the start in the oposite of given directon.

    @param SA output array for storing the suffix array
    @param start starting index
    @param direction direction where to shift - 1 for left shift, -1 for right shift
    @return returns index of element that was last shifted
    @author Goran Golub, Ivan Relic
*/
int shift(int * SA, int start, int direction) {
    int index = start;
    int previous_item = SA[index];
    int neighbour_item = 0;
    do {
        index -= direction;
        neighbour_item = SA[index];
        SA[index] = previous_item;
        previous_item = neighbour_item;
    } while (neighbour_item >= 0);
    SA[start] = EMPTY;
    return index;
}

/**
    Used for storing of the suffix. Type of suffix is determined by direction.

    @param SA output array for storing the suffix array
    @paramn n size of output suffix array
    @param i index to be stored
    @param c bucket start/end depending on type of suffix that is to be stored
    @param direction direction where to go while storing suffixes - direction is 1 for storing the S type sufixes and it's 0 for storing the L type suffixes
    @return returns index of element that was last shifted; it there was no shifting, return value is -1
    @author Goran Golub, Ivan Relic
*/
int store_suffix(int * SA, int n, int i, int c, int direction) {
    int SA_c = SA[c];
    if(SA_c == EMPTY) {
        store_suffix_empty(SA, n, i, c ,direction);
        return -1;
    } else if(SA_c >= 0) {
        int final_index = shift(SA, c, direction);
        store_suffix_empty(SA, n, i, c, direction);
        return final_index;
    } else {
        int pos = c - SA_c * direction + direction;
        if(SA[pos] == EMPTY) {
            SA[pos] = i;
            SA[c] -= 1;
            return -1;
        } else {
            int final_index = shift(SA, pos - direction, direction);
            SA[pos - direction] = i;
            return final_index;
        }
    }
}

/**
    Used for inducing the sort of the LMS substrings.

    @param T input array
    @param SA output array for storing the suffix array
    @param n size of input and output arrays
    @author Goran Golub, Ivan Relic
*/
void induced_sort_LMS_1(int * T, int * SA, int n) {
    fill_array(SA, 0, n, EMPTY);
    SA[0] = n - 1;
    bool last_char_s_type = false;
    int T_i_1 = T[n - 2];
    for (int i = n - 3; i >= 0; --i) {
        int T_i = T[i];
        bool this_char_s_type = (T_i < T_i_1 || (T_i == T_i_1 && last_char_s_type)) ? true : false;
        if (!this_char_s_type && last_char_s_type) {
            store_suffix(SA, n, i+1, T_i_1, -1);
        }
        last_char_s_type = this_char_s_type;
        T_i_1 = T_i;
    }
    for(int i = 1; i < n; ++i) {
        int SA_i = SA[i];
        if (SA_i < 0 && SA_i != EMPTY) {
            int count = i + SA_i;
            for (int j = i; j > count; --j) {
                SA[j] = SA[j - 1];
            }
            SA[count] = EMPTY;
        }
    }
}

/**
    Used for putting the sorted LMS-substrings in ther correct bucket in suffix array.

    @param T input array
    @param SA output array for storing the suffix array
    @param n size of input and output arrays
    @param lms_count size of reduced string
    @author Goran Golub, Ivan Relic
*/
void induced_sort_SA_1(int * T, int * SA, int n, int lms_count) {
    fill_array(SA, lms_count, n, EMPTY);
    SA[0] = n - 1;
    int bucket = 0, index = 0;
    for(int i = lms_count - 1; i > 0; --i) {
        int j = SA[i];
        SA[i] = EMPTY;
        int c_j = T[j];
        if (c_j == bucket) {
            index--;
        } else {
            bucket = c_j;
            index = bucket;
        }
        SA[index] = j;
    }
}

/**
    Used for inducing the sort of the S type suffixes.

    @param T input array
    @param SA output array for storing the suffix array
    @param n size of input and output arrays
    @author Goran Golub, Ivan Relic
*/
void induced_sort_S_1(int * T, int * SA, int n) { 
    for(int i = n - 1; i >= 0; --i) {
        int SA_i = SA[i];
        if(SA_i > 0) {
            int j = SA[i] - 1;
            int T_j = T[j];
            int T_SA_i = T[SA_i];
            if((T_j < T_SA_i) || (T_j == T_SA_i && T_j > i)) {
                int final_index = store_suffix(SA, n, j, T_j, -1);
                if (final_index != -1 && final_index > i) {
                    i++;
                }
            }
        }
    }
}

/**
    Used for inducing the sort of the L type suffixes.

    @param T input array
    @param SA output array for storing the suffix array
    @param n size of input and output arrays
    @author Goran Golub, Ivan Relic
*/
void induced_sort_L_1(int * T, int * SA, int n) {
    for(int i = 0; i < n; ++i) {
        int SA_i = SA[i];
        if(SA_i > 0) {
            int j = SA_i - 1;
            int T_j = T[j];
            int T_SA_i = T[SA_i];
            if(T_j >= T_SA_i) {
                int final_index = store_suffix(SA, n, j, T_j, 1);
                int T_SA_i_1 = T[SA_i + 1];
                bool isLType=(SA_i < n-1) && (T_SA_i>T_SA_i_1 || (T_SA_i == T_SA_i_1 && T_SA_i < i));
                if (!isLType && i > 0) {
                    SA[i] = EMPTY;
                }
                if (final_index != -1 && final_index < i) {
                    i--;
                }
            }
        }
    }
    for(int i = 1; i < n; ++i) {
        int SA_i = SA[i];
        if (SA_i < 0 && SA_i != EMPTY) {
            int count = i - SA_i;
            for (int j = i; j < count; ++j) {
                SA[j] = SA[j + 1];
            }
            SA[count] = EMPTY;
        }
    }
}