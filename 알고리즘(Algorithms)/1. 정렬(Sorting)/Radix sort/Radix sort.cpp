#include <iostream>
using namespace std;

void RADIX_SORT(int A[], int d, int n)
{
	int *C = new int[10];
	int *B = new int[n+1];
	for (int i = 1; i <= n; i++) B[i] = 0;

	for (int i = 1; i <= d; i++) {
		int p = 1;
		for (int j = 1; j <= i - 1; j++) p *= 10;
		for (int j = 0; j <= 9; j++) C[j] = 0;
		for (int j = 1; j <= n; j++) C[(A[j] / p) % 10]++;
		for (int j = 1; j <= 9; j++) C[j] = C[j - 1] + C[j];
		for (int j = n; j >= 1; j--) {
			B[C[(A[j] / p) % 10]] = A[j];
			C[(A[j] / p) % 10]--;
		}
		for (int j = 1; j <= n; j++) A[j] = B[j];
	}

	delete C, B;
}

int main(void)
{
	int A[8] = { 0,329,457,657,839,436,720,355 };
	RADIX_SORT(A, 3, 7);
	for (int i = 1; i <= 7; i++) printf("%d ", A[i]);
	return 0;
}