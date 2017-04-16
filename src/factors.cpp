#include <factors.hpp>
#include <cstdio>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct factor;

//=============================================================================
// REDUCE
//=============================================================================
void reduce(factor& x, std::vector<int>& evidence, factor& result) {
	unsigned int total_parents = 0;
	for (unsigned int i = 0; i < x.parent_ids.size(); i++) {
		if (evidence[x.parent_ids[i]] == HIDDEN) {
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
	reduce(x, result, evidence, 0, 0, (1 << x.parent_ids.size()), len);
}

void reduce(factor& original, factor& result, std::vector<int>& evidence,
		unsigned int begin_x, unsigned int begin_y, unsigned int len_x,
		unsigned int len_y, unsigned int start_x, unsigned int start_y) {
	/* No parents of original factor (length = 1), no need to reduce */
	if (len_x == 1) {
		result.matrix[begin_y] = new double[2];
		result.matrix[begin_y][0] = original.matrix[begin_x][0];
		result.matrix[begin_y][1] = original.matrix[begin_x][1];
		return;
	}
	/* Why is this condition there? Do you assume that parent ids are sorted? */
	if (result.parent_ids.size() <= start_y
			|| original.parent_ids[start_x] != result.parent_ids[start_y]) {
		/* parent start_x of original factor is not a parent of reduced factor,
		 * increase start_x (this parent processed) and reduce the corresponding
		 * part of the table according to the parents' evidence value */
		if (evidence[original.parent_ids[start_x]] == TRUE) {
			/* If true take the upper half */
			reduce(original, result, evidence, begin_x, begin_y, len_x / 2,
					len_y, start_x + 1, start_y);
		} else {
			/* If false take the lower half */
			reduce(original, result, evidence, begin_x + len_x / 2, begin_y,
					len_x / 2, len_y, start_x + 1, start_y);
		}
		return;
	} else {
		/* Both parents at current indices are same, reduce upper and lower
		 * half parts both */
		reduce(original, result, evidence, begin_x, begin_y, len_x / 2,
				len_y / 2, start_x + 1, start_y + 1);
		reduce(original, result, evidence, begin_x + len_x / 2,
				begin_y + len_y / 2, len_x / 2, len_y / 2, start_x + 1,
				start_y + 1);
	}

}

//=============================================================================
// JOIN
//=============================================================================
factor join(factor x, factor y) {
	factor result;
	/* TODO Natural Join */
	/* TODO See https://en.wikipedia.org/wiki/Nested_loop_join and
	 * https://en.wikipedia.org/wiki/Sort-merge_join */
	return result;
}

//=============================================================================
// SUM
//=============================================================================
void sum(factor& x, int var) {
	//TODO
}

//=============================================================================
// NORMALIZE
//=============================================================================
void normalize(factor& x) {
	//TODO
}
