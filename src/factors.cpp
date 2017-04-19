#include <factors.hpp>
#include <print.hpp>
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <map>
#include <utility>

//=============================================================================
// MINOR FUNCTIONS
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
		if (evidence[parent] == HIDDEN || evidence[parent] == NONE) {
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
		if (evidence[parent] == HIDDEN || evidence[parent] == NONE) mask |= 1;
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
	/* Creating masks */
	std::map<int, int> weights;
	int v = 1;
	for (auto it = common_parents.rbegin(); it != common_parents.rend(); it++) {
		weights[*it] = v;
		v <<= 1;
	}
	/* Sorting Tables */
	std::vector<int> indices_x;
	std::vector<int> indices_y;
	sort_table(x, common_parents, weights, indices_x);
	sort_table(y, common_parents, weights, indices_y);
	/* New parents */
	std::copy(common_parents.begin(), common_parents.end(),
			std::back_inserter(result.parent_ids));
	for (unsigned int i = common_parents.size(); i < x.parent_ids.size(); i++)
		result.parent_ids.push_back(x.parent_ids[i]);
	for (unsigned int i = common_parents.size(); i < y.parent_ids.size(); i++)
		result.parent_ids.push_back(y.parent_ids[i]);
	std::copy(result.parent_ids.begin(), result.parent_ids.end(),
			std::inserter(result.parent_ids_set,
					result.parent_ids_set.begin()));
	/* Size of Matrix */
	result.len = 1
			<< (x.parent_ids.size() + y.parent_ids.size()
					- common_parents.size());
	result.matrix = new double[result.len];
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

void sort_table(factor& x, std::set<int>& common_parents,
		std::map<int, int>& weights, std::vector<int>& indices_x) {
	/* Creating vector for parent indices */
	for (int i = 0; i < x.len; i++)
		indices_x.push_back(i);
	/* Sorting Tables */
	std::stable_sort(indices_x.begin(), indices_x.end(),
			[&](int a,int b) {return parent_compare(a, b, x.parent_ids, weights);});
	/* Sorting parents */
	std::stable_partition(x.parent_ids.begin(), x.parent_ids.end(),
			[=](int i) {return contains(common_parents, i);});
	/* Sorting common parents */
	std::sort(x.parent_ids.begin(),
			x.parent_ids.begin() + common_parents.size());

}

bool parent_compare(int a, int b, std::vector<int>& parents,
		std::map<int, int>& weights) {
	int va = 0, vb = 0;
	for (auto it = parents.rbegin(); it != parents.rend(); it++) {
		if (contains(weights, *it)) {
			/* Common parents */
			va += (a & 1) * weights[*it];
			vb += (b & 1) * weights[*it];
		}
		a >>= 1;
		b >>= 1;
	}
	if (va == vb) {
		for (auto it = parents.begin(); it != parents.end() && va == vb; it++) {
			if (!contains(weights, *it)) {
				/* Now other parents */
				va <<= 1;
				vb <<= 1;
				va += (a & 1);
				vb += (b & 1);
			}
		}
	}
	return va < vb;
}

//=============================================================================
// SUM
//=============================================================================
void sum(factor& x, int var) {
	auto pos = find(x.parent_ids.begin(), x.parent_ids.end(), var);
	int delta = 1 << (x.parent_ids.size() - 1 - (pos - x.parent_ids.begin()));
	x.len >>= 1;
	double* new_matrix = new double[x.len];
	for (int i = 0, j = 0; i < delta; i += 2 * delta) {
		for (int k = i; k < i + delta; k++) {
			new_matrix[j++] = x.matrix[k] + x.matrix[k + delta];
		}
	}
	x.parent_ids.erase(pos);
	x.parent_ids_set.erase(var);
	delete[] x.matrix;
	x.matrix = new_matrix;
}

//=============================================================================
// NORMALIZE
//=============================================================================
void normalize(factor& x) {
	double sum = std::accumulate(x.matrix, x.matrix + x.len, 0.0);
	for (int i = 0; i < x.len; i++)
		x.matrix[i] /= sum;
}
