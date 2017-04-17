#ifndef INCLUDE_FACTORS_HPP_
#define INCLUDE_FACTORS_HPP_

#include <set>
#include <vector>

//=============================================================================
//CONSTANTS
//=============================================================================
#define HIDDEN -1
#define TRUE 1
#define FALSE 0

//=============================================================================
// STRUCTS
//=============================================================================
/*
 * if parent_ids = {1, 2, 3}
 * then matrix = { P(x|1,2,3), P(~x|1,2,3), P(x|1,2,~3), P(~x|1,2,-3),
 * 		... P(~x|~1,~2,~3) }
 */
struct factor {
		int id;
		int len;
		double* matrix;
		std::vector<int> parent_ids;
		std::set<int> parent_ids_set;

		inline bool contains(int id) {
			return parent_ids_set.find(id) != parent_ids_set.end();
		}
};
//=============================================================================
// PROTOTYPES
//=============================================================================
void reduce(factor& original, std::vector<int>& evidence, factor& result);
factor join(factor x, factor y);
void sum(factor& x, int var);
void normalize(factor& x);

#endif /* INCLUDE_FACTORS_HPP_ */
