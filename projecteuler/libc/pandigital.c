#include "pandigital.h"

// Assumes 1 <= digits <= 9
int isPandigital(int n, int digits) {
    int i, idx;
    int seen[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (i = 0; i < digits; ++i) {
		idx = (n % 10) - 1;
		if (idx < 0 || idx >= digits || seen[idx]) {
			return 0;
		}
		seen[idx] = 1;
		n /= 10;
	}
    return 1;
}
