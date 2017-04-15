#include <factors.hpp>
#include <cstdio>

struct factor;

//=============================================================================
// FUNCTIONS
//=============================================================================
void reduce(factor& x, std::vector<int>& evidence, factor& result) {
	int total_parents = 0;
	for (int i = 0; i < x.parent_ids.size(); i++) {
		if (evidence[x.parent_ids[i]] == NONE) {
			total_parents++;
			result.parent_ids.push_back(x.parent_ids[i]);
		}
	}
	if (total_parents == x.parent_ids.size()) {
		result = x;
		return;
	}
	int len = 1 << total_parents;
	result.matrix = new double*[len];
	reduce_matrix(x, result, evidence, 0, 0, (1 << x.parent_ids.size()), len);
}

void reduce_matrix(factor& x, factor& y, std::vector<int>& evidence_variables, int begin_x, int begin_y, int len_x, int len_y, int start_x,
		int start_y) {
	if (len_x == 1) {
		y.matrix[begin_y] = new double[2];
		y.matrix[begin_y][0] = x.matrix[begin_x][0];
		y.matrix[begin_y][1] = x.matrix[begin_x][1];
		return;
	}
	if (y.parent_ids.size() <= start_y || x.parent_ids[start_x] != y.parent_ids[start_y]) {
		if (evidence_variables[x.parent_ids[start_x]]) reduce_matrix(x, y, evidence_variables, begin_x, begin_y, len_x / 2, len_y, start_x + 1, start_y);
		else reduce_matrix(x, y, evidence_variables, begin_x + len_x / 2, begin_y, len_x / 2, len_y, start_x + 1, start_y);
		return;
	}
	reduce_matrix(x, y, evidence_variables, begin_x, begin_y, len_x / 2, len_y / 2, start_x + 1, start_y + 1);
	reduce_matrix(x, y, evidence_variables, begin_x + len_x / 2, begin_y + len_y / 2, len_x / 2, len_y / 2, start_x + 1, start_y + 1);
}

void join(factor& x, factor& y, factor& result) {

}

void sum(factor& x, factor& y, factor& result) {

}

void normalize(factor& x, factor& result) {

}
