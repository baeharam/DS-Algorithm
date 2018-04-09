#include <cstdio>
#include <Windows.h>
#include <cstdlib>

// 보석의 최대개수를 100개, knapsack의 최대 크기를 100이라고 하자.
int knapsack[101][101];
int jewel[101][2]; // jewel[][0]=jewel의 크기, jewel[][1]=jewel의 값

int main(void)
{
	printf("보석의 개수와 배낭의 최대크기 입력 : ");
	int n, k; scanf("%d %d", &n, &k);
	printf("보석의 크기와 가격 입력\n\n");
	for (int i = 1; i <= n; i++) scanf("%d %d", &jewel[i][0], &jewel[i][1]);

	// jewel의 개수가 0이라면 knapsack에 들어간 jewel의 가치는 0
	for (int w = 0; w <= k; w++) knapsack[0][w] = 0;


	for (int i = 1; i <= n; i++) {
		// knapsack의 크기가 0이라면 어떤 jewel도 들어갈 수 없으므로 또한 0
		knapsack[i][0] = 0;

		// wi=jewel의 크기, bi=jewel의 가격(benefit)으로 설정
		int wi = jewel[i][0], bi = jewel[i][1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("\n====================i = %d===================\n", i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		for (int w = 1; w <= k; w++) {
			printf("-----------------------\n");
			printf("        w = %d         \n", w);
			printf("-----------------------\n");
			if (wi <= w) {
				printf("wi(%d)<=w(%d)인 경우!!\n\n", wi, w);
				if (bi + knapsack[i - 1][w - wi] > knapsack[i - 1][w]) {
					printf("bi(%d)+B[%d][%d]>B[%d][%d]이므로 ",bi, i - 1, w - wi, i - 1, w);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					printf("B[%d][%d] = bi(%d) + B[%d][%d] = %d이다.\n", i, w, bi, i - 1, w - wi, bi + knapsack[i - 1][w - wi]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					knapsack[i][w] = bi + knapsack[i - 1][w - wi];
				}
				else {
					printf("bi(%d)+B[%d][%d]<=B[%d][%d]이므로 ", bi, i - 1, w - wi, i - 1, w);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					printf("B[%d][%d] = B[%d][%d] = %d이다.\n", i, w, i - 1, w, knapsack[i - 1][w]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					knapsack[i][w] = knapsack[i - 1][w];
				}
			}
			else {
				printf("wi(%d)>w(%d)이므로 ", wi, w);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("B[%d][%d] = B[%d][%d] = %d이다.\n", i, w, i - 1, w, knapsack[i - 1][w]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				knapsack[i][w] = knapsack[i - 1][w];
			}
		}
	}
	printf("-----------------------\n\n");
	printf("최종 답 : %d\n", knapsack[n][k]);
	system("pause");
	return 0;
}