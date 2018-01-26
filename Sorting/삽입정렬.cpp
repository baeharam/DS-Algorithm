#include <iostream>

int main(void)
{
	int arr[20] = {1,2,3,4,5,6,6,1,2,333,4,3,2,5,6,7,0,11,23,40 };

	int temp; //임시변수

	for (int i = 1; i < 20; i++){
		temp = arr[i];
		for (int j = i - 1; j >= 0; j--){
			if (arr[j]>temp)
				std::swap(arr[j], arr[j+1]);
		}
	}

	for (int i = 0; i < 20; i++) std::cout << arr[i] << " ";

	return 0;
}