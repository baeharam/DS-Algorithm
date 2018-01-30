#include <iostream>
#include <string>

// ť�� ���� ��� Ŭ����
template <typename T>
class Node{
private:
	T data;
	// ���� ��带 ����Ű�� �����͸� ���´�.
	Node* prevNode;
public:
	Node(int _data = 0, Node* _prevNode = NULL);
	Node* getPrev() const;
	T getData() const;
	void setPrev(Node<T>* prev);
};

template <typename T>
Node<T>::Node(int _data, Node* _prevNode)
	:data(_data), prevNode(_prevNode)
{}

template <typename T>
Node<T>* Node<T>::getPrev() const
{
	return prevNode;
}

template <typename T>
T Node<T>::getData() const
{
	return data;
}

template <typename T>
void Node<T>::setPrev(Node* prev)
{
	prevNode = prev;
}

template <typename T>
class Queue{
private:
	// �� �հ� �� �ڸ� ����Ű�� �����͸� ���´�.
	Node<T>* frontNode;
	Node<T>* backNode;
	T sizeq;
public:
	Queue() :frontNode(NULL), backNode(NULL), sizeq(0){}
	~Queue();
	void enqueue(T data);
	T dequeue();
	int size();
	bool empty() const;
	void front() const;
	void back() const;
};

// frontNode ���� �� �������鼭 �޸� ����
template <typename T>
Queue<T>::~Queue()
{
	Node<T>* front = frontNode;
	while (front){
		Node<T>* temp = front;
		front = front->getPrev();
		delete temp;
	}
}

template <typename T>
void Queue<T>::enqueue(T data)
{
	Node<T>* newNode = new Node<T>(data, NULL);
	// �ƹ��͵� ���ٸ� ���� �����ؼ� frontNode�� backNode�� �ʱ�ȭ
	if (empty())
		frontNode = backNode = newNode;
	// �ϳ��� �ִٸ� ���� �����ؼ� backNode �ʱ�ȭ
	else{
		backNode->setPrev(newNode);
		backNode = newNode;
	}
	sizeq++;
}

// �ݵ�� ����ִ��� Ȯ�� �ؾ���
template <typename T>
T Queue<T>::dequeue()
{
	int num = frontNode->getData();
	std::cout << num << std::endl;
	Node<T>* temp = frontNode;
	frontNode = frontNode->getPrev();
	delete temp;
	sizeq--;
	return num;
}

template <typename T>
int Queue<T>::size()
{
	std::cout << sizeq << '\n';
	return sizeq;
}

template <typename T>
bool Queue<T>::empty() const
{
	if (sizeq == 0){
		std::cout << 1 << '\n';
		return true;
	}
	else {
		std::cout << 0 << '\n';
		return false;
	}
}

// �ݵ�� ����ִ��� Ȯ�� �ؾ���
template <typename T>
void Queue<T>::front() const
{
	std::cout << frontNode->getData() << '\n';
}

// �ݵ�� ����ִ��� Ȯ�� �ؾ���
template <typename T>
void Queue<T>::back() const
{
	std::cout << backNode->getData() << '\n';
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	Queue<int> q;

	q.enqueue(1);
	q.front();
	q.enqueue(2);
	q.dequeue();

	return 0;

}