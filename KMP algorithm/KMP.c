#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 패턴의 각 길이에 대해서 pi를 구하는 함수
// 즉, prefix=suffix를 만족하는 longest prefix를 찾는다 왜? 비교가 필요없는 부분은 지나가야 하지만,
// 패턴안에서 반복되는 부분이 있다면 비교해보아야 하므로!!
int* COMPUTE_PREFIX_FUNCTION(char P[])
{
	int m = strlen(P + 1); // 인덱스가 1부터
	int *PI = (int*)malloc(sizeof(int)*(m + 1)); // 원래 길이만큼 받았으므로 할당할 때는 1 더해주어야 한다.
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
	char T[256] = ""; // 텍스트
	char P[256] = ""; // 패턴
	scanf("%s %s", T + 1, P + 1); // 인덱스를 1부터 취급하기 위해서
	// 텍스트와 패턴의 길이 계산(인덱스가 1부터이므로 P의 길이를 계산하면 안되고 P+1의 길이를 계산해야됨)
	int n = strlen(T+1), m = strlen(P+1); 

	// 패턴의 prefix=suffix인 longest prefix를 확인하고 그 테이블을 PI에 받는다.
	int *PI = COMPUTE_PREFIX_FUNCTION(P);


	int q = 0; // 패턴과 매칭되는 문자의 개수
	for (int i = 1; i <= n; i++) {
		// q는 패턴의 index이고 i는 문자열의 index
		// q가 이전에 매칭되었었고, 다음 패턴문자와 문자열의 문자가 다르다면 이전에 매칭되었던 index로 이동한다.
		while (q > 0 && P[q + 1] != T[i]) q = PI[q];
		// 다음 패턴문자와 문자열의 문자가 같으면 q의 index를 증가시킨다.
		if (P[q + 1] == T[i]) q = q + 1;
		// q와 m이 같다는 것은 패턴이 부분 문자열과 모두 일치한 경우이므로 shift는 i-m이다.
		// 다음에 찾을 부분문자열을 위해서 q=PI[q]를 해준다.
		if (q == m) {
			printf("Pattern occurs with shift %d\n", i - m);
			q = PI[q];
		}
	}
	free(PI);
	return 0;
}