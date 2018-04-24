#include <cstdio>
#include <Windows.h>
#include <cstdlib>

// ������ �ִ밳���� 100��, knapsack�� �ִ� ũ�⸦ 100�̶�� ����.
int knapsack[101][101];
int jewel[101][2]; // jewel[][0]=jewel�� ũ��, jewel[][1]=jewel�� ��

int main(void)
{
	printf("������ ������ �賶�� �ִ�ũ�� �Է� : ");
	int n, k; scanf("%d %d", &n, &k);
	printf("������ ũ��� ���� �Է�\n\n");
	for (int i = 1; i <= n; i++) scanf("%d %d", &jewel[i][0], &jewel[i][1]);

	// jewel�� ������ 0�̶�� knapsack�� �� jewel�� ��ġ�� 0
	for (int w = 0; w <= k; w++) knapsack[0][w] = 0;


	for (int i = 1; i <= n; i++) {
		// knapsack�� ũ�Ⱑ 0�̶�� � jewel�� �� �� �����Ƿ� ���� 0
		knapsack[i][0] = 0;

		// wi=jewel�� ũ��, bi=jewel�� ����(benefit)���� ����
		int wi = jewel[i][0], bi = jewel[i][1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("\n====================i = %d===================\n", i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		for (int w = 1; w <= k; w++) {
			printf("-----------------------\n");
			printf("        w = %d         \n", w);
			printf("-----------------------\n");
			if (wi <= w) {
				printf("wi(%d)<=w(%d)�� ���!!\n\n", wi, w);
				if (bi + knapsack[i - 1][w - wi] > knapsack[i - 1][w]) {
					printf("bi(%d)+B[%d][%d]>B[%d][%d]�̹Ƿ� ",bi, i - 1, w - wi, i - 1, w);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					printf("B[%d][%d] = bi(%d) + B[%d][%d] = %d�̴�.\n", i, w, bi, i - 1, w - wi, bi + knapsack[i - 1][w - wi]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					knapsack[i][w] = bi + knapsack[i - 1][w - wi];
				}
				else {
					printf("bi(%d)+B[%d][%d]<=B[%d][%d]�̹Ƿ� ", bi, i - 1, w - wi, i - 1, w);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					printf("B[%d][%d] = B[%d][%d] = %d�̴�.\n", i, w, i - 1, w, knapsack[i - 1][w]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					knapsack[i][w] = knapsack[i - 1][w];
				}
			}
			else {
				printf("wi(%d)>w(%d)�̹Ƿ� ", wi, w);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("B[%d][%d] = B[%d][%d] = %d�̴�.\n", i, w, i - 1, w, knapsack[i - 1][w]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				knapsack[i][w] = knapsack[i - 1][w];
			}
		}
	}
	printf("-----------------------\n\n");
	printf("���� �� : %d\n", knapsack[n][k]);
	system("pause");
	return 0;
}