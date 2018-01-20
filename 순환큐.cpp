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
	node = new Node[size+1]; // 더미노드까지 포함해서 생성
}

CircularQueue::~CircularQueue()
{
	delete[] node;
}

void CircularQueue::enqueue(int data)
{
	int pos;
	// back이 마지막 인덱스에 채우는 경우
	// back은 계속 순환하니까 0으로 초기화
	// 마지막엔 pos로 담는다.
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
	// front가 마지막 인덱스의 데이터를 제거하는 경우
	// front도 순환하므로 0으로 초기화
	// 리턴은 pos로 한다.
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
	// back은 enqueue에서 증가하므로 -1 해서 접근해야 함
	return node[back-1].data;
}

int CircularQueue::getSize() const
{
	// front가 back보다 작거나 같은경우
	if (front <= back) return back - front;
	// front가 back보다 큰 경우는 
	// back이 다시 돌아오고 front가 진행하는 경우이다.
	else if (front > back) return capacity - front + back;
}

bool CircularQueue::isEmpty() const
{
	return front == back;
}

bool CircularQueue::isFull() const
{
	// front가 back보다 작으면 back이 더미 바로 전에 있어야 함
	if (front <= back) back - front == capacity - 1;
	// front가 back보다 크면 back이 front 바로 전에 있어야 함
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