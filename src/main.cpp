#include <stdio.h>
#include <stdlib.h>

#include "functions.hpp"
#include "read_write.cpp"
#include "queries.cpp"

int main(int argc, char** argv) {
	if (argc < 4) {
		printf("Input Format: %s <bayesian network input file> <queries input file> <output file>", argv[0]);
		exit(1);
	}

	read_input(argv[1]);
	process_queries(argv[2]);
	write_results(argv[3]);

	return 0;
}

