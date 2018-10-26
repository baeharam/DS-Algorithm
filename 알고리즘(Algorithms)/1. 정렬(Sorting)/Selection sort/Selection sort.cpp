#include <iostream>

void SelectionSort(int *list,int last)
{
	int max, j,max_index;
	for (int i = last-1; i >= 1; i--){
		max = 0, j = 0;
		for (j = i; j >= 0; j--)
			if (max < list[j]){ max = list[j]; max_index = j; }
		std::swap(list[max_index], list[i]);
	}
}

int main(void)
{
	int list[6] = { 23, 12, 4, 9, 67, 0 };
	SelectionSort(list, 6);
	for (int i = 0; i < 6; i++) std::cout << list[i] << " ";
	return 0;
}