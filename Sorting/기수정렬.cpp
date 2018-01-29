#include <iostream>
#include <queue>

int main(void)
{
	int arr[8] = { 170, 45, 75, 90, 2, 24, 802, 66 };
	std::queue<int> radix[10]; // 자리수에 대한 큐 배열

	int max = arr[0];
	int d = 1; // 최대자리수

	// 최대 자리수를 구하기 위해서 최댓값을 찾아낸다.
	for (int i = 1; i < 8; i++)
		if (max < arr[i]) max = arr[i];

	// 최대 자리수를 구해낸다.
	while (max/10){
		d *= 10;
		max /= 10;
	}

	int mod = 10;
	int dMin = 1;

	while (dMin<=d){
		// 자리수에 따라 큐에 집어넣는다.
		for (int i = 0; i < 8; i++){
			radix[(arr[i] % mod)/dMin].push(arr[i]);
		}

		// 큐에 들어간 값들을 자리수 크기 순으로 다시 배열에 집어넣는다.
		for (int i = 0, j = 0; i < 10;){
			if (radix[i].size()){
				arr[j++] = radix[i].front();
				radix[i].pop();
			}
			else i++;
		}

		dMin *= 10;
		mod *= 10;
	}

	for (int i = 0; i < 8; i++) std::cout << arr[i] << ' ';

	return 0;
}