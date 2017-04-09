#ifndef INCLUDE_NETWORK_HPP_
#define INCLUDE_NETWORK_HPP_

#include <vector>

//=============================================================================
// STRUCTS
//=============================================================================
struct node {
		double** conditional_probability_table;
		std::vector<int> parent_ids;
};

struct network {
		int total_nodes;
		node* nodes;
};

#endif /* INCLUDE_NETWORK_HPP_ */
