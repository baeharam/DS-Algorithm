#include <stdio.h>

void swap(int arr[], int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

int Partition(int arr[], int from, int to)
{
	int pivot = arr[to];
	int i = from - 1;
	for (int j = from; j <= to - 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(arr, i, j);
		}
	}
	swap(arr, i + 1, to);
	return i + 1;
}

void quickSort(int arr[], int from, int to)
{
	if (from < to) {
		int partition = Partition(arr, from, to);
		quickSort(arr, from, partition - 1);
		quickSort(arr, partition + 1, to);
	}
}

int main(void)
{
	int arr[10] = { 2,4,5,3,9,1,0,2,3,7 };
	quickSort(arr, 0, 9);
	for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
	return 0;
}

