#include <factors.hpp>
#include <cstdio>
#include <vector>

//=============================================================================
// FUNCTIONS
//=============================================================================
void print_factor(factor& _factor) {
	int total_parents = _factor.parent_ids.size();
	int rows = 1 << total_parents;

	printf("| ");
	if (_factor.parent_ids.size() == 0) printf(" X");
	for (int i = total_parents - 1; i >= 0; i--) {
		printf("%02d", _factor.parent_ids[i]);
		if (i != 0) printf(", ");
	}
	printf(" | %4s | %4s |\n", "x", "~x");
	for (int i = 0; i < rows; i++) {
		printf("| ");
		if (total_parents == 0) printf("  ");
		else {
			for (int j = i, k = 0; k < total_parents; j >>= 1, k++) {
				printf("%2s", (j & 1) ? "F" : "T");
				if (k != total_parents - 1) printf(", ");
			}
		}
		printf(" | %1.2f | %1.2f |\n", _factor.matrix[i][0], _factor.matrix[i][1]);
	}
}
