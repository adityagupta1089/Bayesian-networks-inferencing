#include <factors.hpp>
#include <cstdio>

struct factor;

//=============================================================================
// FUNCTIONS
//=============================================================================
void reduce(factor& x, std::vector<int>& evidence_variables, factor& result) {
	int total_parents = 0;
	for (int i = 0; i < x.parent_ids.size(); i++) {
		if (evidence_variables[x.parent_ids[i]] == -1) {
			total_parents++;
			result.parent_ids.push_back(x.parent_ids[i]);
			printf("%d ", x.parent_ids[i]);
		}
	}
	int len = 1 << total_parents;
	result.matrix = new double*[len];
	reduce_matrix(x, result, evidence_variables, 0, 0,
			(1 << x.parent_ids.size()), len);
}

void reduce_matrix(factor& x, factor& y, std::vector<int>& evidence_variables,
		int begin_x, int begin_y, int len_x, int len_y, int start_x,
		int start_y) {
	// FIXME run input/b3.txt input/q3.txt output/o33.txt
	/*
	 Initial factor
	 | 05, 04, 01 |    x |   ~x |
	 |  T,  T,  T | 0.00 | 1.00 |
	 |  F,  T,  T | 1.00 | 0.00 |
	 |  T,  F,  T | 1.00 | 0.00 |
	 |  F,  F,  T | 0.00 | 1.00 |
	 |  T,  T,  F | 0.40 | 0.60 |
	 |  F,  T,  F | 0.20 | 0.80 |
	 |  T,  F,  F | 0.00 | 1.00 |
	 |  F,  F,  F | 0.20 | 0.80 |
	 Evidence Variables
	 -1, 2, 3, -2, 3, 5, 1, 1, 1, 3, 5, 6, 12, 1, 3, 5, 6, 12, 1, 2, -5, 6,
	 Reduced factor
	 |  X |    x |   ~x |
	 |    | 0.00 | 1.00 |
	 */
	if (len_x == 1) {
		y.matrix[begin_y] = new double[2];
		y.matrix[begin_y][0] = x.matrix[begin_x][0];
		y.matrix[begin_y][1] = x.matrix[begin_x][1];
		return;
	}
	if (y.parent_ids.size() <= start_y
			|| x.parent_ids[start_x] != y.parent_ids[start_y]) {
		if (evidence_variables[x.parent_ids[start_x]])
			reduce_matrix(x, y, evidence_variables, begin_x, begin_y, len_x / 2,
					len_y, start_x + 1, start_y);
		else
			reduce_matrix(x, y, evidence_variables, begin_x + len_x / 2,
					begin_y, len_x / 2, len_y, start_x + 1, start_y);
		return;
	}
	reduce_matrix(x, y, evidence_variables, begin_x, begin_y, len_x / 2,
			len_y / 2, start_x + 1, start_y + 1);
	reduce_matrix(x, y, evidence_variables, begin_x + len_x / 2,
			begin_y + len_y / 2, len_x / 2, len_y / 2, start_x + 1,
			start_y + 1);
}

void join(factor& x, factor& y, factor& result) {

}

void sum(factor& x, factor& y, factor& result) {

}

void normalize(factor& x, factor& result) {

}
