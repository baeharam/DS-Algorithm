#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void swap(int A[], int a, int b)
{
	int temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}

int RandomizedPartition(int A[], int p, int r)
{
	srand((unsigned)time(NULL));
	int random = (rand() % r) + p;
	int pivot = A[random];
	swap(A, random, p);
	int i = p;
	for (int j = p + 1; j <= r; j++) {
		if (A[j] <= pivot) {
			i++;
			swap(A, i, j);
		}
	}
	swap(A, i, p);
	return i;
}

int RandomizedSelect(int A[], int p, int r, int i)
{
	if (p == r) return A[p];
	int q = RandomizedPartition(A, p, r);
	int k = q - p + 1;
	if (i == k) return A[q];
	if (i < k) return RandomizedSelect(A, p, q - 1, i);
	else return RandomizedSelect(A, q + 1, r, i - k);
}

int main(void)
{
	int A[9] = { 3,1,2,4,5,2,9,14,1 };
	printf("%d", RandomizedSelect(A, 0, 8, 7));
	return 0;
}