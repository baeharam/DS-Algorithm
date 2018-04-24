#include <iostream>
#include <string>

// 덱에 들어가질 노드 클래스
class Node{
private:
	int data;
	// 이전 노드와 다음 노드를 가리키는 포인터를 갖는다.
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
	// 맨 앞과 맨 뒤를 가리키는 포인터를 갖는다.
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

// frontNode 부터 쭉 내려오면서 메모리 해제
Deque::~Deque()
{
	Node* front = frontNode;
	while (front){
		Node* temp = front;
		front = front->getPrev();
		delete temp;
	}
}

// 덱 가장 앞에 데이터를 넣는다.
void Deque::push_front(int data)
{
	Node* newNode = new Node(data, NULL, NULL);
	// 아무것도 없다면 새로 생성해서 frontNode와 backNode를 초기화
	if (empty()) frontNode = backNode = newNode;
	// 하나라도 있다면 새로 생성해서 frontNode 초기화
	else{
		newNode->setNext(frontNode);
		frontNode->setPrev(newNode);
		frontNode = newNode;
	}
	std::cout << "덱 가장 앞에 " << data << "를 삽입했습니다..\n";
	std::cout << "----------------------------------------------\n";
	deque_size++;
}

// 덱 가장 뒤에 데이터를 넣는다.
void Deque::push_back(int data)
{
	Node* newNode = new Node(data, NULL, NULL);
	// 아무것도 없다면 새로 생성해서 frontNode와 backNode를 초기화
	if (empty()) frontNode = backNode = newNode;
	// 하나라도 있다면 새로 생성해서 backNode 초기화
	else{
		backNode->setNext(newNode);
		newNode->setPrev(backNode);
		backNode = newNode;
	}
	std::cout << "덱 가장 뒤에 " << data << "를 삽입했습니다..\n";
	std::cout << "----------------------------------------------\n";
	deque_size++;
}

// 덱 가장 앞의 데이터를 빼고 출력한다. (리턴까지)
void Deque::pop_front()
{
	// 덱에 들어있는 정수가 없는 경우
	if (empty()) std::cout << "덱이 비었습니다.\n";
	// 덱에 정수가 있는 경우 출력하고 메모리 삭제한 뒤 리턴
	else{
		int data = frontNode->getData();
		Node* temp = frontNode;
		frontNode = frontNode->getNext();
		if (frontNode != NULL) frontNode->setPrev(NULL);
		delete temp;
		deque_size--;
		std::cout << "덱 가장 앞에서 " << data << "을 제거했습니다..\n";
	}
	std::cout << "----------------------------------------------\n";
}

// 덱 가장 뒤의 데이터를 빼고 출력한다. (리턴까지)
void Deque::pop_back()
{
	// 덱에 들어있는 정수가 없는 경우
	if (empty()) std::cout << "덱이 비었습니다.\n";
	// 덱에 정수가 있는 경우 출력하고 메모리 삭제한 뒤 리턴
	else{
		int data = backNode->getData();
		Node* temp = backNode;
		backNode = backNode->getPrev();
		if (backNode != NULL) backNode->setNext(NULL);
		delete temp;
		deque_size--;
		std::cout << "덱 가장 뒤에서 " << data << "을 제거했습니다..\n";
	}
	std::cout << "----------------------------------------------\n";
}

int Deque::size()
{
	std::cout <<"덱의 크기는 "<< deque_size << "입니다.\n";
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
	if (empty()) std::cout << "덱이 비었습니다.\n";
	else std::cout << "덱의 가장 앞에 있는 값은 "<<frontNode->getData() << "입니다.\n";
	std::cout << "----------------------------------------------\n";
}

void Deque::back()
{
	if (empty()) std::cout << "덱이 비었습니다.\n";
	else std::cout << "덱의 가장 뒤에 있는 값은 " << backNode->getData() << "입니다.\n";
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