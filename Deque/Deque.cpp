#include <iostream>
#include <string>

// ���� ���� ��� Ŭ����
class Node{
private:
	int data;
	// ���� ���� ���� ��带 ����Ű�� �����͸� ���´�.
	Node* prevNode;
	Node* nextNode;
public:
	Node(int _data = 0, Node* _prevNode = NULL, Node* _nextNode = NULL)
		:data(_data), prevNode(_prevNode), nextNode(_nextNode){}
	Node* getPrev() const { return prevNode; }
	Node* getNext() const { return nextNode; }
	int getData() const { return data; }
	void setPrev(Node* prev) { prevNode = prev; }
	void setNext(Node* next) { nextNode = next; }
};

class Deque{
private:
	// �� �հ� �� �ڸ� ����Ű�� �����͸� ���´�.
	Node* frontNode;
	Node* backNode;
	int deque_size;
public:
	Deque() :frontNode(NULL), backNode(NULL), deque_size(0){}
	~Deque();
	void push_front(int data);
	void push_back(int data);
	void pop_front();
	void pop_back();
	int size();
	bool empty();
	void front();
	void back();
};

// frontNode ���� �� �������鼭 �޸� ����
Deque::~Deque()
{
	Node* front = frontNode;
	while (front){
		Node* temp = front;
		front = front->getPrev();
		delete temp;
	}
}

// �� ���� �տ� �����͸� �ִ´�.
void Deque::push_front(int data)
{
	Node* newNode = new Node(data, NULL, NULL);
	// �ƹ��͵� ���ٸ� ���� �����ؼ� frontNode�� backNode�� �ʱ�ȭ
	if (empty()) frontNode = backNode = newNode;
	// �ϳ��� �ִٸ� ���� �����ؼ� frontNode �ʱ�ȭ
	else{
		newNode->setNext(frontNode);
		frontNode->setPrev(newNode);
		frontNode = newNode;
	}
	std::cout << "�� ���� �տ� " << data << "�� �����߽��ϴ�..\n";
	std::cout << "----------------------------------------------\n";
	deque_size++;
}

// �� ���� �ڿ� �����͸� �ִ´�.
void Deque::push_back(int data)
{
	Node* newNode = new Node(data, NULL, NULL);
	// �ƹ��͵� ���ٸ� ���� �����ؼ� frontNode�� backNode�� �ʱ�ȭ
	if (empty()) frontNode = backNode = newNode;
	// �ϳ��� �ִٸ� ���� �����ؼ� backNode �ʱ�ȭ
	else{
		backNode->setNext(newNode);
		newNode->setPrev(backNode);
		backNode = newNode;
	}
	std::cout << "�� ���� �ڿ� " << data << "�� �����߽��ϴ�..\n";
	std::cout << "----------------------------------------------\n";
	deque_size++;
}

// �� ���� ���� �����͸� ���� ����Ѵ�. (���ϱ���)
void Deque::pop_front()
{
	// ���� ����ִ� ������ ���� ���
	if (empty()) std::cout << "���� ������ϴ�.\n";
	// ���� ������ �ִ� ��� ����ϰ� �޸� ������ �� ����
	else{
		int data = frontNode->getData();
		Node* temp = frontNode;
		frontNode = frontNode->getNext();
		if (frontNode != NULL) frontNode->setPrev(NULL);
		delete temp;
		deque_size--;
		std::cout << "�� ���� �տ��� " << data << "�� �����߽��ϴ�..\n";
	}
	std::cout << "----------------------------------------------\n";
}

// �� ���� ���� �����͸� ���� ����Ѵ�. (���ϱ���)
void Deque::pop_back()
{
	// ���� ����ִ� ������ ���� ���
	if (empty()) std::cout << "���� ������ϴ�.\n";
	// ���� ������ �ִ� ��� ����ϰ� �޸� ������ �� ����
	else{
		int data = backNode->getData();
		Node* temp = backNode;
		backNode = backNode->getPrev();
		if (backNode != NULL) backNode->setNext(NULL);
		delete temp;
		deque_size--;
		std::cout << "�� ���� �ڿ��� " << data << "�� �����߽��ϴ�..\n";
	}
	std::cout << "----------------------------------------------\n";
}

int Deque::size()
{
	std::cout <<"���� ũ��� "<< deque_size << "�Դϴ�.\n";
	std::cout << "----------------------------------------------\n";
	return deque_size;
}

bool Deque::empty()
{
	if (deque_size == 0) return true;
	else return false;
}

void Deque::front()
{
	if (empty()) std::cout << "���� ������ϴ�.\n";
	else std::cout << "���� ���� �տ� �ִ� ���� "<<frontNode->getData() << "�Դϴ�.\n";
	std::cout << "----------------------------------------------\n";
}

void Deque::back()
{
	if (empty()) std::cout << "���� ������ϴ�.\n";
	else std::cout << "���� ���� �ڿ� �ִ� ���� " << backNode->getData() << "�Դϴ�.\n";
	std::cout << "----------------------------------------------\n";
}


int main(void)
{
	Deque dq;
	dq.push_front(1);
	dq.push_back(2);
	dq.push_front(12);

	dq.pop_front();
	dq.pop_front();
	dq.pop_front();
	dq.pop_back();

	return 0;
}