#include <stdio.h>
#include <stdlib.h>

// 배열이 함수의 인자로 전달되면 포인터이기 때문에 배열의 길이를 구할 때 사용하는
// sizeof(A)/sizeof(A[0])이 통하지 않는다... 이걸 이제알다니...
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