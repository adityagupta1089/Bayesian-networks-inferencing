#include <factors.hpp>
#include <network.hpp>
#include <print.hpp>
#include <read_write.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

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
	for (int x : query_variables)
		evidence[abs(x) - 1] = NONE;
	for (int x : evidence_variables)
		evidence[abs(x) - 1] = (x > 0 ? TRUE : FALSE);
	/* Start with initial factors (Local CPTs instantiated by evidence variable) */
	std::vector<factor> factors;
	for (node _node : _network.nodes) {
		factor reduced_factor;
		reduce(_node.cpt, evidence, reduced_factor);
		/* Only push if it's not a constant */
		if (reduced_factor.parent_ids.size() > 0) {
			factors.push_back(reduced_factor);
		}
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
	normalize(result);
	/* Write to output file*/
	write_output(result, query_variables, out);
}
