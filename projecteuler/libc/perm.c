#include "perm.h"

int isPermutation(int n1, int n2) {
	int i, digit;
	int count[10];
	for (i = 0; i < 10; ++i) {
		count[i] = 0;
	}
	while (n1 > 0 && n2 > 0) {
		digit = n1 % 10;
		++count[digit];
		n1 /= 10;
		digit = n2 % 10;
		--count[digit];
		n2 /= 10;
	}
	for (i = 0; i < 10; ++i) {
		if (count[i]) {
			return 0;
		}
	}
	return 1;
}
