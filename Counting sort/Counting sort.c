#include <stdio.h>
#include <stdlib.h>

// �迭�� �Լ��� ���ڷ� ���޵Ǹ� �������̱� ������ �迭�� ���̸� ���� �� ����ϴ�
// sizeof(A)/sizeof(A[0])�� ������ �ʴ´�... �̰� �����˴ٴ�...
void COUNTING_SORT(int A[], int B[], int k, int n)
{
	int *C = (int*)malloc(sizeof(int)*(k + 1));
	for (int i = 0; i <= k; i++) C[i] = 0;
	for (int j = 1; j <= n; j++) 
		C[A[j]]++;
	for (int i = 1; i <= k; i++) C[i] = C[i] + C[i - 1];
	for (int j = n; j >= 1; j--) {
		B[C[A[j]]] = A[j];
		C[A[j]]--;
	}
	free(C);
}

int main(void)
{
	int A[11] = { 0,2,5,4,8,1,9,2,3,10,0 };
	int B[11] = { 0 };
	COUNTING_SORT(A, B, 10,10);
	for (int i = 1; i <= 10; i++) printf("%d ", B[i]);
	return 0;
}