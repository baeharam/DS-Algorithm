#include <iostream>
#include <string>

// �켱���� ť�� ���� ��� Ŭ����
template <typename T>
class Node{
private:
	T data;
	// ���� ���� ���� ��带 ����Ű�� �����͸� ���´�.
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
	Node<T>* frontNode; // �� �� ��带 ����Ű�� ������
	Node<T>* backNode; // �� �� ��带 ����Ű�� ������
	int sizeq; // �켱���� ť�� ������
	std::string type; // �켱���� ť�� ���� ���
public:
	PriorityQueue(std::string qtype="less") :frontNode(NULL), backNode(NULL), sizeq(0),type(qtype){
		if (!type.compare("less")) std::cout << "�������� ���� �켱���� ť�� �����߽��ϴ�.\n";
		else std::cout << "�������� ���� �켱���� ť�� �����߽��ϴ�.\n";
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

// frontNode ���� ��� �������� ���鼭 �޸� ����
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
// �����͸� �ִ� �Լ�
void PriorityQueue<T>::enqueue(T data)
{
	// �ϴ� ���ο� ��� ��ü�� �ϳ� ����
	Node<T>* newNode = new Node<T>(data, NULL);

	// �ƹ��͵� ���ٸ� frontNode�� backNode�� �ʱ�ȭ
	if (empty()) frontNode = backNode = newNode;
		
	// �ϳ��� �ִٸ� ���� less(��������)���� greater(��������)���� Ȯ���Ѵ�.
	else{
		// ������ ������ �ӽ������� tempNode�� frontNode�� �ʱ�ȭ�Ѵ�.
		Node<T>* tempNode = frontNode;
		// 1. less(��������)�� ���
		if (!type.compare("less")){
			// tempNode�� NULL�� �� ������ �����ϴµ�
			while (tempNode){
				// ���� ����� ���� �� Ŭ ��� �������� �Ѿ��.
				if (tempNode->getData() > data) tempNode = tempNode->getNext();
				// ���� ����� ���� ���� ��� newNode�� ���� �ٲٰ� �������´�.
				else{
					T temp = tempNode->getData();
					tempNode->setData(data);
					newNode->setData(temp);
					break;
				}
			}
		}

		// 2. greater(��������)�� ���
		else if (!type.compare("greater")){
			// tempNode�� NULL�� �� ������ �����ϴµ�
			while (tempNode){
				// ���� ����� ���� �� ���� ��� �������� �Ѿ��.
				if (tempNode->getData() < data) tempNode = tempNode->getNext();
				// ���� ����� ���� ū ��� newNode�� ���� �ٲٰ� �������´�.
				else{
					T temp = tempNode->getData();
					tempNode->setData(data);
					newNode->setData(temp);
					break;
				}
			}
		}
		// �߰��� �ٲ� �����
		if (tempNode){
			// newNode�� ���� ��带 tempNode�� �������� �����ϰ�
			newNode->setNext(tempNode->getNext());
			// tempNode�� ���� ��带 newNode�� �����Ѵ�.
			tempNode->setNext(newNode);
			// �׸��� ���� ������ ��带 backNode�� �ʱ�ȭ��Ų��.
			while (tempNode->getNext())
				tempNode = tempNode->getNext();
			backNode = tempNode;
		}
		// �߰��� �ٲ��� �ʾҴٸ�
		else{
			// ���� ��Ĵ�� ������ ��� �������� newNode�� �����Ѵ�.
			backNode->setNext(newNode);
			backNode = newNode;
		}
	}
	if (!type.compare("less")) std::cout << "�������� ���� �켱���� ť�� " << data << "�� �����߽��ϴ�..\n";
	else std::cout << "�������� ���� �켱���� ť�� " << data << "�� �����߽��ϴ�..\n";	
	std::cout << "-----------------------------------------------------\n";
	sizeq++;
}

// �ݵ�� ����ִ��� Ȯ�� �ؾ���
template <typename T>
// �����͸� �����ϴ� �Լ�
T PriorityQueue<T>::dequeue()
{
	if (!type.compare("less")) std::cout << "�������� ���� �켱���� ť���� " << frontNode->getData() << "�� �����߽��ϴ�..\n";
	else std::cout << "�������� ���� �켱���� ť���� " << frontNode->getData() << "�� �����߽��ϴ�..\n";
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
	std::cout << "���� �տ� �ִ� ���� " << frontNode->getData() << "�Դϴ�.\n";
	return frontNode->getData();
}

template <typename T>
T PriorityQueue<T>::back() const
{
	std::cout << "���� �ڿ� �ִ� ���� " << backNode->getData() << "�Դϴ�.\n";
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