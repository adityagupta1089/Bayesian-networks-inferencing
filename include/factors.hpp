#ifndef INCLUDE_FACTORS_HPP_
#define INCLUDE_FACTORS_HPP_

#include <unordered_set>
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
		double* matrix;
		std::vector<int> parent_ids;
		std::unordered_set<int> parent_ids_set;

		inline bool contains(int id) {
			return parent_ids_set.find(id) != parent_ids_set.end();
		}
};
//=============================================================================
// PROTOTYPES
//=============================================================================
void reduce(factor& x, std::vector<int>& evidence, factor& result);
void reduce(factor& x, factor& y, std::vector<int>& evidence,
		unsigned int begin_x, unsigned int begin_y, unsigned int len_x,
		unsigned int len_y, unsigned int start_x = 0, unsigned int start_y = 0);

factor join(factor x, factor y);

void sum(factor& x, int var);
void normalize(factor& x);

#endif /* INCLUDE_FACTORS_HPP_ */
