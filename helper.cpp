void fill_array(int * arr, int start, int end, int value) {
	for(int i = start; i < end; ++i) {
		arr[i] = value;
	}

	return;
}

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

void print_array(int * arr, int n, char * name) {
	printf("%s={", name);
	for(int i = 0, length = n -1; i < length; ++i) {
		printf("%d, ", arr[i]);
	}
	printf("%d}\n", arr[n - 1]);
	return;
}