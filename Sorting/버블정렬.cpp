#include <iostream>

int main(void)
{
	int data[] = { 3,234,5,4,3,9,3,1 };

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8 - 1 - i; j++) {
			if (data[j] > data[j+1]) {
				int temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}
	}

	for (int i = 0; i < 8; i++) std::cout << data[i] << ' ';

	return 0;
}