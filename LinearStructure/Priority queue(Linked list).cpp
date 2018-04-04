#include <iostream>
#include <string>

// 우선순위 큐에 들어가질 노드 클래스
template <typename T>
class Node{
private:
	T data;
	// 다음 노드와 이전 노드를 가리키는 포인터를 갖는다.
	Node* nextNode;
public:
	Node(int _data = 0, Node* _nextNode = NULL)
		:data(_data), nextNode(_nextNode){}
	Node* getNext() const { return nextNode; }
	T getData() const { return data; }
	void setData(T _data){ data = _data; }
	void setNext(Node<T>* next) { nextNode = next; }
};

template <typename T>
class PriorityQueue{
private:
	Node<T>* frontNode; // 맨 앞 노드를 가리키는 포인터
	Node<T>* backNode; // 맨 뒤 노드를 가리키는 포인터
	int sizeq; // 우선순위 큐의 사이즈
	std::string type; // 우선순위 큐에 들어가는 방식
public:
	PriorityQueue(std::string qtype="less") :frontNode(NULL), backNode(NULL), sizeq(0),type(qtype){
		if (!type.compare("less")) std::cout << "내림차순 기준 우선순위 큐를 생성했습니다.\n";
		else std::cout << "오름차순 기준 우선순위 큐를 생성했습니다.\n";
		std::cout << "-----------------------------------------------------\n";
	}
	~PriorityQueue();
	void enqueue(T data);
	T dequeue();
	int size();
	bool empty() const;
	T front() const;
	T back() const;
};

// frontNode 부터 계속 다음으로 가면서 메모리 해제
template <typename T>
PriorityQueue<T>::~PriorityQueue()
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
void PriorityQueue<T>::enqueue(T data)
{
	// 일단 새로운 노드 객체를 하나 생성
	Node<T>* newNode = new Node<T>(data, NULL);

	// 아무것도 없다면 frontNode와 backNode를 초기화
	if (empty()) frontNode = backNode = newNode;
		
	// 하나라도 있다면 이제 less(내림차순)인지 greater(오름차순)인지 확인한다.
	else{
		// 노드들을 조사할 임시포인터 tempNode를 frontNode로 초기화한다.
		Node<T>* tempNode = frontNode;
		// 1. less(내림차순)인 경우
		if (!type.compare("less")){
			// tempNode가 NULL이 될 때까지 조사하는데
			while (tempNode){
				// 기존 노드의 값이 더 클 경우 다음으로 넘어간다.
				if (tempNode->getData() > data) tempNode = tempNode->getNext();
				// 기존 노드의 값이 작은 경우 newNode의 값과 바꾸고 빠져나온다.
				else{
					T temp = tempNode->getData();
					tempNode->setData(data);
					newNode->setData(temp);
					break;
				}
			}
		}

		// 2. greater(오름차순)인 경우
		else if (!type.compare("greater")){
			// tempNode가 NULL이 될 때까지 조사하는데
			while (tempNode){
				// 기존 노드의 값이 더 작을 경우 다음으로 넘어간다.
				if (tempNode->getData() < data) tempNode = tempNode->getNext();
				// 기존 노드의 값이 큰 경우 newNode의 값과 바꾸고 빠져나온다.
				else{
					T temp = tempNode->getData();
					tempNode->setData(data);
					newNode->setData(temp);
					break;
				}
			}
		}
		// 중간에 바꾼 경우라면
		if (tempNode){
			// newNode의 다음 노드를 tempNode의 다음노드로 설정하고
			newNode->setNext(tempNode->getNext());
			// tempNode의 다음 노드를 newNode로 설정한다.
			tempNode->setNext(newNode);
			// 그리고 가장 마지막 노드를 backNode로 초기화시킨다.
			while (tempNode->getNext())
				tempNode = tempNode->getNext();
			backNode = tempNode;
		}
		// 중간에 바꾸지 않았다면
		else{
			// 기존 방식대로 마지막 노드 다음으로 newNode를 설정한다.
			backNode->setNext(newNode);
			backNode = newNode;
		}
	}
	if (!type.compare("less")) std::cout << "내림차순 기준 우선순위 큐에 " << data << "를 삽입했습니다..\n";
	else std::cout << "오름차순 기준 우선순위 큐에 " << data << "를 삽입했습니다..\n";	
	std::cout << "-----------------------------------------------------\n";
	sizeq++;
}

// 반드시 비어있는지 확인 해야함
template <typename T>
// 데이터를 제거하는 함수
T PriorityQueue<T>::dequeue()
{
	if (!type.compare("less")) std::cout << "내림차순 기준 우선순위 큐에서 " << frontNode->getData() << "를 삭제했습니다..\n";
	else std::cout << "오름차순 기준 우선순위 큐에서 " << frontNode->getData() << "를 삭제했습니다..\n";
	std::cout << "-----------------------------------------------------\n";
	int num = frontNode->getData();
	Node<T>* temp = frontNode;
	frontNode = frontNode->getNext();
	delete temp;
	sizeq--;
	return num;
}

template <typename T>
int PriorityQueue<T>::size()
{
	return sizeq;
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
	if (sizeq == 0) return true;
	else return false;
}

template <typename T>
T PriorityQueue<T>::front() const
{
	std::cout << "가장 앞에 있는 값은 " << frontNode->getData() << "입니다.\n";
	return frontNode->getData();
}

template <typename T>
T PriorityQueue<T>::back() const
{
	std::cout << "가장 뒤에 있는 값은 " << backNode->getData() << "입니다.\n";
	return backNode->getData();
}

int main(void)
{
	PriorityQueue<int> pq_less;
	PriorityQueue<int> pq_greater("greater");

	pq_less.enqueue(2);
	pq_less.enqueue(4);
	pq_less.enqueue(3);
	pq_less.enqueue(15);
	pq_less.enqueue(1);

	pq_less.dequeue();
	pq_less.dequeue();
	pq_less.dequeue();
	pq_less.dequeue();
	pq_less.dequeue();

	pq_greater.enqueue(2);
	pq_greater.enqueue(4);
	pq_greater.enqueue(3);
	pq_greater.enqueue(15);
	pq_greater.enqueue(1);

	pq_greater.dequeue();
	pq_greater.dequeue();
	pq_greater.dequeue();
	pq_greater.dequeue();
	pq_greater.dequeue();

	return 0;
}