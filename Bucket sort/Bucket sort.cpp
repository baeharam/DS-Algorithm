#include <iostream>
#include <vector>
#include <algorithm>

void InsertionSort(std::vector<int>& arr)
{
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i; j >= 1; j--) {
			if (arr[j] < arr[j - 1]) 
				std::swap(arr[j],arr[j-1]);
		}
	}
}

int main(void)
{
	int n = 10;
	// n���� ��Ŷ ����
	std::vector<int>* bucket = new std::vector<int>[n];

	int arr[10] = { 0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68 };
	int arr2[10] = { 1922,2011,8144,1333,9225,3317,5314,1411,1001,9120 };

	// �� ���ڿ� �´� �ڸ��� ��Ŷ�� �ִ´�. ������ �Ҽ��� ���� ù��° �ڸ�
	for (int i = 0; i < n; i++) 
		bucket[arr2[i]/1000].push_back(arr2[i]);
	// �� �ڸ����� ���ؼ� Insertion sort�� �Ͽ� �����Ѵ�.
	for (int i = 0; i < n; i++)
		InsertionSort(bucket[i]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < bucket[i].size(); j++)
			std::cout << bucket[i][j] << " ";
	}
	delete[] bucket;
	return 0;
}