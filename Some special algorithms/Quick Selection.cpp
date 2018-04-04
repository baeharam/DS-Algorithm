#include <iostream>
#include <cstdio>

int A[5000001];

// pivot�� ù��° ���� ���
int Partition(int list[], int left, int right)
{
	int pivot = list[left];
	int i = left + 1, j = right;

	while (i <= j) {
		while (list[i] <= pivot && i <= right) i++;
		while (list[j] >= pivot && j >= (left + 1)) j--;
		if (i <= j) std::swap(list[i], list[j]);
	}
	std::swap(list[left], list[j]);
	return j;
}

/* pivot�� ������ ���� ���
int Partition(int list[], int left, int right)
{
	int pivot = list[right];
	int i = left - 1, j;

	for (j = left; j < right; j++) {
		if (list[j] < pivot) {
			i++;
			std::swap(list[i], list[j]);
		}
	}

	i++;
	std::swap(list[i], list[right]);
	return i;
}*/

// �������� �Լ� (��������� k�� ������Ű�� �����ȿ� ������ ȣ��ȴ�.)
int quickSelect(int list[], int left, int right, int k)
{
	int nth = Partition(list, left, right);

	if (nth == k) return list[nth];
	else if (nth > k) quickSelect(list, left, nth - 1, k);
	else if (nth < k) quickSelect(list, nth + 1, right, k);
}

int main(void)
{
	int n, k; std::cin >> n >> k;
	k--;
	for (int i = 0; i < n; i++) scanf("%d", &A[i]);
	std::cout << quickSelect(A, 0, n - 1, k);

	return 0;
}