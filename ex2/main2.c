#include <stdio.h>
int go(int A[10]);

int main()
{
	int array[10] = {2, 1, 2, 1, 1, 1, 1, 1, 1, 1};
	int answer = go(array);
	printf("this is you answer: %d", answer);

	return 0;
}