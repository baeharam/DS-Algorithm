#include <stdio.h>
#include <stdlib.h>


void RADIX_SORT(int A[], int d, int n)
{
	int C[2] = { 0 };
	int *B = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 1; i <= n; i++) B[i] = 0;
	
	int exp = 0;
	for (int i = 1; i <= d; i++) {
		C[0] = C[1] = 0;
		for (int j = 1; j <= n; j++) {
			C[A[j] >> exp & 1]++;
		}
		C[1] += C[0];
		for (int j = n; j >= 1; j--) {
			B[C[A[j] >> exp & 1]] = A[j];
			C[A[j] >> exp & 1]--;
		}
		for (int i = 1; i <= n; i++) A[i] = B[i];
		exp++;
	}

	free(B);
}

int main(void)
{
	int A[11] = { 0,156,728,123,453,232,919,511,671,844,100 };
	int d = 1, max = A[6];
	while (max / 2) {
		d++;
		max /= 2;
	}
	RADIX_SORT(A, d, 10);
	for (int i = 1; i <= 10; i++) printf("%d ", A[i]);

	return 0;
}