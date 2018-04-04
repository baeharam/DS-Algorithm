#include <iostream>
#include <string>

// ť�� ���� ��� Ŭ����
template <typename T>
class Node{
private:
	T data;
	// ���� ��带 ����Ű�� �����͸� ���´�.
	Node* nextNode;
public:
	Node(int _data = 0, Node* _nextNode = NULL);
	Node* getNext() const;
	T getData() const;
	void setNext(Node<T>* next);
};

template <typename T>
Node<T>::Node(int _data, Node* _nextNode)
	:data(_data), nextNode(_nextNode)
{}

template <typename T>
Node<T>* Node<T>::getNext() const
{
	return nextNode;
}

template <typename T>
T Node<T>::getData() const
{
	return data;
}

template <typename T>
void Node<T>::setNext(Node* next)
{
	nextNode = next;
}

template <typename T>
class Queue{
private:
	Node<T>* frontNode; // �� �� ��带 ����Ű�� ������
	Node<T>* backNode; // �� �� ��带 ����Ű�� ������
	int sizeq; // ť�� ������
public:
	Queue() :frontNode(NULL), backNode(NULL), sizeq(0){
		std::cout << "ť�� �����߽��ϴ�!\n";
	}
	~Queue();
	void enqueue(T data);
	T dequeue();
	int size();
	bool empty() const;
	T front() const;
	T back() const;
};

// frontNode ���� ��� �������� ���鼭 �޸� ����
template <typename T>
Queue<T>::~Queue()
{
	Node<T>* front = frontNode;
	while (front){
		Node<T>* temp = front;
		front = front->getNext();
		delete temp;
	}
}

template <typename T>
// �����͸� �ִ� �Լ�
void Queue<T>::enqueue(T data)
{
	std::cout << "ť�� " << data << "�� �����߽��ϴ�..\n";
	Node<T>* newNode = new Node<T>(data, NULL);
	// �ƹ��͵� ���ٸ� ���� �����ؼ� frontNode�� backNode�� �ʱ�ȭ
	if (empty())
		frontNode = backNode = newNode;
	// �ϳ��� �ִٸ� ���� �����ؼ� backNode �ʱ�ȭ
	else{
		backNode->setNext(newNode);
		backNode = newNode;
	}
	sizeq++;
}

// �ݵ�� ����ִ��� Ȯ�� �ؾ���
template <typename T>
// �����͸� �����ϴ� �Լ�
T Queue<T>::dequeue()
{
	std::cout << "ť���� " << frontNode->getData() << "�� �����߽��ϴ�..\n";
	int num = frontNode->getData();
	Node<T>* temp = frontNode;
	frontNode = frontNode->getNext();
	delete temp;
	sizeq--;
	return num;
}

template <typename T>
int Queue<T>::size()
{
	return sizeq;
}

template <typename T>
bool Queue<T>::empty() const
{
	if (sizeq == 0) return true;
	else return false;
}

template <typename T>
T Queue<T>::front() const
{
	std::cout << "���� �տ� �ִ� ���� " << frontNode->getData() << "�Դϴ�.\n";
	return frontNode->getData();
}

template <typename T>
T Queue<T>::back() const
{
	std::cout << "���� �ڿ� �ִ� ���� " << backNode->getData() << "�Դϴ�.\n";
	return backNode->getData();
}


int main(void)
{
	Queue<int> q;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);

	q.front();
	q.back();

	q.dequeue();
	q.dequeue();
	q.dequeue();
	q.dequeue();

	return 0;
}