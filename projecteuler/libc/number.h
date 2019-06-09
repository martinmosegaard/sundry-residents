typedef struct number {
	int *array;
	int length; // length of array
	int digits; // number of digits used
} Number;

// Adds n2 to n1, returns the result in n1.
// n1 should be the larger number.
void Number_add(Number *n1 /* in/out */, Number *n2);

// Adds 1 to a number
void Number_addOne(Number *number);

// Adds 2 to a number
void Number_addTwo(Number *number);

// 1 if n1 > n2
// 0 if n1 == n2
// -1 if n1 < n2
int Number_compare(Number *n1, Number *n2);

void Number_copy(Number *in, Number *out);

void Number_delete(Number *n);

// Divides a number by 2
void Number_divTwo(Number *number);

// Number must have been allocated with length set.
// This will set digits.
void Number_fromInt(Number *number, int n);

void Number_insert(Number *number, int index, int elm);

// Problem 112: A number that is neither decreasing nor increasing
int Number_isBouncy(Number *number);

int Number_isPalindrome(Number *number);

// Determines if n1 is a permutation of n2 (and vice-versa)
int Number_isPermutation(Number *n1, Number *n2);

void Number_mul(Number *n1, Number *n2, Number *result /* out */);

Number *Number_new(int length);

// Modifies number (must be a copy)
// Assumes perm is allocated, and with digits == 0
// n is index
void Number_nthPerm(Number *number, int index, Number *perm /* out */);

// Remove the last element and return it
int Number_pop(Number *number);

void Number_print(Number *number);

void Number_reverse(Number *in, Number *out);

// Subtracs 1 from a number
void Number_subOne(Number *number);

int Number_sumOfDigits(Number *number);

int Number_toInt(Number *number);
