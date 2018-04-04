#include <iostream>
#include <algorithm>

class Heap {
private:
	int *heap;
	int capacity; // 힙의 크기
	int currentSize; // 현재 힙에 있는 원소의 개수

public:
	Heap(int size);
	~Heap();
	void Insert(int data);
	void extractMax();
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
	// 원소개수의 인덱스 = 마지막 인덱스 (0부터 시작이므로)
	int current = currentSize;

	if (current == capacity) {
		std::cout << "힙이 가득찼습니다\n";
		return;
	}

	printf("%d를 삽입했습니다..\n", data);

	// 가장 마지막 위치에 데이터 삽입
	heap[current] = data;

	// 부모노드의 위치
	int root = (current - 1) / 2;

	// 현재노드가 부모노드보다 크면 바꾸고 현재노드, 부모노드 업데이트
	while (heap[current] > heap[root]) {
		std::swap(heap[current], heap[root]);
		current = root;
		root = (current - 1) / 2;
	}

	// 원소의 개수 증가
	currentSize++;
}

void Heap::Print()
{
	printf("-----------------------------------------\n");
	for (int i = 0; i < currentSize; i++) printf("%d ", heap[i]);
	printf("\n");
	printf("-----------------------------------------\n");
}

void Heap::extractMax()
{
	// 힙에 원소가 없는 경우
	if (currentSize == 0) return;
	// Insert함수로 +1 된 것을 원상복귀
	currentSize--;
	

	// 루트 노드와 가장 마지막 노드를 바꾼다.
	std::swap(heap[0], heap[currentSize]);
	printf("%d를 힙에서 삭제했습니다.\n", heap[currentSize]);

	// 가장 마지막 노드 삭제
	heap[currentSize] = NULL;

	// 루트부터 왼쪽자식노드, 오른쪽자식노드를 검사해가면서 위치 바꿔야 하므로 미리 선언
	int root = 0, leftchild, rightchild;

	// 루트노드가 현재 크기를 넘어가지 않는 경우
	while (root<=currentSize) {
		leftchild = (root + 1) * 2 - 1;
		rightchild = (root + 1) * 2;

		// 자식노드가 존재하지 않음 
		// (왼쪽 자식노드가 원소의 개수보다 크다는 건 없다는 얘기 = 오른쪽도 없다는 얘기)
		if (leftchild > currentSize) break; 

		// 왼쪽 자식노드만 존재함
		// (오른쪽 자식노드가 원소의 개수보다 크다는 건 없다는 얘기)
		else if (rightchild > currentSize) {
			if (heap[root] < heap[leftchild]) {
				std::swap(heap[root], heap[leftchild]);
				root = leftchild;
			}
			else break;
		}

		// 둘 다 존재함
		else {
			// 루트노드보다 왼쪽 자식노드가 클 경우
			if (heap[root] < heap[leftchild]) {
				// 왼쪽 자식노드보다 오른쪽 자식노드가 클 경우
				if (heap[leftchild] < heap[rightchild]) {
					std::swap(heap[root], heap[rightchild]);
					root = rightchild;
				}
				// 왼쪽 자식노드가 오른쪽 자식노드보다 클 경우
				else {
					std::swap(heap[root], heap[leftchild]);
					root = leftchild;
				}
			}
			// 루트노드보다 왼쪽 자식노드가 작지만 오른쪽 자식노드가 클 경우
			else if (heap[root] < heap[rightchild]) {
				std::swap(heap[root], heap[rightchild]);
				root = rightchild;
			}
			else break;
		}
	}
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

	h.extractMax();
	h.Print();

	h.extractMax();
	h.Print();
	h.extractMax();
	h.Print();

	return 0;
}