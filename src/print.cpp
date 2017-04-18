#include <factors.hpp>
#include <algorithm>
#include <cstdio>
#include <string>
#include <stack>

//=============================================================================
// HEADER
//=============================================================================
void print_separator(int cnt) {
	printf("+");
	for (int i = 0; i <= cnt; i++)
		printf("-");
	printf("+--------------+\n");
}
//=============================================================================
// PRINT
//=============================================================================
void print_factor(factor& _factor) {
	int total_parents = _factor.parent_ids.size();
	int rows = 1 << total_parents;
	int cnt = 4 * std::max(total_parents, 1) - 1;
	/* Separator */
	print_separator(cnt);
	/* Parent IDS */
	printf("| ");
	if (_factor.parent_ids.size() == 0) printf("  ");
	for (unsigned int i = 0; i < _factor.parent_ids.size(); i++) {
		printf("%02d", _factor.parent_ids[i]);
		if (i != _factor.parent_ids.size() - 1) printf(", ");
	}
	printf(" | %12s |\n", "P");
	/* Separator */
	print_separator(cnt);
	/* Rows */
	for (int i = 0; i < rows; i++) {
		printf("| ");
		if (total_parents == 0) printf("  ");
		else {
			std::stack<std::string> vals;
			for (int j = i, k = 0; k < total_parents; j >>= 1, k++) {
				vals.push((j & 1) ? " F" : " T");
				if (k != total_parents - 1) vals.push(", ");
			}
			while (!vals.empty()) {
				printf("%s", vals.top().c_str());
				vals.pop();
			}
		}
		printf(" | %1.10f |\n", _factor.matrix[i]);
	}
	/* Separator */
	print_separator(cnt);
}
