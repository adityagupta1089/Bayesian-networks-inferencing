#include <iostream>
#include <vector>

struct network;

void process_query_variable_elimination(network& _network,
		std::vector<int>& query_variables, std::vector<int>& evidence_variables,
		std::ofstream& out) {
	//TODO
	/* Start with initial factors (Local CPTs instantiated by evidence variable) */
	/* For each hidden variable H */
	{
		/* Join all factors with H */
		/* Eliminate/Sum H */
	}
	/* Join all remaining factors */
	/* Normalize */
	/* Write to output file*/
}

