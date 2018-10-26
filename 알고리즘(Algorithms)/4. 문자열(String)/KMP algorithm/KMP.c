#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// ������ �� ���̿� ���ؼ� pi�� ���ϴ� �Լ�
// ��, prefix=suffix�� �����ϴ� longest prefix�� ã�´� ��? �񱳰� �ʿ���� �κ��� �������� ������,
// ���Ͼȿ��� �ݺ��Ǵ� �κ��� �ִٸ� ���غ��ƾ� �ϹǷ�!!
int* COMPUTE_PREFIX_FUNCTION(char P[])
{
	int m = strlen(P + 1); // �ε����� 1����
	int *PI = (int*)malloc(sizeof(int)*(m + 1)); // ���� ���̸�ŭ �޾����Ƿ� �Ҵ��� ���� 1 �����־�� �Ѵ�.
	PI[1] = 0;
	int k = 0;
	for (int q = 2; q <= m; q++) {
		while (k > 0 && P[k + 1] != P[q]) k = PI[k];
		if (P[k + 1] == P[q]) k = k + 1;
		PI[q] = k;
	}
	return PI;
}

int main(void)
{
	char T[256] = ""; // �ؽ�Ʈ
	char P[256] = ""; // ����
	scanf("%s %s", T + 1, P + 1); // �ε����� 1���� ����ϱ� ���ؼ�
	// �ؽ�Ʈ�� ������ ���� ���(�ε����� 1�����̹Ƿ� P�� ���̸� ����ϸ� �ȵǰ� P+1�� ���̸� ����ؾߵ�)
	int n = strlen(T+1), m = strlen(P+1); 

	// ������ prefix=suffix�� longest prefix�� Ȯ���ϰ� �� ���̺��� PI�� �޴´�.
	int *PI = COMPUTE_PREFIX_FUNCTION(P);


	int q = 0; // ���ϰ� ��Ī�Ǵ� ������ ����
	for (int i = 1; i <= n; i++) {
		// q�� ������ index�̰� i�� ���ڿ��� index
		// q�� ������ ��Ī�Ǿ�����, ���� ���Ϲ��ڿ� ���ڿ��� ���ڰ� �ٸ��ٸ� ������ ��Ī�Ǿ��� index�� �̵��Ѵ�.
		while (q > 0 && P[q + 1] != T[i]) q = PI[q];
		// ���� ���Ϲ��ڿ� ���ڿ��� ���ڰ� ������ q�� index�� ������Ų��.
		if (P[q + 1] == T[i]) q = q + 1;
		// q�� m�� ���ٴ� ���� ������ �κ� ���ڿ��� ��� ��ġ�� ����̹Ƿ� shift�� i-m�̴�.
		// ������ ã�� �κй��ڿ��� ���ؼ� q=PI[q]�� ���ش�.
		if (q == m) {
			printf("Pattern occurs with shift %d\n", i - m);
			q = PI[q];
		}
	}
	free(PI);
	return 0;
}