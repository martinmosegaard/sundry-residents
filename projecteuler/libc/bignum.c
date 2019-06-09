#include <stdio.h>
#include "bignum.h"

void bignum_init(unsigned int sum[], unsigned int length) {
	unsigned int i; 
	for (i = 0; i < length; ++i) {
		sum[i] = 0;
	}
}

/*
 * Adds a number to a sum represented by an array.
 *
 * Params:
 * sum - the number represented by an array, to which the number is added
 * length - the length of the array
 * number - the number to add
 *
 * Returns:
 * -1 if there is an overflow, otherwise 0.
 */
int bignum_add(unsigned int sum[], unsigned int length, unsigned long number) {
	unsigned int pos;
	unsigned int current;
	unsigned int carry;
	unsigned long rest;
	rest = number;
	pos = length - 1;
	carry = 0;
	while (rest > 0 || carry) {
		current = (rest % 10) + carry + sum[pos];
		rest /= 10;
		carry = current / 10;
		sum[pos] = current % 10;
		--pos;
		if (pos < 0) {
			return -1;
		}
	}
	return 0;
}

/*
 * Adds two numbers represented by arrays and returns the result in the first array.
 *
 * Params:
 * sum1 - The array which will hold the result
 * sum2 - The array to add to sum1
 * length - The length of the arrays
 *
 * Returns:
 * -1 if there is an overflow, otherwise zero
 */
int bignum_add2(unsigned int sum1[], unsigned int sum2[], unsigned int length) {
	int pos, carry, current;
	carry = 0;
	for (pos = length - 1; pos >= 0; --pos) {
		current = sum1[pos] + sum2[pos] + carry;
		carry = current / 10;
		sum1[pos] = current % 10;
	}
	return carry * -1;
}

/*
 * Multiplies a number to a sum represented by an array.
 *
 * Params:
 * sum - the number represented by an array, to which the number is multiplied
 * length - the length of the array
 * number - the number to multiply
 *
 * Returns:
 * -1 if there is an overflow, otherwise 0.
 */
int bignum_mul(unsigned int sum[], unsigned int length, unsigned long number) {
	int pos, i, result;
	unsigned int current, digit, carry;
	unsigned long rest;
	unsigned int *copy, *copy2; // multiply into copy, copy2 holds original number
	result = 0;
	copy = (int*) malloc(sizeof(unsigned int) * length);
	copy2 = (int*) malloc(sizeof(unsigned int) * length);
	bignum_copy(sum, copy, length);
	bignum_copy(sum, copy2, length);
	bignum_init(sum, length);
	rest = number;
	pos = length - 1;
	carry = 0;
	do {
		digit = rest % 10;
		rest /= 10;
		// multiply digit into copy
		for (i = pos; i >= 0; --i) {
			current = (digit * copy[i]) + carry;
			carry = current / 10;
			copy[i] = current % 10;
		}
		// add to result
		bignum_add2(sum, copy, length);
		if (carry) {
			result = -1; // overflow
			break;
		}
		--pos;
		if (pos < 0) {
			result = -1; // number was larger than array
			break;
		}
		// multiply copy by 10
		bignum_copy(copy2, copy, length);
		if (copy[0] != 0) {
			result = -1; // overflow
			break;
		}
		for (i = 0; i < length - 1; ++i) {
			copy[i] = copy[i + 1];
		}
		copy[length - 1] = 0;
		bignum_copy(copy, copy2, length);
	} while (rest > 0);
	free(copy);
	free(copy2);
	return result;
}

/*
 * Multiplies two numbers represented by arrays.
 *
 * Params:
 * sum1 - first number
 * sum2 - second number
 * length - the length of the two arrays
 * result - result array
 * resultLength - length of result array
 *
 * Returns:
 * -1 if there is an overflow, otherwise 0.
 */
int bignum_mul2(unsigned int sum1[], unsigned int sum2[], unsigned int length,
			    unsigned int result[] /* out */, unsigned int resultLength) {
	int i, j, res;
	unsigned int current, carry, pos, *copy;
	res = 0;
	copy = (unsigned int*) malloc(sizeof(unsigned int) * resultLength);
	bignum_init(result, resultLength);
	for (i = length - 1; i >= 0; --i) {
		carry = 0;
		bignum_init(copy, resultLength);
		// multiply digit through sum2 into copy
		for (j = length - 1; j >= 0; --j) {
			current = (sum1[i] * sum2[j]) + carry;
			carry = current / 10;
			pos = i + j + 1;
			copy[pos] = current % 10;
		}
		copy[i] = carry;
		// add to result
		if (bignum_add2(result, copy, resultLength)) {
			res = -1; // overflow
			break;
		}
	}
	free(copy);
	return res;
}

/*
 * Multiplies a number by itself.
 * The result length should be twice the length of the number.
 * Returns -1 if there is an overflow error.
 */
int bignum_square(unsigned int number[], unsigned int length,
				  unsigned int result[] /* out */, unsigned int resultLength) {
	int i, j, res;
	unsigned int current, carry, pos, *copy;
	res = 0;
	copy = (unsigned int*) malloc(sizeof(unsigned int) * resultLength);
	bignum_init(result, resultLength);
	for (i = length - 1; i >= 0; --i) {
		carry = 0;
		bignum_init(copy, resultLength);
		// multiply digit though number into copy
		for (j = length - 1; j >= 0; --j) {
			current = (number[i] * number[j]) + carry;
			carry = current / 10;
			pos = i + j + 1;
			copy[pos] = current % 10;
		}
		copy[i] = carry;

		// add to result
		if (bignum_add2(result, copy, resultLength)) {
			res = -1; // overflow
			break;
		}
	}
	free(copy);
	return res;
}

void bignum_copy(unsigned int bignum[], unsigned int copy[] /* out */, unsigned int length) {
	unsigned int i;
	for (i = 0; i < length; ++i) {
		copy[i] = bignum[i];
	}
}

/*
 * Prints a number represented as an array.
 */
void bignum_print(unsigned int sum[], unsigned int length) {
	unsigned int i;
	printf("\n");
	for (i = 0; i < length; ++i) {
		printf("%d", sum[i]);
	}
	printf("\n");
	printf("\n");
}

unsigned int bignum_sumOfDigits(unsigned int number[], unsigned int length) {
	unsigned int sum, i;
	sum = 0;
	for (i = 0; i < length; ++i) {
		sum += number[i];
	}
	return sum;
}

/*
* Returns 1 if the number is contained in the array, otherwise 0.
* The numbers in the array and the number must all have same length.
*/
int bignum_contains(unsigned int **array, unsigned int arrayLength, unsigned int *number, unsigned int length) {
	unsigned int i, j;
	unsigned int *elm;
	int seen;
	for (i = 0; i < arrayLength; ++i) {
		elm = array[i];
		seen = 1;
		for (j = 0; j < length; ++j) {
			if (elm[j] != number[j]) {
				seen = 0;
				break;
			}
		}
		if (seen) { // found a match
			return 1;
		}
	}
	return 0;
}

int bignum_equals(unsigned int *n1, unsigned int *n2, unsigned int length) {
	unsigned int i;
	for (i = 0; i < length; ++i) {
		if (n1[i] != n2[i]) {
			return 0;
		}
	}
	return 1;
}
