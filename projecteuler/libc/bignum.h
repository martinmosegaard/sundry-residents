void bignum_init(unsigned int sum[], unsigned int length);

int bignum_add(unsigned int sum[], unsigned int length, unsigned long number);

int bignum_add2(unsigned int sum1[] /* in / out */, unsigned int sum2[], unsigned int length);

int bignum_mul(unsigned int sum[], unsigned int length, unsigned long number);

int bignum_mul2(unsigned int sum1[], unsigned int sum2[], unsigned int length,
			    unsigned int result[] /* out */, unsigned int resultLength);

int bignum_square(unsigned int number[], unsigned int length,
				  unsigned int result[] /* out */, unsigned int resultLength);

void bignum_copy(unsigned int bignum[], unsigned int copy[] /* out */, unsigned int length);

void bignum_print(unsigned int sum[], unsigned int length);

unsigned int bignum_sumOfDigits(unsigned int number[], unsigned int length);

int bignum_contains(unsigned int **array, unsigned int arrayLength, unsigned int *number, unsigned int length);

int bignum_equals(unsigned int *n1, unsigned int *n2, unsigned int length);
