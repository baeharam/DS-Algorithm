#include <iostream>
#include <string>

// 큐에 들어가질 노드 클래스
template <typename T>
class Node{
private:
	T data;
	// 다음 노드를 가리키는 포인터를 갖는다.
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
	Node<T>* frontNode; // 맨 앞 노드를 가리키는 포인터
	Node<T>* backNode; // 맨 뒤 노드를 가리키는 포인터
	int sizeq; // 큐의 사이즈
public:
	Queue() :frontNode(NULL), backNode(NULL), sizeq(0){
		std::cout << "큐를 생성했습니다!\n";
	}
	~Queue();
	void enqueue(T data);
	T dequeue();
	int size();
	bool empty() const;
	T front() const;
	T back() const;
};

// frontNode 부터 계속 다음으로 가면서 메모리 해제
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
// 데이터를 넣는 함수
void Queue<T>::enqueue(T data)
{
	std::cout << "큐에 " << data << "를 삽입했습니다..\n";
	Node<T>* newNode = new Node<T>(data, NULL);
	// 아무것도 없다면 새로 생성해서 frontNode와 backNode를 초기화
	if (empty())
		frontNode = backNode = newNode;
	// 하나라도 있다면 새로 생성해서 backNode 초기화
	else{
		backNode->setNext(newNode);
		backNode = newNode;
	}
	sizeq++;
}

// 반드시 비어있는지 확인 해야함
template <typename T>
// 데이터를 제거하는 함수
T Queue<T>::dequeue()
{
	std::cout << "큐에서 " << frontNode->getData() << "를 삭제했습니다..\n";
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
	std::cout << "가장 앞에 있는 값은 " << frontNode->getData() << "입니다.\n";
	return frontNode->getData();
}

template <typename T>
T Queue<T>::back() const
{
	std::cout << "가장 뒤에 있는 값은 " << backNode->getData() << "입니다.\n";
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