#include <iostream>

int main(void)
{
	int arr[10] = { 33, 2, 45, 17, 100, 22, 22, 3, 0, 12 };

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10 - 1-i; j++){
			if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
		}
	}

	for (int i = 0; i < 10; i++) std::cout << arr[i] << " ";

	return 0;
}