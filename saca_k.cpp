#include "induced_sorting_0.hpp"
#include "helper.hpp"
#include <cstring>
#include <cstdio>

void saca_k(char * T, int * SA, int K, int n, int n1, int level) {
	int * bkt;
	if (level == 0) {
		bkt = new int[K];
		induced_sort_LMS_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		induced_sort_L_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
		induced_sort_S_0(T, SA, bkt, n);
		print_array(SA, n, "SA");
	}

	// TODO

	if (level == 0) {
		induced_sort_SA_0(T, SA, bkt, n, n1);
		delete [] bkt;
	}

	return;
}

int main() {
	char T[] = {'c', 'a', 'b', 'b', 'a', 'g', 'e', '\0', '\0'};
	int SA[8];
	printf("sizeof SA %ld\n", sizeof(SA));
	saca_k(T, SA, 127, 8, 0, 0);
	return 0;
}