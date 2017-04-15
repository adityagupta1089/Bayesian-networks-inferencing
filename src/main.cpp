#include <network.hpp>
#include <queries.hpp>
#include <read_write.hpp>
#include <stdio.h>
#include <stdlib.h>

//=============================================================================
// MAIN
//=============================================================================
int main(int argc, char** argv) {
	if (argc < 4) {
		printf("Input Format: %s <bayesian network input file> <queries input file> <output file>", argv[0]);
		exit(1);
	}

	network _network;

	read_input(argv[1], _network);
	process_queries(argv[2], _network, argv[3]);

	return 0;
}

