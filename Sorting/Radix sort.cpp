#include <iostream>
#include <queue>

int main(void)
{
	int arr[8] = { 170, 45, 75, 90, 2, 24, 802, 66 };
	std::queue<int> radix[10]; // �ڸ����� ���� ť �迭

	int max = arr[0];
	int d = 1; // �ִ��ڸ���

	// �ִ� �ڸ����� ���ϱ� ���ؼ� �ִ��� ã�Ƴ���.
	for (int i = 1; i < 8; i++)
		if (max < arr[i]) max = arr[i];

	// �ִ� �ڸ����� ���س���.
	while (max/10){
		d *= 10;
		max /= 10;
	}

	int mod = 10;
	int dMin = 1;

	while (dMin<=d){
		// �ڸ����� ���� ť�� ����ִ´�.
		for (int i = 0; i < 8; i++){
			radix[(arr[i] % mod)/dMin].push(arr[i]);
		}

		// ť�� �� ������ �ڸ��� ũ�� ������ �ٽ� �迭�� ����ִ´�.
		for (int i = 0, j = 0; i < 10;){
			if (radix[i].size()){
				arr[j++] = radix[i].front();
				radix[i].pop();
			}
			else i++;
		}

		dMin *= 10;
		mod *= 10;
	}

	for (int i = 0; i < 8; i++) std::cout << arr[i] << ' ';

	return 0;
}