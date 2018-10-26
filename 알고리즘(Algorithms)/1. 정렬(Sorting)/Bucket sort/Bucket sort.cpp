#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void InsertionSort(std::vector<double>& arr)
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
	int n = 11;
	// n���� ��Ŷ ����, �� 
	std::vector<double>* bucket = new std::vector<double>[n];

	// index 1���� ����
	double arr[12] = { 0,0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68,0.01 };
	
	// �� ���ڿ� �´� �ڸ��� ��Ŷ�� �ִ´�. ������ �Ҽ��� ���� ù��° �ڸ�
	for (int i = 1; i <= n; i++)
		bucket[(int)floor(n*arr[i])].push_back(arr[i]);
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