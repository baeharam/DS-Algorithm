#include <iostream>

// �ɰ��� ��ҵ��� �����Ͽ� ��ģ��.
void merge(int *list, int first, int mid, int last)
{
	// ���� �迭�� ������ �� ����ϴ� �ִ� �ε����� last�̹Ƿ�
	// �Ҵ��Ϸ��� �迭�� ũ�⸦ last+1�� �����.
	int len = last + 1;

	// �����ϱ� ���� �迭 �Ҵ�
	int *tempList = new int[len];

	// �񱳸� ���� index1, index2 �ʱ�ȭ
	int index1 = first, index2 = mid + 1;

	// tempList�� �ε��� k
	int k = first;
	
	// �ɰ��� �ΰ��� �迭�� ���� �����Ѵ�.
	while (index1 <= mid && index2 <= last){
		if (list[index1] < list[index2]){
			tempList[k] = list[index1];
			index1++;
		}
		else{
			tempList[k] = list[index2];
			index2++;
		}
		k++;
	}

	// ���� ���ĵ��� �ʰ� �����ִ� ���� ��� ��Ҹ�
	// tempList�� �ű��.
	if (index1 > mid){
		for (int i = index2; i <= last; i++){
			tempList[k] = list[i];
			k++;
		}
	}
	else if (index2 > last){
		for (int i = index1; i <= mid; i++){
			tempList[k] = list[i];
			k++;
		}
	}

	// tempList�� ��� ��Ҹ� list�� �����Ѵ�.
	for (int i = first; i <= last; i++)
		list[i] = tempList[i];

	// tempList �޸� ����
	delete[] tempList;
}

// �迭�� ��������� �ɰ���.
void mergeSort(int *list, int first, int last)
{
	// first<last�� �ƴ϶�� first=last�� ���ۿ� ���µ�
	// �̷��� �迭�� ��Ұ� 1���̹Ƿ� �ɰ� �ʿ� ����
	if (first < last){
		int mid = (first + last) / 2;
		mergeSort(list, first, mid);
		mergeSort(list, mid + 1, last);
		merge(list, first, mid, last);
	}
}

int main(void)
{
	int arr[8] = { 5, 2, 4, 7, 1, 3, 2, 6 };
	mergeSort(arr, 0, 7);
	for (int i = 0; i < 8; i++) std::cout << arr[i] << " ";
	
	return 0;
}