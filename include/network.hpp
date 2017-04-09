#ifndef INCLUDE_NETWORK_HPP_
#define INCLUDE_NETWORK_HPP_

using namespace std;

struct node {
		int** conditional_probability_table;
		int total_parents;
		int* parent_ids;
};

struct network {
		int total_nodes;
		node* nodes;
};

#endif /* INCLUDE_NETWORK_HPP_ */
