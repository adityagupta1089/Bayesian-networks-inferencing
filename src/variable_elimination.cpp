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

#define DEBUG true

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
	if (DEBUG) {
		printf("Query Variables: \n");
		for (int x : query_variables)
			printf("%2d, ", x - 1);
		printf("\nEvidence Variables: \n");
		for (int x : evidence_variables)
			printf("%s%2d", (x < 0 ? "~" : " "), abs(x) - 1);
		printf("\n");
	}
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
		if (DEBUG) {
			printf("Factor: \n");
			print_factor(_node.cpt);
		}
		reduce(_node.cpt, evidence, reduced_factor);
		if (DEBUG) {
			printf("Reduced: \n");
			print_factor(reduced_factor);
		}
		/* Only push if it's not a constant */
		if (reduced_factor.parent_ids.size() > 0) {
			factors.push_back(reduced_factor);
		}
	}
	if (DEBUG) {
		printf("Initially factors: \n");
		for (factor f : factors)
			print_factor(f);
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
				if (DEBUG) {
					printf("Joint Factor for hidden variable %d\n", i);
					print_factor(joint_factor);
				}
				/* Eliminate/Sum H */
				sum(joint_factor, i);
				if (DEBUG) {
					printf("Summed variable %d\n", i);
					print_factor(joint_factor);
				}
				factors.push_back(joint_factor);
			}
		}
	}
	if (DEBUG) {
		printf("After Joining all hidden variables: \n");
		for (factor f : factors)
			print_factor(f);
	}
	/* Join all remaining factors */
	factor result = std::accumulate(factors.begin() + 1, factors.end(),
			factors[0], join);
	if (DEBUG) {
		printf("Joining remaining factors: \n");
		print_factor(result);
	}
	/* Normalize */
	normalize(result);
	if (DEBUG) {
		printf("Normalizing\n");
		print_factor(result);
	}
	/* TODO Write to output file*/
	write_output(result, out);
}
