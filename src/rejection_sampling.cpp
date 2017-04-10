#include <iostream>
#include <vector>

#define SAMPLE_COUNT

struct network;

void process_query_rejection_sampling(network& _network, std::vector<int>& query_variables,
		std::vector<int>& evidence_variables, std::ofstream& out) {
	//TODO
	/* repeat for SAMPLE_COUNT */
		/* for each node x_i */
			/* sample x_i from cpt */
			/* if x_i not consistent with evidence go to next cycle*/
			/* else maintain some count of x_i */

	/* calculate probability for given query */
}
