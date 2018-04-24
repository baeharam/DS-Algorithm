#include <iostream>

// 쪼개진 요소들을 정렬하여 합친다.
void merge(int *list, int first, int mid, int last)
{
	// 원본 배열에 복사할 때 사용하는 최대 인덱스가 last이므로
	// 할당하려는 배열의 크기를 last+1로 만든다.
	int len = last + 1;

	// 정렬하기 위한 배열 할당
	int *tempList = new int[len];

	// 비교를 위한 index1, index2 초기화
	int index1 = first, index2 = mid + 1;

	// tempList의 인덱스 k
	int k = first;
	
	// 쪼개진 두개의 배열에 대해 정렬한다.
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

	// 아직 정렬되지 않고 남아있는 쪽의 모든 요소를
	// tempList로 옮긴다.
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

	// tempList의 모든 요소를 list로 복사한다.
	for (int i = first; i <= last; i++)
		list[i] = tempList[i];

	// tempList 메모리 해제
	delete[] tempList;
}

// 배열을 재귀적으로 쪼갠다.
void mergeSort(int *list, int first, int last)
{
	// first<last가 아니라면 first=last인 경우밖에 없는데
	// 이러면 배열의 요소가 1개이므로 쪼갤 필요 없음
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