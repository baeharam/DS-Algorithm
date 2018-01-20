#include <iostream>

typedef struct Node{
	int data;
}Node;

class CircularQueue{
private:
	Node* node;
	int front;
	int back;
	int capacity;

public:
	CircularQueue(int size);
	~CircularQueue();
	void enqueue(int data);
	int dequeue();
	int getFront() const;
	int getBack() const;
	int getSize() const;
	bool isEmpty() const;
	bool isFull() const;
};

CircularQueue::CircularQueue(int size) :front(0), back(0), capacity(size)
{
	node = new Node[size+1]; // ���̳����� �����ؼ� ����
}

CircularQueue::~CircularQueue()
{
	delete[] node;
}

void CircularQueue::enqueue(int data)
{
	int pos;
	// back�� ������ �ε����� ä��� ���
	// back�� ��� ��ȯ�ϴϱ� 0���� �ʱ�ȭ
	// �������� pos�� ��´�.
	if (back==capacity-1){
		pos = back; back = 0;
		node[pos].data = data;
	}
	else
		node[back++].data = data;
}

int CircularQueue::dequeue()
{
	int pos = front;
	// front�� ������ �ε����� �����͸� �����ϴ� ���
	// front�� ��ȯ�ϹǷ� 0���� �ʱ�ȭ
	// ������ pos�� �Ѵ�.
	if (front == capacity - 1) front = 0;
	else front++;
	return node[pos].data;
}

int CircularQueue::getFront() const
{
	return node[front].data;
}

int CircularQueue::getBack() const
{
	// back�� enqueue���� �����ϹǷ� -1 �ؼ� �����ؾ� ��
	return node[back-1].data;
}

int CircularQueue::getSize() const
{
	// front�� back���� �۰ų� �������
	if (front <= back) return back - front;
	// front�� back���� ū ���� 
	// back�� �ٽ� ���ƿ��� front�� �����ϴ� ����̴�.
	else if (front > back) return capacity - front + back;
}

bool CircularQueue::isEmpty() const
{
	return front == back;
}

bool CircularQueue::isFull() const
{
	// front�� back���� ������ back�� ���� �ٷ� ���� �־�� ��
	if (front <= back) back - front == capacity - 1;
	// front�� back���� ũ�� back�� front �ٷ� ���� �־�� ��
	else back + 1 == front;
}



int main(void)
{
	CircularQueue cq(10);

	cq.enqueue(1);
	cq.enqueue(2);
	cq.enqueue(3);

	std::cout << cq.dequeue() << '\n';
	std::cout << cq.dequeue() << '\n';
	std::cout << cq.getFront() << '\n';
	std::cout << cq.getBack() << '\n';

	return 0;
}