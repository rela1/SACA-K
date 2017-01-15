#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include <sys/resource.h>
#include "saca_k.hpp"

/**
    Used for getting the peak used memory in bytes.

    @return peak used memory in bytes
    @author Ivan Relic
*/
long get_peak_used_memory() {
	struct rusage rusage;
    getrusage(RUSAGE_SELF, &rusage);
    return (long)(rusage.ru_maxrss * 1024L);
}

/**
    Main endpoint for calculating the suffix array.

	@param argc number of arguments
	@param argv array of arguments; argument on index 1 is expected to be input file and argument on index 2 is expected to be output file for suffix array of input file
    @author Ivan Relic
*/
int main(int argc, char const *argv[])
{
	FILE * f = fopen(argv[1], "rb");
	if (f == NULL) {
		perror("Cannot open input file!\n");
		return -1;
	}
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	printf("Input file size %ld\n", size);
	rewind(f);

	char * T = new char[size + 1];
	int read_size = fread(T, sizeof(char), size, f);
	fclose(f);
	if (read_size != size) {
		printf("Error reading input file!\n");
		return -1;
	}

	T[size] = 0;
	int * SA = new int[size + 1];
	long start = clock();
	saca_k(T, SA, 128, size + 1);
	long clocks = clock() - start;
	printf("Time needed for constructing suffix array: %f\n", double(clocks) / CLOCKS_PER_SEC);
	printf("Peak memory used: %ld bytes\n", get_peak_used_memory());
	printf("Writing suffix array to output file...\n");
	f = fopen(argv[2], "wb");
	if (f == NULL) {
		perror("Cannot open output file!");
		return -1;
	}
	int written_size = fwrite(SA + 1, sizeof(int), size, f);
	fclose(f);
	if (written_size != size) {
		printf("Error writing output file!\n");

		return -1;
	}

	delete [] T;
	delete [] SA;
	return 0;
}