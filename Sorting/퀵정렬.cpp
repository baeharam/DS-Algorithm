#include <iostream>

void Swap(int left, int right, int *data)
{
	int temp = data[left];
	data[left] = data[right];
	data[right] = temp;
}

int partition(int left, int right, int *data)
{
	int pivot = (left + right) / 2;

	while (left < right){
		while ((data[left] < data[pivot]) && (left < right))
			left++;
		while ((data[right] >= data[pivot]) && (left < right))
			right--;
		if (left < right)
			Swap(left, right, data);
	}

	Swap(left, pivot, data);

	return left;
}

void quicksort(int begin, int end, int *data)
{
	if (begin < end){
		int p = partition(begin, end, data);
		quicksort(begin, p, data);
		quicksort(p + 1, end, data);
	}
}

int main(void)
{
	int n = 0;
	std::cin >> n;
	int *list = new int[n];

	for (int i = 0; i<n; i++) std::cin >> list[i];
	quicksort(0, n - 1, list);
	for (int i = 0; i<n; i++) std::cout << list[i] << std::endl;

	delete[] list;
	return 0;
}