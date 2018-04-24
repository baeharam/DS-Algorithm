#include <iostream>
#include <algorithm>
#include <cstdio>

class Heap {
private:
	int *heap;
	int capacity; // 힙의 크기
	int currentSize; // 현재 힙에 있는 원소의 개수

public:
	Heap(int size);
	~Heap();
	void Insert(int data);
	void extractMin();
	void Print();
};

Heap::Heap(int size) :capacity(size), currentSize(0)
{
	heap = new int[capacity];
}

Heap::~Heap()
{
	delete[] heap;
}

void Heap::Insert(int data)
{
	// currentSize가 insert되면 크기가 1 증가하므로 바로 capacity와 비교해주면 된다.
	if (currentSize == capacity) {
		printf("힙이 가득찼습니다.");
		return;
	}

	// currentSize는 처음 0부터 시작
	int current = currentSize;

	// heap 마지막에 삽입
	heap[current] = data;

	// 부모노드의 인덱스 계산. 인덱스가 0부터임으로 -1해주어야됨
	int parent = (current - 1) / 2;

	// parent의 값이 current보다 크면 바꾼다.
	// 원리는 마지막에 노드를 삽입해서 루트에 최솟값이 오도록 맞춰주는 작업이다.
	while (heap[parent] > heap[current]) {
		std::swap(heap[current], heap[parent]);
		current = parent;
		parent = (current - 1) / 2;
	}

	currentSize++;
}

void Heap::Print()
{
	printf("-----------------------------------------\n");
	for (int i = 0; i < currentSize; i++) printf("%d ", heap[i]);
	printf("\n");
	printf("-----------------------------------------\n");
}

void Heap::extractMin()
{
	if (currentSize == 0) {
		printf("힙이 비었습니다.\n");
		return;
	}
	// Insert 함수에서 증가했기 때문에 1 빼주어야 됨.
	int current = currentSize - 1;
	
	// 마지막 노드와 루트노드를 바꾼다.
	std::swap(heap[0], heap[current]);
	printf("%d를 힙에서 삭제했습니다.\n", heap[current]);
	heap[current] = INT_MAX; // 마지막 노드 값 제거, 루트노드 값 제거하는 것이다.

	// 루트노드부터 왼쪽 오른쪽 노드 중 루트노드보다 작은 값 있으면 스왑하면서 루트노드에 최솟값 오도록 조정
	int parent = 0, left, right;

	// 마지막 노드까지 조사
	while (parent <= current) {
		left = parent * 2 + 1;
		right = left + 1;

		if (left > current) break;
		else if (right > current) {
			if (heap[parent] > heap[left]) {
				std::swap(heap[parent], heap[left]);
				parent = left;
			}
			else break;
		}
		else {
			if (heap[parent] > heap[left]) {
				if (heap[left] > heap[right]) {
					std::swap(heap[parent], heap[right]);
					parent = right;
				}
				else {
					std::swap(heap[parent], heap[left]);
					parent = left;
				}
			}
			else if (heap[parent] > heap[right]) {
				std::swap(heap[parent], heap[right]);
				parent = right;
			}
			else break;
		}
	}
	currentSize--;
}

int main(void)
{
	int size; scanf("%d", &size);
	Heap h(size);

	h.Insert(23);
	h.Insert(2);
	h.Insert(43);
	h.Insert(14);
	h.Insert(95);
	h.Insert(142);

	h.Print();

	h.extractMin();
	h.Print();

	h.extractMin();
	h.Print();
	h.extractMin();
	h.Print();

	return 0;
}