// Convert magnitude to int and backwards
int intToMagnitude(int i) {
	//Calcualte a number with msb 1
	const int msb = 1 << (sizeof(int) * 8 - 1);
	//Check if the number is INT_MIN and set it to 0
	if (msb == i) {
		return 0;
	}
	//If the number is positive return it
	if (!(msb & i)) {
		return i;
	}
	//Return the magnitude representation of the number
	return (-i) | msb;
}

int add(int a, int b) {
	a = intToMagnitude(a);
	b = intToMagnitude(b);
	int sum = intToMagnitude(a + b);
	//Check if an overflow or an underflow occurred
	if ((a < 0 && b < 0 && sum > 0) ||
	        (a > 0 && b > 0 && sum < 0)) {
		//Fix the sum
		sum = -sum;
	}
	return sum;
}

int sub(int a, int b) {
	a = intToMagnitude(a);
	b = intToMagnitude(b);
	int res = intToMagnitude(a - b);
	//Check if an overflow or an underflow occurred
	if (a > b && res < 0 || a < b && res > 0) {
		//Fix the result
		res = -res;
	}
	return res;
}

int multi(int a, int b) {
	a = intToMagnitude(a);
	b = intToMagnitude(b);
	int mul = intToMagnitude(a * b);
	//Check if an overflow or an underflow occurred
	if ((a < 0 && b < 0 && mul < 0) ||
	        (a > 0 && b > 0 && mul < 0) ||
	        (a > 0 && b < 0 && mul > 0) ||
	        (a < 0 && b > 0 && mul > 0 )) {
		//fix the result
		mul = -mul;
	}
	return mul;
}

int equal(int a, int b) {
	return intToMagnitude(a) == intToMagnitude(b);
}

int greater(int a, int b) {
	return intToMagnitude(a) > intToMagnitude(b);
}