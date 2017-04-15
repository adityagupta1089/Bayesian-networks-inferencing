#include <factors.hpp>
#include <network.hpp>
#include <print.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;

//=============================================================================
// FUNCTIONS
//=============================================================================
void process_query_variable_elimination(network& _network, std::vector<int>& query_variables, std::vector<int>& evidence_variables, std::ofstream& out) {
	/* Processing Values of evidence variables */
	std::vector<int> evidence(_network.total_nodes);
	std::fill(evidence.begin(), evidence.begin() + _network.total_nodes, NONE);
	for (unsigned int i = 0; i < evidence_variables.size(); i++) {
		evidence[abs(evidence_variables[i]) - 1] = (evidence_variables[i] > 0 ? TRUE : FALSE);
	}
	/* Start with initial factors (Local CPTs instantiated by evidence variable) */
	std::vector<factor> factors(_network.total_nodes);
	for (node _node : _network.nodes) {
		std::cout << "Initial factor\n";
		print_factor(_node.cpt);
		factor reduced_factor;
		std::cout << "Evidence Variables\n";
		for (int x : evidence_variables)
			std::cout << (x < 0 ? "~" : " ") << (abs(x) - 1) << ", ";
		std::cout << "\n";
		reduce(_node.cpt, evidence, reduced_factor);
		std::cout << "Reduced factor\n";
		print_factor(reduced_factor);
		factors.push_back(reduced_factor);
		std::cout << "\n";
	}

	/* For each hidden variable H */
	{
		/* Join all factors with H */
		/* Eliminate/Sum H */
	}
	/* Join all remaining factors */
	/* Normalize */
	/* Write to output file*/
}
