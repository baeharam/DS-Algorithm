#include <iostream>
#include <string>

// 큐에 들어가질 노드 클래스
template <typename T>
class Node{
private:
	T data;
	// 이전 노드를 가리키는 포인터를 갖는다.
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
	// 맨 앞과 맨 뒤를 가리키는 포인터를 갖는다.
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

// frontNode 부터 쭉 내려오면서 메모리 해제
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
	// 아무것도 없다면 새로 생성해서 frontNode와 backNode를 초기화
	if (empty())
		frontNode = backNode = newNode;
	// 하나라도 있다면 새로 생성해서 backNode 초기화
	else{
		backNode->setPrev(newNode);
		backNode = newNode;
	}
	sizeq++;
}

// 반드시 비어있는지 확인 해야함
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

// 반드시 비어있는지 확인 해야함
template <typename T>
void Queue<T>::front() const
{
	std::cout << frontNode->getData() << '\n';
}

// 반드시 비어있는지 확인 해야함
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