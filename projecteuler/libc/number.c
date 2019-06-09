#include "number.h"

// Adds n2 to n1, returns the result in n1
// n1 should be the larger number (more digits)
void Number_add(Number *n1 /* in/out*/, Number *n2) {
    int i, idx1, idx2, digit, carry;
    carry = 0;
    for (i = 0; i < n2->digits; ++i) {
        idx1 = n1->length - 1 - i;
        idx2 = n2->length - 1 - i;
        digit = carry + n1->array[idx1] + n2->array[idx2];
        carry = digit / 10;
        n1->array[idx1] = digit % 10;
    }
    for (; carry && i < n1->digits; ++i) {
        idx1 = n1->length - 1 - i;
        digit = carry + n1->array[idx1];
        carry = digit / 10;
        n1->array[idx1] = digit % 10;
    }
    if (carry) {
        n1->array[idx1 - 1] = carry;
        ++n1->digits;
    }
}

void Number_addOne(Number *number) {
	int digit, carry, i;
	carry = 1;
	for (i = number->length - 1; i >= number->length - number->digits; --i) {
		digit = number->array[i] + carry;
		number->array[i] = digit % 10;
		carry = digit / 10;
		if (!carry) {
			return;
		}
	}
	number->array[number->length - number->digits - 1] = carry;
	++number->digits;
}

void Number_addTwo(Number *number) {
	int digit, carry, i;
	digit = number->array[number->length - 1] + 2;
	number->array[number->length - 1] = digit % 10;
	carry = digit / 10;
	if (!carry) {
		return;
	}
	for (i = number->length - 2; i >= number->length - number->digits; --i) {
		digit = number->array[i] + carry;
		number->array[i] = digit % 10;
		carry = digit / 10;
		if (!carry) {
			return;
		}
	}
	number->array[number->length - number->digits - 1] = carry;
	++number->digits;
}

// 1 if n1 > n2
// 0 if n1 == n2
// -1 if n1 < n2
int Number_compare(Number *n1, Number *n2) {
	int i, idx, n1digit, n2digit;
	if (n1->digits > n2->digits) {
		return 1;
	} else if (n2->digits > n1->digits) {
		return -1;
	} else {
		// same number of digits
		for (i = 0; i < n1->digits; ++i) {
			idx = n1->length - n1->digits + i;
			n1digit = n1->array[idx];
			n2digit = n2->array[idx];
			if (n1digit > n2digit) {
				return 1;
			} else if (n2digit > n1digit) {
				return -1;
			}
		}
		// numbers are equal
		return 0;
	}
}

void Number_copy(Number *in, Number *out) {
    int i;
    out->length = in->length;
    out->digits = in->digits;
    for (i = 0; i < in->length; ++i) {
        out->array[i] = in->array[i];
    }
}

void Number_delete(Number *n) {
    free(n->array);
    free(n);
}

// Divides a number by 2
void Number_divTwo(Number *number) {
	int i, idx, current, digit, carry, digits;
	carry = 0;
	for (i = 0; i < number->digits; ++i) {
		idx = number->length - number->digits + i;
		current = number->array[idx] + (carry * 10);
		digit = current / 2; // XXX shift
		carry = current % 2;
		number->array[idx] = digit;
	}
	// Remove leading zeroes
	digits = number->digits;
	for (i = 0; i < digits; ++i) {
		idx = number->length - digits + i;
		if (number->array[idx]) {
			break;
		}
		--number->digits;
	}
}

void Number_fromInt(Number *number, int n) {
    int pos = number->length - 1;
    while (n > 0) {
        number->array[pos--] = n % 10;
        n /= 10;
    }
    number->digits = number->length - (pos + 1);
}

void Number_insert(Number *number, int index, int elm) {
    int i;
    index += number->length - number->digits - 1; // Relative to digits used
    // Shift left
    for (i = number->length - number->digits - 1; i < index; ++i) {
        number->array[i] = number->array[i + 1];
    }
    // Insert
    number->array[index] = elm;
    ++number->digits;
}

int Number_isBouncy(Number *number) {
	int i, pos, digit0, digit1, inc, dec;
	inc = 0;
	dec = 0;
	for (i = 1; i < number->digits; ++i) {
		pos = number->length - number->digits + i;
		digit0 = number->array[pos - 1];
		digit1 = number->array[pos];
		if (digit1 > digit0) {
			inc = 1;
			if (dec) {
				return 1;
			}
		} else if (digit1 < digit0) {
			dec = 1;
			if (inc) {
				return 1;
			}
		}
	}
	return 0;
}

int Number_isPalindrome(Number *number) {
	int i, j;
	if (number->digits < 1) {
		return 0;
	}
	i = number->length - number->digits;
	j = number->length - 1;
	for ( ; i < j; ++i, --j) {
		if (number->array[i] != number->array[j]) {
			return 0;
		}
	}
	return 1;
}

