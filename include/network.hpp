#ifndef INCLUDE_NETWORK_HPP_
#define INCLUDE_NETWORK_HPP_

#include <factors.hpp>
#include <vector>

//=============================================================================
// STRUCTS
//=============================================================================
struct node {
		factor cpt;
};

struct network {
		int total_nodes;
		std::vector<node> nodes;
};

#endif /* INCLUDE_NETWORK_HPP_ */
