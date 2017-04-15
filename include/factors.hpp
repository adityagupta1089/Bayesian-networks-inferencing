#ifndef INCLUDE_FACTORS_HPP_
#define INCLUDE_FACTORS_HPP_

#include <vector>

//=============================================================================
//CONSTANTS
//=============================================================================
#define NONE -1
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
		double** matrix;
		std::vector<int> parent_ids;
};

void reduce(factor& x, std::vector<int>& evidence_variables, factor& result);
void reduce_matrix(factor& x, factor& y, std::vector<int>& evidence_variables,unsigned int begin_x,unsigned int begin_y,unsigned int len_x,unsigned int len_y,unsigned int start_x = 0, unsigned int start_y = 0);

//=============================================================================
// PROTOTYPES
//=============================================================================
void reduce(factor& x, factor& y, factor& result);
void join(factor& x, factor& y, factor& result);
void sum(factor& x, factor& y, factor& result);
void normalize(factor& x, factor& result);

#endif /* INCLUDE_FACTORS_HPP_ */
