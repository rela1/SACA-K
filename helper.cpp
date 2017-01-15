#include <cstdio>

int EMPTY = 1 << ((sizeof(int) * 8) - 1);

/**
    Used for filling the array with given value.

    @param arr array to be filled
    @param start starting index of array
    @param end ending index of array, not included
    @param value value that array will be filled with
    @author Ivan Relic
*/
void fill_array(int * arr, int start, int end, int value) {
	for(int i = start; i < end; ++i) {
		arr[i] = value;
	}

	return;
}

/**
    Used for calculating the start of the bucket.

    @param T input array
    @param bkt bucket counter array
    @param K alphabet size
    @param n size of input array
    @author Ivan Relic
*/
void calculate_bucket_start(char * T, int * bkt, int K, int n) {
	fill_array(bkt, 0, K, 0);
	for(int i = 0; i < n; ++i) {
		bkt[T[i]]++;
	}
	int current_index = 0;
	for(int i = 0; i < K; ++i) {
		int char_number = bkt[i];
		bkt[i] = current_index;
		current_index += char_number;
	}

	return;
}

/**
    Used for calculating the end of the bucket.

    @param T input array
    @param bkt bucket counter array
    @param K alphabet size
    @param n size of input array
    @author Ivan Relic
*/
void calculate_bucket_end(char * T, int * bkt, int K, int n) {
	fill_array(bkt, 0, K, 0);
	for(int i = 0; i < n; ++i) {
		bkt[T[i]]++;
	}
	int current_index = -1;
	for(int i = 0; i < K; ++i) {
		current_index += bkt[i];
		bkt[i] = current_index;
	}

	return;
}

/**
    Used for printing the data in array.

    @param arr array to be printed
    @param n size of given array
    @param name name of the array
    @author Ivan Relic
*/
void print_array(int * arr, int n, const char * const name) {
	printf("%s={", name);
	for(int i = 0, length = n -1; i < length; ++i) {
		printf("%d, ", arr[i]);
	}
	printf("%d}\n", arr[n - 1]);
	return;
}