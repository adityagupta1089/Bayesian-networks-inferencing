#include <factors.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <utility>

//=============================================================================
// NIFTY SHORTHAND
//=============================================================================
#define contains(set, val) (set.find(val) != set.end())

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
struct factor;

//=============================================================================
// REDUCE
//=============================================================================
void reduce(factor& original, std::vector<int>& evidence, factor& result) {
	unsigned int total_parents = 0;
	for (int parent : original.parent_ids) {
		if (evidence[parent] == HIDDEN) {
			total_parents++;
			result.parent_ids.push_back(parent);
			result.parent_ids_set.insert(parent);
		}
	}
	int new_len = 1 << total_parents;
	result.len = new_len;
	result.matrix = new double[new_len];
	int res = 0, mask = 0;
	for (int parent : original.parent_ids) {
		res <<= 1;
		mask <<= 1;
		if (evidence[parent] == HIDDEN) mask |= 1;
		if (evidence[parent] != FALSE) res |= 1;
	}
	for (int i = original.len - 1, j = 0; i >= 0; i--) {
		if ((i | mask) == res) {
			result.matrix[j++] = original.matrix[original.len - 1 - i];
		}
	}
}

//=============================================================================
// JOIN
//=============================================================================
factor join(factor x, factor y) {
	factor result;
	std::set<int> common_parents;
	std::set_intersection(x.parent_ids_set.begin(), x.parent_ids_set.end(),
			y.parent_ids_set.begin(), y.parent_ids_set.end(),
			std::inserter(common_parents, common_parents.end()));
	if (common_parents.size() > 1) {
		fprintf(stderr,
				"NOTE: If more than one parents are there, we need to sort "
						"common parents amongst themselves also\n");
		exit(0);
	}
	/* NOTE: Assuming x & y are pass by value so modifying them by sorting */

	/* Creating vector for parent indices */
	std::vector<int> indices_x;
	for (int i = 0; i < x.len; i++)
		indices_x.push_back(i);

	std::vector<int> indices_y;
	for (int i = 0; i < y.len; i++)
		indices_y.push_back(i);
	/* Creating masks */
	int mask_x = 0;
	int mask_y = 0;
	for (int parent : x.parent_ids) {
		mask_x <<= 1;
		if (!contains(common_parents, parent)) mask_x |= 1;
	}
	for (int parent : y.parent_ids) {
		mask_y <<= 1;
		if (!contains(common_parents, parent)) mask_y |= 1;
	}
	/* sorting parents */
	std::stable_partition(x.parent_ids.begin(), x.parent_ids.end(),
			[=](int i) {return contains(common_parents, i);});
	std::stable_partition(y.parent_ids.begin(), y.parent_ids.end(),
			[=](int i) {return contains(common_parents, i);});
	/* Sorting Tables */
	std::sort(indices_x.begin(), indices_x.end(),
			[=](int a, int b) {return (a | mask_x) < (b | mask_x);});
	std::sort(indices_y.begin(), indices_y.end(),
			[=](int a, int b) {return (a | mask_y) < (b | mask_y);});
	/* Size of Matrix */
	result.len = 1
			<< (x.parent_ids.size() + y.parent_ids.size()
					- common_parents.size());
	result.matrix = new double[result.len];
	/* New parents */
	std::copy(common_parents.begin(), common_parents.end(),
			std::back_inserter(result.parent_ids));
	for (unsigned int i = common_parents.size(); i < x.parent_ids.size(); i++)
		result.parent_ids.push_back(x.parent_ids[i]);
	for (unsigned int i = common_parents.size(); i < y.parent_ids.size(); i++)
		result.parent_ids.push_back(y.parent_ids[i]);
	/* Join Operation */
	int common_parents_block = 1 << common_parents.size();
	int x_block_len = x.len / common_parents_block;
	int y_block_len = y.len / common_parents_block;
	for (int c = 0, i = 0, j = 0, m = 0; c < common_parents_block; i +=
			x_block_len, j += y_block_len, c++) {
		for (int k = i; k < i + x_block_len; k++) {
			for (int l = j; l < j + y_block_len; l++) {
				result.matrix[m++] = x.matrix[indices_x[k]]
						* y.matrix[indices_y[l]];
			}
		}
	}
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
