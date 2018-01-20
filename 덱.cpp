#include <iostream>
#include <string>

// ť�� ���� ��� Ŭ����
class Node{
private:
	int data;
	// ���� ���� ���� ��带 ����Ű�� �����͸� ���´�.
	Node* prevNode;
	Node* nextNode;
public:
	Node(int _data = 0, Node* _prevNode = NULL, Node* _nextNode = NULL);
	Node* getPrev() const;
	Node* getNext() const;
	int getData() const;
	void setPrev(Node* prev);
	void setNext(Node* next);
};

Node::Node(int _data, Node* _prevNode, Node* _nextNode)
	:data(_data), prevNode(_prevNode), nextNode(_nextNode)
{}

Node* Node::getPrev() const
{
	return prevNode;
}

int Node::getData() const
{
	return data;
}

void Node::setPrev(Node* prev)
{
	prevNode = prev;
}

void Node::setNext(Node* next)
{
	nextNode = next;
}

Node* Node::getNext() const
{
	return nextNode;
}

class Deque{
private:
	// �� �հ� �� �ڸ� ����Ű�� �����͸� ���´�.
	Node* frontNode;
	Node* backNode;
	int sizeq;
public:
	Deque() :frontNode(NULL), backNode(NULL), sizeq(0){}
	~Deque();
	void push_front(int data);
	void push_back(int data);
	int pop_front();
	int pop_back();
	int size();
	int empty();
	void front() const;
	void back() const;
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
	if (!sizeq)
		frontNode = backNode = newNode;
	// �ϳ��� �ִٸ� ���� �����ؼ� frontNode �ʱ�ȭ
	else{
		newNode->setPrev(frontNode);
		frontNode->setNext(newNode);
		frontNode = newNode;
	}
	sizeq++;
}

// �� ���� �ڿ� �����͸� �ִ´�.
void Deque::push_back(int data)
{
	Node* newNode = new Node(data, NULL, NULL);
	// �ƹ��͵� ���ٸ� ���� �����ؼ� frontNode�� backNode�� �ʱ�ȭ
	if (!sizeq)
		frontNode = backNode = newNode;
	// �ϳ��� �ִٸ� ���� �����ؼ� backNode �ʱ�ȭ
	else{
		backNode->setPrev(newNode);
		newNode->setNext(backNode);
		backNode = newNode;
	}
	sizeq++;
}

// �� ���� ���� �����͸� ���� ����Ѵ�. (���ϱ���)
int Deque::pop_front()
{
	// ť�� ����ִ� ������ ���� ���
	if (!sizeq){
		std::cout << -1 << '\n';
		return -1;
	}
	// ť�� ������ �ִ� ��� ����ϰ� �޸� ������ �� ����
	else{
		int num = frontNode->getData();
		std::cout << num << std::endl;
		Node* temp = frontNode;
		frontNode = frontNode->getPrev();
		if (frontNode != NULL) frontNode->setNext(NULL);
		delete temp;
		sizeq--;
		return num;
	}
}

// �� ���� ���� �����͸� ���� ����Ѵ�. (���ϱ���)
int Deque::pop_back()
{
	// ť�� ����ִ� ������ ���� ���
	if (!sizeq){
		std::cout << -1 << '\n';
		return -1;
	}
	// ť�� ������ �ִ� ��� ����ϰ� �޸� ������ �� ����
	else{
		int num = backNode->getData();
		std::cout << num << std::endl;
		Node* temp = backNode;
		backNode = backNode->getNext();
		if (backNode != NULL) backNode->setPrev(NULL);
		delete temp;
		sizeq--;
		return num;
	}
}

int Deque::size()
{
	std::cout << sizeq << '\n';
	return sizeq;
}

int Deque::empty()
{
	if (sizeq == 0){
		std::cout << 1 << '\n';
		return 1;
	}
	else {
		std::cout << 0 << '\n';
		return 0;
	}
}

void Deque::front() const
{
	if (!sizeq) std::cout << -1 << '\n';
	else std::cout << frontNode->getData() << '\n';
}

void Deque::back() const
{
	if (!sizeq) std::cout << -1 << '\n';
	else std::cout << backNode->getData() << '\n';
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	int n; std::cin >> n; // 1<=n<=10,000
	int data; std::string str; // 1<=data<=100,000
	Deque q;

	while (n--){
		std::cin >> str;
		if (!str.compare("push_front")){
			std::cin >> data;
			q.push_front(data);
		}
		else if (!str.compare("push_back")){
			std::cin >> data;
			q.push_back(data);
		}
		else if (!str.compare("pop_front"))
			q.pop_front();
		else if (!str.compare("pop_back"))
			q.pop_back();
		else if (!str.compare("size"))
			q.size();
		else if (!str.compare("empty"))
			q.empty();
		else if (!str.compare("front"))
			q.front();
		else if (!str.compare("back"))
			q.back();
	}

	return 0;

}