#include <math.h>
#include "prime.h"

int isPrime(unsigned long long n) {
	unsigned long long sq, i;
	if (n < 2) {
		return 0;
	}
	if (n == 2 || n == 3) {
		return 1;
	}
	sq = sqrt(n);
	for (i = 2; i <= sq; ++i) {
		if (!(n % i)) { // i divides n
			return 0;
		}
	}
	return 1;
}

int isPrimeInt(int n) {
	int sq, i;
	if (n < 2) {
		return 0;
	}
	if (n == 2 || n == 3) {
		return 1;
	}
	sq = sqrt(n);
	for (i = 2; i <= sq; ++i) {
		if (!(n % i)) { // i divides n
			return 0;
		}
	}
	return 1;
}

int primeFactor(int n) {
	int sq, i;
	if (isPrimeInt(n)) {
		return n;
	}
	sq = sqrt(n);
	for (i = 2; i <= sq; ++i) {
		if (!(n % i) && isPrimeInt(i)) {
			return i;
		}
	}
	return 0;
}

int primeFactorCount(int n) {
	int i, count, factor, *seen, seenLength;
	seenLength = sqrt(n);
	seen = (int*) malloc(sizeof(int) * seenLength);
	count = 0;
	do {
		factor = primeFactor(n);
		if (!factor) {
			break;
		}
		for (i = 0; i < count && seen[i] != factor; ++i);
		if (i == count) {
			seen[count] = factor;
			++count;
		}
		n /= factor;
	} while (n > factor);
	free(seen);
	return count;
}

int phi(int n) {
	int result, i, factor;
	if (isPrimeInt(n)) {
		return n * (1 - (1.0 / n));
	}
	result = n;
	do {
		factor = primeFactor(n);
		while (!(n % factor)) {
			n /= factor;
		}
		result *= (1 - (1.0 / factor));
	} while (n > factor);
	return result;
}
