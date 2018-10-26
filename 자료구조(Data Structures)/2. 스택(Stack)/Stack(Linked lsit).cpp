#include <iostream>

// 데이터를 담는 노드클래스
template <typename T>
class Node{
private:
	T data; // 실제 int형 데이터
	Node* prevNode; // 이전노드를 가리키는 포인터변수
public:
	Node(T data, Node* prevNode); // 생성자
	T getData() const { return data; } // data를 받환하는 멤버함수, 멤버를 건들지 않기 때문에 const이다.
	void setPrev(Node* prev); // prevNode를 초기화하는 멤버함수
	Node* getPrev() const; // prevNode를 반환하는 멤버함수, 멤버를 건들지 않기 때문에 const이다.
};

// 생성자
// 멤버 초기화 리스트를 사용해서 초기화한다.
// 인자가 없을 경우 0과 NULL로 초기화한다.
template <typename T>
Node<T>::Node(T num = 0, Node* prev = NULL)
	:data(num), prevNode(prev)
{}

// prevNode 초기화 함수
// prevNode를 인자로 받아서 초기화시킨다.
template <typename T>
void Node<T>::setPrev(Node* prev)
{
	this->prevNode = prev;
}

// prevNode 반환 함수
// prevNode를 반환한다.
template <typename T>
Node<T>* Node<T>::getPrev() const
{
	return this->prevNode;
}

// 노드를 이어주는 스택 클래스
template <typename T>
class Stack{
private:
	Node<T>* topNode; // 최상위 노드를 가리키는 포인터 변수
	int size; // 스택에 쌓인 총 개수에 대한 변수
public:
	Stack(); // 생성자
	~Stack(); // 소멸자
	void Push(const T& data); // data를 스택에 넣는다.
	T Pop(); // data를 스택에서 빼고 반환한다.
	bool IsEmpty() const; // 스택이 비어있는지 반환한다.
	int Size() const; // 스택의 사이즈를 반환한다.
	T Top() const; // 스택 제일 위에 있는 data를 반환한다.
};

// 생성자
// 기본 생성자이며 NULL과 0으로 초기화한다.
template <typename T>
Stack<T>::Stack() :topNode(NULL), size(0)
{
	std::cout << "스택을 생성했습니다!\n";
}

// 소멸자
// topNode와 prevNode에 할당되었던 모든 메모리를 해제한다.
template <typename T>
Stack<T>::~Stack()
{
	// 제일 최상위 노드를 가리키는 포인터를 top에 할당한다.
	Node<T>* top = this->topNode;
	while (top){
		// 메모리 해제를 위해 임시로 만든 old에 top을 할당한다.
		Node<T>* old = top;
		// top->getPrev()가 원래 this->topNode->getPrev()로 되어있어서
		// 백준 1874번 문제에서 계속 런타임 에러 발생
		// 질문해서 다른 분이 알아내주심
		// top을 아래노드로 업데이트시키고
		top = top->getPrev();
		// old로 메모리를 해제한다
		delete old;
	}
}

// Push
template <typename T>
void Stack<T>::Push(const T& data)
{
	std::cout << "스택에 " << data << "를 추가했습니다.\n";
	// 비어있다면 새로운 객체를 할당한다.
	if (this->topNode == NULL)
		this->topNode = new Node<T>(data, NULL);
	// 아니라면 포인터변수에 topNode를 담고
	// topNode에 새로운 객체를 대입한다. temp는 prevNode에 대입된다.
	else{
		Node<T>* temp = topNode;
		this->topNode = new Node<T>(data, temp);
	}
	this->size++;
}

// 가장 위의 값 제거 후 리턴
template <typename T>
T Stack<T>::Pop()
{
	// 임시변수들에 데이터와 topNode를 담는다.
	std::cout << "스택에서 " << this->topNode->getData() << "를 삭제했습니다.\n";
	int temp = this->topNode->getData();
	Node<T> *old = this->topNode;

	// 만약 prevNode가 NULL이라면 topNode만 NULL로 초기화해주면 된다.
	if (this->topNode->getPrev() == NULL)
		this->topNode = NULL;
	// 아니라면 topNode와 prevNode를 한칸씩 내려준다.
	else{
		this->topNode = this->topNode->getPrev();
		this->topNode->setPrev(this->topNode->getPrev());
	}

	// 메모리에 할당되었던 topNode를 해제해주고 길이가 줄어든다.
	// 데이터를 리턴해준다.
	this->size--;
	delete old;
	return temp;
}

// 비어있는지 여부 리턴
template <typename T>
bool Stack<T>::IsEmpty() const
{
	if (this->size) return false;
	else return true;
}

// 몇개 있는지 리턴
template <typename T>
int Stack<T>::Size() const
{
	std::cout << "스택의 크기는 " << this->size << "입니다.\n";
	return this->size;
}

// 가장 위의 값 제거하지 않고 리턴
template <typename T>
T Stack<T>::Top() const
{
	std::cout << "가장 위의 데이터는 " << this->topNode->getData() << "입니다.\n";
	return this->topNode->getData();
}

int main(void)
{
	Stack<int> s;

	// 스택에 1,2를 넣는다.
	s.Push(1);
	s.Push(2);

	// LIFO이므로 2,1로 빠진다.
	s.Pop();
	s.Pop();

	// 스택에 5를 넣는다.
	s.Push(5);
	// 빼지 않고 출력만한다.
	s.Top();
	// 5만 있으니까 사이즈는 1
	s.Size();

	return 0;

}
