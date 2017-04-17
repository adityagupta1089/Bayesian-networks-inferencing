#include <factors.hpp>
#include <algorithm>
#include <cstdio>
#include <vector>

//=============================================================================
// HEADER
//=============================================================================
void print_header(int cnt) {
	printf("+");
	for (int i = 0; i <= cnt; i++)
		printf("-");
	printf("+------+\n");
}
//=============================================================================
// PRINT
//=============================================================================
void print_factor(factor& _factor) {
	int total_parents = _factor.parent_ids.size();
	int rows = 1 << total_parents;
	int cnt = 4 * std::max(total_parents, 1) - 1;
	/* Header */
	print_header(cnt);
	/* Parent IDS */
	printf("| ");
	if (_factor.parent_ids.size() == 0) printf("  ");
	for (int i = total_parents - 1; i >= 0; i--) {
		printf("%02d", _factor.parent_ids[i]);
		if (i != 0) printf(", ");
	}
	printf(" | %4s |\n", "P");
	/* Header */
	print_header(cnt);
	/* Values */
	for (int i = 0; i < rows; i++) {
		printf("| ");
		if (total_parents == 0) printf("  ");
		else {
			for (int j = i, k = 0; k < total_parents; j >>= 1, k++) {
				printf("%2s", (j & 1) ? "F" : "T");
				if (k != total_parents - 1) printf(", ");
			}
		}
		printf(" | %1.2f |\n", _factor.matrix[i]);
	}
	/* Header */
	print_header(cnt);
}
