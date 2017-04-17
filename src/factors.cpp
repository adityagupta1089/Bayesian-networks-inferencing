#include <factors.hpp>
#include <cstdio>
#include <algorithm>
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
			/* Parents in both of them will be in same order */
			result.parent_ids.push_back(x.parent_ids[i]);
		}
	}
	if (total_parents == x.parent_ids.size()) {
		result = x;
		return;
	}
	int len = 1 << total_parents;
	result.matrix = new double[len];
	reduce(x, result, evidence, 0, 0, (1 << x.parent_ids.size()), len);
}

void reduce(factor& original, factor& result, std::vector<int>& evidence,
		unsigned int begin_x, unsigned int begin_y, unsigned int len_x,
		unsigned int len_y, unsigned int start_x, unsigned int start_y) {
	/* No parents of original factor (length = 1), no need to reduce */
	if (len_x == 1) {
		result.matrix[begin_y] = original.matrix[begin_x];
		return;
	}
	/* Both have parents in the same order so we can compare if both have same
	 * parent at the corresponding indexes start_x and start_y */
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
		/* Both parents at current indexes are same, reduce upper and lower
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
factor sum(factor& x, int var) {
	//TODO
	factor result;
	result.parent_ids=x.parent_ids;
	result.parent_ids.erase(std::remove(result.parent_ids.begin(), result.parent_ids.end(), var), result.parent_ids.end());
	result.matrix=new double[1<<result.parent_ids.size()];
	sum_matrix(x,result,var,0,0,1<<x.parent_ids.size(),1<<result.parent_ids.size(),0,0);
	return result;
}
void sum_matrix(factor& original, factor& result, int var,
		unsigned int begin_x, unsigned int begin_y, unsigned int len_x,
		unsigned int len_y, unsigned int start_x, unsigned int start_y) {
	/* No parents of original factor (length = 1), no need to reduce */
	if (len_x == 1) {
		result.matrix[begin_y] += original.matrix[begin_x];
//		printf("%f:%f\n", original.matrix[begin_x],result.matrix[begin_y]);
		return;
	}
	/* Both have parents in the same order so we can compare if both have same
	 * parent at the corresponding indexes start_x and start_y */
	if (original.parent_ids[start_x] == var) {
		/* parent start_x of original factor is not a parent of reduced factor,
		 * increase start_x (this parent processed) and reduce the corresponding
		 * part of the table according to the parents' evidence value */
			/* If true take the upper half */
			sum_matrix(original, result, var, begin_x, begin_y, len_x / 2,
					len_y, start_x + 1, start_y);
			sum_matrix(original, result, var, begin_x + len_x/2, begin_y, len_x / 2,
					len_y, start_x + 1, start_y);
		} else {
			/* If false take the lower half */
			sum_matrix(original, result, var, begin_x, begin_y, len_x / 2,
					len_y/2, start_x + 1, start_y + 1);
			sum_matrix(original, result, var, begin_x + len_x / 2, begin_y + len_y/2,
					len_x / 2, len_y/2, start_x + 1, start_y + 1);
		}
		return;
}

//=============================================================================
// NORMALIZE
//=============================================================================
void normalize(factor& x) {
	//TODO
}
