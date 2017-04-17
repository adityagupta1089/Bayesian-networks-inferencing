#include <iostream>
#include <vector>

#define SAMPLE_COUNT 500

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
	//TODO
	/* repeat for SAMPLE_COUNT */
	for (int _i = 0; _i < SAMPLE_COUNT; _i++) {
		/* for each node x_i in query?*/
		for (int x_i : query_variables) {
			//TODO sample(_network, x_i);
			/* sample x_i from cpt */
			/* if x_i not consistent with evidence go to next cycle*/
			/* else maintain some count of x_i */
		}
	}
	/* calculate probability for given query */
}
