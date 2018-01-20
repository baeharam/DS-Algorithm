#include <iostream>

const int max = 10000;

int main(void)
{
	int countList[max + 1] = { 0 };
	int n,num=0; std::cin >> n;
	int *List = new int[n+1], *sortList = new int[n+1];

	// 각 숫자가 등장한 횟수만큼 countList 값 설정
	for (int i = 1; i <= n; i++){
		std::cin >> num;
		List[i] = num;
		countList[num]++;
		sortList[i] = 0;
	}

	// 숫자의 누적합으로 다시 설정
	for (int i = 1; i < max + 1; i++)
		countList[i] += countList[i - 1];

	for (int i = 1; i <= n; i++){
		sortList[countList[List[i]]] = List[i];
		countList[List[i]]--;
	}

	for (int i = 1; i <= n; i++){
		if (sortList[i]!=0)
			std::cout << sortList[i] << " ";
	}

	delete[] List, sortList;

	return 0;
}