int Number_isPermutation(Number *n1, Number *n2) {
	int i, digit;
	int count[10];
	if (n1->digits != n2->digits) {
		return 0;
	}
	// Initialize count of all digits to zero
	for (i = 0; i < 10; ++i) {
		count[i] = 0;
	}
	// Increase from n1
	for (i = 0; i < n1->digits; ++i) {
		digit = n1->array[n1->length - i - 1];
		++count[digit];
	}
	// Decrease from n2
	for (i = 0; i < n2->digits; ++i) {
		digit = n2->array[n2->length - i - 1];
		--count[digit];
	}
	// Check if all are zero
	for (i = 0; i < 10; ++i) {
		if (count[i]) {
			return 0;
		}
	}
	return 1;
}

// n1 and n2 must have same length
void Number_mul(Number *n1, Number *n2, Number *result /* out */) {
	int n1digit, n2digit,
		tempPos, // Starting pos in temp number
		i, j, // indices into n1 and n2
		current, // current multiplication
		digit, // current digit
		carry; // carry of current multiplication
	Number *temp;
    temp = Number_new(result->length);
	for (i = 0; i < n1->digits; ++i) {
		carry = 0;
		// take digit from n1
		n1digit = n1->array[n1->length - 1 - i];
		// init temp number with enough zeroes at the end
        temp->digits = 0;
		tempPos = temp->length - 1 - i;
		for (j = 0; j < i; ++j) {
			temp->array[temp->length - 1 - j] = 0;
			++temp->digits;
		}
		// multiply n1 digit through n2 into temp
		for (j = 0; j < n2->digits; ++j) {
			n2digit = n2->array[n2->length - 1 - j];
			current = (n1digit * n2digit) + carry;
			digit = current % 10;
			carry = current / 10;
			temp->array[tempPos--] = digit;
			++temp->digits;
		}
		if (carry) {
			temp->array[tempPos] = carry;
			++temp->digits;
		}
		// add temp to result
		// XXX: ackward adding, since first arg to add must be the larger number
		if (result->digits) {
			Number_add(temp /* out */, result);
		}
		Number_copy(temp, result /* out */);
	}
    Number_delete(temp);
}

Number *Number_new(int length) {
    Number *n;
    n = (Number*) malloc(sizeof(Number));
    n->digits = 0;
    n->length = length;
    n->array = (int*) malloc(sizeof(int) * length);
    return n;
}

// Number must be a copy, as it is mutated
// Assumes perm is allocated, and with digits == 0
// n is index
void Number_nthPerm(Number *number, int index, Number *perm /* out */) {
    int elm, divider, newIndex;
    elm = Number_pop(number);
    Number_insert(perm, 0, elm);
    divider = 2; //  len(perm)  + 1
    while (number->digits > 0) {
        newIndex = index % divider;
        index /= divider;
        elm = Number_pop(number);
        Number_insert(perm, newIndex, elm);
        divider += 1;
    }
}

// Remove the last element and return it
int Number_pop(Number *number) {
    int i, idx, elm;
    elm = number->array[number->length - 1];
    // Shift right
    for (i = 0; i < number->digits; ++i) {
        idx = number->length - 1 - i;
        number->array[idx] = number->array[idx - 1];
    }
    if (idx > 0) {
        number->array[idx - 1] = 0; // Clear
    }
    --number->digits;
    return elm;
}

void Number_print(Number *number) {
    int i;
    for (i = number->length - number->digits; i < number->length; ++i) {
        printf("%d", number->array[i]);
    }
    printf("\n");
}

void Number_reverse(Number *in, Number *out) {
	int i;
	out->digits = in->digits;
	for (i = 0; i < in->digits; ++i) {
		out->array[out->length - out->digits + i] =
			in->array[in->length - 1 - i];
	}
}

void Number_subOne(Number *number) {
	int i, idx, digit;
	for (i = 0; i < number->digits; ++i) {
		idx = number->length - 1 - i;
		digit = number->array[idx];
		if (digit) {
			--number->array[idx];
			break;
		}
	}
	// If we did not seek through number we are done
	if (i != number->digits - 1) {
		return;
	}
	// If first digit became zero, decrease digits
	if (!number->array[idx]) {
		--number->digits;
	}
	// Change all zeroes to nines
	for (i = idx + 1; i < number->length; ++i) {
		if (!number->array[i]) {
			number->array[i] = 9;
		}
	}
}

int Number_sumOfDigits(Number *number) {
	int sum, i;
	sum = 0;
	for (i = 0; i < number->digits; ++i) {
		sum += number->array[number->length - 1 - i];
	}
	return sum;
}

int Number_toInt(Number *number) {
    int n, i, factor;
    n = 0;
    factor = 1;
    for (i = number->length - 1; i >= number->length - number->digits; --i) {
        n += number->array[i] * factor;
        factor *= 10;
    }
    return n;
}
