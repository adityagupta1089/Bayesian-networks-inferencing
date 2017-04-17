#include <factors.hpp>
#include <network.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>
#include <print.hpp>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;

//=============================================================================
// FUNCTIONS
//=============================================================================
void process_query_variable_elimination(network& _network,
		std::vector<int>& query_variables, std::vector<int>& evidence_variables,
		std::ofstream& out) {
	/* Processing Values of evidence variables */
	std::vector<int> evidence(_network.total_nodes);
	std::fill(evidence.begin(), evidence.begin() + _network.total_nodes,
	HIDDEN);
	for (unsigned int i = 0; i < evidence_variables.size(); i++) {
		evidence[abs(evidence_variables[i]) - 1] = (
				evidence_variables[i] > 0 ? TRUE : FALSE);
	}
	/* Start with initial factors (Local CPTs instantiated by evidence variable) */
	std::vector<factor> factors(_network.total_nodes);
	unsigned int i = 0;
	for (node _node : _network.nodes) {
		factor reduced_factor;
		reduce(_node.cpt, evidence, reduced_factor);
		factors[i++] = reduced_factor;
	}
	/* For each hidden variable H */
	for (int i = 0; i < _network.total_nodes; i++) {
		if (evidence[i] == HIDDEN) {
			auto it = std::partition(factors.begin(), factors.end(),
					[&](factor _factor) {return !_factor.contains(i);});
			if (it != factors.end()) {
				/* Join all factors with H */
				factor joint_factor = std::accumulate(it + 1, factors.end(),
						*it, join);
				factors.erase(it, factors.end());
				/* Eliminate/Sum H */
				sum(joint_factor, i);
				factors.push_back(joint_factor);
			}
		}
	}
	/* Join all remaining factors */
	factor result = std::accumulate(factors.begin() + 1, factors.end(),
			factors[0], join);
	/* Normalize */
//	normalize(result);
	/* TODO Write to output file*/
	print_factor(result);
}
