#include <iostream>

const int max = 10000;

int main(void)
{
	int countList[max + 1] = { 0 };
	int n,num=0; std::cin >> n;
	int *List = new int[n+1], *sortList = new int[n+1];

	// �� ���ڰ� ������ Ƚ����ŭ countList �� ����
	for (int i = 1; i <= n; i++){
		std::cin >> num;
		List[i] = num;
		countList[num]++;
		sortList[i] = 0;
	}

	// ������ ���������� �ٽ� ����
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