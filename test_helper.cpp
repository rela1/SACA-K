#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "test_helper.hpp"
#include "saca_k.hpp"

int ONE_MB = 1024 * 1024;

bool check_suffix_array(char * T, int * SA, int n) {
	for(int i = 0; i < n - 1; ++i) {
		if (strcmp(T + SA[i], T + SA[i + 1]) >= 0) return false;
	}
	return true;
}

bool test_create_sa_from_file(std::string path) {
	FILE * f = fopen(path.c_str(), "rb");
	if (f == NULL) {
		perror("Cannot run test!");
		return false;
	}
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	printf("Input file size: %ld characters\n", size);
	rewind(f);

	char * T = new char[size + 1]; 
	int offset_T = 0;
	int read_size = 0;
	do {
		read_size = fread(T + offset_T, sizeof(char), ONE_MB, f);
		offset_T += read_size;
	} while (read_size > 0);

	T[size] = 0;
	int * SA = new int[size + 1];
	saca_k(T, SA, 128, size + 1);
	if (check_suffix_array(T, SA, size + 1)) {
		printf("SUFFIX ARRAY OK MAJSTORE!\n");
	} else {
		printf("NI DOBRE!!!\n");
	}
	delete [] T;
	delete [] SA;
	return true;
}

bool test_random_sa(int number_of_tests, int T_size) {
	bool pass = true;
	srand(time(NULL));
	int passed_tests = 0;
	for(int i = 0; i < number_of_tests; ++i) {
		char * T = new char[T_size + 1];
		for(int j = 0; j < T_size; ++j) {
			T[j] = 1 + rand() % 10;
		}
		T[T_size] = 0;
		int * SA = new int[T_size + 1];
		saca_k(T, SA, 128, T_size + 1);
		if (check_suffix_array(T, SA, T_size + 1)) {
			printf("SUFFIX ARRAY OK MAJSTORE!\n");
			passed_tests++;
		} else {
			pass = false;
			printf("NI DOBRE!!!\n");
		}
		delete [] T;
		delete [] SA;
	}
	printf("Passed tests: %d/%d\n", passed_tests, number_of_tests);
	return pass;
}