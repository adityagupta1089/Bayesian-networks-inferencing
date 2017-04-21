#include <factors.hpp>
#include <network.hpp>
#include <read_write.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

#define SAMPLE_COUNT 1000000

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct network;

//=============================================================================
// FUNCTIONS
//=============================================================================
void process_query_rejection_sampling(network& _network,
		std::vector<int>& query_variables, std::vector<int>& evidence_variables,
		std::ofstream& out) {
	factor result;
	unsigned int count = 0;
	for (int i : query_variables) {
		result.parent_ids.push_back(abs(i) - 1);
	}
	result.len = 1 << result.parent_ids.size();
	result.matrix = new double[result.len];
	/* Variable Values */
	unsigned int* values = new unsigned int[_network.total_nodes];
	/* Processing Values of evidence variables */
	std::vector<int> evidence(_network.total_nodes);
	std::fill(evidence.begin(), evidence.begin() + _network.total_nodes,
	HIDDEN);
	for (int x : query_variables)
		evidence[abs(x) - 1] = NONE;
	for (int x : evidence_variables)
		evidence[abs(x) - 1] = (x > 0 ? TRUE : FALSE);
	/* Iterate SAMPLE_COUNT times */
	for (int _i = 0; _i < SAMPLE_COUNT; _i++) {
		double sample = rand() / (double) RAND_MAX;
		unsigned int index = 0;
		bool reject = false;
		/* for each node x_i in the query, Topologically sorted */
		for (int x_i : _network.ids) {
			index = 0;
			/* Constructing Index */
			for (int i : _network.nodes[x_i].cpt.parent_ids) {
				if (i == x_i) continue;
				index <<= 1;
				index |= values[i];
			}
			/* Using sample value */
			if (sample < _network.nodes[x_i].cpt.matrix[index]) {
				if (evidence[x_i] == FALSE) {
					values[x_i] = 1;
					reject = true;
					break;
				}
				values[x_i] = 0;
				sample = rand() / (double) RAND_MAX;
			} else {
				if (evidence[x_i] == TRUE) {
					values[x_i] = 0;
					reject = true;
					break;
				}
				values[x_i] = 1;
				sample = rand() / (double) RAND_MAX;
			}
		}
		if (reject) continue;
		/* Final value */
		index = 0;
		for (int x_i : query_variables) {
			index <<= 1;
			index |= values[abs(x_i) - 1];
		}
		result.matrix[index]++;
		count++;
	}
	delete[] values;
	if (count == 0) {
		out << "These evidences can't occur at the same time,"
				" i.e. P(e) = 0, thus P(Q|e) is undefined.\n";
		return;
	}
	/* Averaging Values */
	for (unsigned int i = 0; i < result.len; i++)
		result.matrix[i] /= count;
	write_output(result, query_variables, out);
}
