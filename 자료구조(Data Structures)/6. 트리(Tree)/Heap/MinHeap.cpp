#include <iostream>
#include <algorithm>
#include <cstdio>

class Heap {
private:
	int *heap;
	int capacity; // ���� ũ��
	int currentSize; // ���� ���� �ִ� ������ ����

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
	// currentSize�� insert�Ǹ� ũ�Ⱑ 1 �����ϹǷ� �ٷ� capacity�� �����ָ� �ȴ�.
	if (currentSize == capacity) {
		printf("���� ����á���ϴ�.");
		return;
	}

	// currentSize�� ó�� 0���� ����
	int current = currentSize;

	// heap �������� ����
	heap[current] = data;

	// �θ����� �ε��� ���. �ε����� 0���������� -1���־�ߵ�
	int parent = (current - 1) / 2;

	// parent�� ���� current���� ũ�� �ٲ۴�.
	// ������ �������� ��带 �����ؼ� ��Ʈ�� �ּڰ��� ������ �����ִ� �۾��̴�.
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
		printf("���� ������ϴ�.\n");
		return;
	}
	// Insert �Լ����� �����߱� ������ 1 ���־�� ��.
	int current = currentSize - 1;
	
	// ������ ���� ��Ʈ��带 �ٲ۴�.
	std::swap(heap[0], heap[current]);
	printf("%d�� ������ �����߽��ϴ�.\n", heap[current]);
	heap[current] = INT_MAX; // ������ ��� �� ����, ��Ʈ��� �� �����ϴ� ���̴�.

	// ��Ʈ������ ���� ������ ��� �� ��Ʈ��庸�� ���� �� ������ �����ϸ鼭 ��Ʈ��忡 �ּڰ� ������ ����
	int parent = 0, left, right;

	// ������ ������ ����
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