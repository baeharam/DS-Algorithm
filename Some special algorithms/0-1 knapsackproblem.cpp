#include <cstdio>

// ������ �ִ밳���� 100��, knapsack�� �ִ� ũ�⸦ 100�̶�� ����.
int knapsack[101][101];
int jewel[101][2]; // jewel[][0]=jewel�� ũ��, jewel[][1]=jewel�� ��

int main(void)
{
	int n, k; scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d %d", &jewel[i][0], &jewel[i][1]);

	// jewel�� ������ 0�̶�� knapsack�� �� jewel�� ��ġ�� 0
	for (int w = 0; w <= k; w++) knapsack[0][w] = 0;


	for (int i = 1; i <= n; i++) {
		// knapsack�� ũ�Ⱑ 0�̶�� � jewel�� �� �� �����Ƿ� ���� 0
		knapsack[i][0] = 0;

		// wi=jewel�� ũ��, bi=jewel�� ����(benefit)���� ����
		int wi = jewel[i][0], bi = jewel[i][1];

		printf("====================i = %d===================\n", i);

		for (int w = 1; w <= k; w++) {
			printf("-----------------------\n");
			printf("        w = %d         \n", w);
			printf("-----------------------\n");
			if (wi <= w) {
				printf("wi(%d)<=w(%d)�� ���!!\n\n", wi, w);
				if (bi + knapsack[i - 1][w - wi] > knapsack[i - 1][w]) {
					printf("bi(%d)+B[%d][%d]>B[%d][%d]�̹Ƿ� B[%d][%d]=bi(%d)+B[%d][%d]=%d�̴�.\n",
						bi, i - 1, w - wi, i - 1, w, i, w, bi, i - 1, w - wi,bi+knapsack[i-1][w-wi]);
					knapsack[i][w] = bi + knapsack[i - 1][w - wi];
				}
				else {
					printf("bi(%d)+B[%d][%d]<=B[%d][%d]�̹Ƿ� B[%d][%d]=B[%d][%d]=%d�̴�.\n",
						bi, i - 1, w - wi, i - 1, w, i, w, i - 1, w,knapsack[i-1][w]);
					knapsack[i][w] = knapsack[i - 1][w];
				}
			}
			else {
				printf("wi(%d)>w(%d)�̹Ƿ� B[%d][%d]=B[%d][%d]=%d�̴�.\n", wi, w, i, w, i - 1, w, knapsack[i - 1][w]);
				knapsack[i][w] = knapsack[i - 1][w];
			}
		}
	}
	printf("-----------------------\n\n");
	printf("���� �� : %d\n", knapsack[n][k]);
	return 0;
}