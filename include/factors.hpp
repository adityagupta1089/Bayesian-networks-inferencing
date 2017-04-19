#ifndef INCLUDE_FACTORS_HPP_
#define INCLUDE_FACTORS_HPP_

#include <map>
#include <set>
#include <vector>

//=============================================================================
//CONSTANTS
//=============================================================================
#define HIDDEN -2
#define NONE -1
#define TRUE 1
#define FALSE 0

//=============================================================================
// STRUCTS
//=============================================================================
struct factor {
		int id;
		unsigned int len;
		double* matrix;
		std::vector<int> parent_ids;
		std::set<int> parent_ids_set;
		std::set<int> predecessors;
		std::vector<int> child_ids;

		inline bool contains(int id) {
			return parent_ids_set.find(id) != parent_ids_set.end();
		}
};
//=============================================================================
// PROTOTYPES
//=============================================================================
void reduce(factor& original, std::vector<int>& evidence, factor& result);

bool parent_compare(int a, int b, std::vector<int>& parents,
		std::map<int, int>& weights);
void sort_table(factor& x, std::set<int>& common_parents,
		std::map<int, int>& weights, std::vector<unsigned int>& indices_x);
factor join(factor x, factor y);

void sum(factor& x, int var);
void normalize(factor& x);

#endif /* INCLUDE_FACTORS_HPP_ */
