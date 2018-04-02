#include <iostream>
#include <algorithm>

class Heap {
private:
	int *heap;
	int capacity; // ���� ũ��
	int currentSize; // ���� ���� �ִ� ������ ����

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
	// ���Ұ����� �ε��� = ������ �ε��� (0���� �����̹Ƿ�)
	int current = currentSize;

	if (current == capacity) {
		std::cout << "���� ����á���ϴ�\n";
		return;
	}

	printf("%d�� �����߽��ϴ�..\n", data);

	// ���� ������ ��ġ�� ������ ����
	heap[current] = data;

	// �θ����� ��ġ
	int root = (current - 1) / 2;

	// �����尡 �θ��庸�� ũ�� �ٲٰ� ������, �θ��� ������Ʈ
	while (heap[current] > heap[root]) {
		std::swap(heap[current], heap[root]);
		current = root;
		root = (current - 1) / 2;
	}

	// ������ ���� ����
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
	// ���� ���Ұ� ���� ���
	if (currentSize == 0) return;
	// Insert�Լ��� +1 �� ���� ���󺹱�
	currentSize--;
	

	// ��Ʈ ���� ���� ������ ��带 �ٲ۴�.
	std::swap(heap[0], heap[currentSize]);
	printf("%d�� ������ �����߽��ϴ�.\n", heap[currentSize]);

	// ���� ������ ��� ����
	heap[currentSize] = NULL;

	// ��Ʈ���� �����ڽĳ��, �������ڽĳ�带 �˻��ذ��鼭 ��ġ �ٲ�� �ϹǷ� �̸� ����
	int root = 0, leftchild, rightchild;

	// ��Ʈ��尡 ���� ũ�⸦ �Ѿ�� �ʴ� ���
	while (root<=currentSize) {
		leftchild = (root + 1) * 2 - 1;
		rightchild = (root + 1) * 2;

		// �ڽĳ�尡 �������� ���� 
		// (���� �ڽĳ�尡 ������ �������� ũ�ٴ� �� ���ٴ� ��� = �����ʵ� ���ٴ� ���)
		if (leftchild > currentSize) break; 

		// ���� �ڽĳ�常 ������
		// (������ �ڽĳ�尡 ������ �������� ũ�ٴ� �� ���ٴ� ���)
		else if (rightchild > currentSize) {
			if (heap[root] < heap[leftchild]) {
				std::swap(heap[root], heap[leftchild]);
				root = leftchild;
			}
			else break;
		}

		// �� �� ������
		else {
			// ��Ʈ��庸�� ���� �ڽĳ�尡 Ŭ ���
			if (heap[root] < heap[leftchild]) {
				// ���� �ڽĳ�庸�� ������ �ڽĳ�尡 Ŭ ���
				if (heap[leftchild] < heap[rightchild]) {
					std::swap(heap[root], heap[rightchild]);
					root = rightchild;
				}
				// ���� �ڽĳ�尡 ������ �ڽĳ�庸�� Ŭ ���
				else {
					std::swap(heap[root], heap[leftchild]);
					root = leftchild;
				}
			}
			// ��Ʈ��庸�� ���� �ڽĳ�尡 ������ ������ �ڽĳ�尡 Ŭ ���
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