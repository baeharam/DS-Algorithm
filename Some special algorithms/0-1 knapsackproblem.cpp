#include <cstdio>

// 보석의 최대개수를 100개, knapsack의 최대 크기를 100이라고 하자.
int knapsack[101][101];
int jewel[101][2]; // jewel[][0]=jewel의 크기, jewel[][1]=jewel의 값

int main(void)
{
	int n, k; scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d %d", &jewel[i][0], &jewel[i][1]);

	// jewel의 개수가 0이라면 knapsack에 들어간 jewel의 가치는 0
	for (int w = 0; w <= k; w++) knapsack[0][w] = 0;


	for (int i = 1; i <= n; i++) {
		// knapsack의 크기가 0이라면 어떤 jewel도 들어갈 수 없으므로 또한 0
		knapsack[i][0] = 0;

		// wi=jewel의 크기, bi=jewel의 가격(benefit)으로 설정
		int wi = jewel[i][0], bi = jewel[i][1];

		for (int w = 1; w <= k; w++) {
			if (wi <= w) {
				if (bi + knapsack[i - 1][w - wi] > knapsack[i - 1][w])
					knapsack[i][w] = bi + knapsack[i - 1][w - wi];
				else
					knapsack[i][w] = knapsack[i - 1][w];
			}
			else
				knapsack[i][w] = knapsack[i - 1][w];
		}
	}

	printf("최종 답 : %d\n", knapsack[n][k]);
	return 0;
}