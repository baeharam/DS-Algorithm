#include <iostream>

// �����͸� ��� ���Ŭ����
template <typename T>
class Node{
private:
	T data; // ���� int�� ������
	Node* prevNode; // ������带 ����Ű�� �����ͺ���
public:
	Node(T data, Node* prevNode); // ������
	T getData() const { return data; } // data�� ��ȯ�ϴ� ����Լ�, ����� �ǵ��� �ʱ� ������ const�̴�.
	void setPrev(Node* prev); // prevNode�� �ʱ�ȭ�ϴ� ����Լ�
	Node* getPrev() const; // prevNode�� ��ȯ�ϴ� ����Լ�, ����� �ǵ��� �ʱ� ������ const�̴�.
};

// ������
// ��� �ʱ�ȭ ����Ʈ�� ����ؼ� �ʱ�ȭ�Ѵ�.
// ���ڰ� ���� ��� 0�� NULL�� �ʱ�ȭ�Ѵ�.
template <typename T>
Node<T>::Node(T num = 0, Node* prev = NULL)
	:data(num), prevNode(prev)
{}

// prevNode �ʱ�ȭ �Լ�
// prevNode�� ���ڷ� �޾Ƽ� �ʱ�ȭ��Ų��.
template <typename T>
void Node<T>::setPrev(Node* prev)
{
	this->prevNode = prev;
}

// prevNode ��ȯ �Լ�
// prevNode�� ��ȯ�Ѵ�.
template <typename T>
Node<T>* Node<T>::getPrev() const
{
	return this->prevNode;
}

// ��带 �̾��ִ� ���� Ŭ����
template <typename T>
class Stack{
private:
	Node<T>* topNode; // �ֻ��� ��带 ����Ű�� ������ ����
	int size; // ���ÿ� ���� �� ������ ���� ����
public:
	Stack(); // ������
	~Stack(); // �Ҹ���
	void Push(const T& data); // data�� ���ÿ� �ִ´�.
	T Pop(); // data�� ���ÿ��� ���� ��ȯ�Ѵ�.
	bool IsEmpty() const; // ������ ����ִ��� ��ȯ�Ѵ�.
	int Size() const; // ������ ����� ��ȯ�Ѵ�.
	T Top() const; // ���� ���� ���� �ִ� data�� ��ȯ�Ѵ�.
};

// ������
// �⺻ �������̸� NULL�� 0���� �ʱ�ȭ�Ѵ�.
template <typename T>
Stack<T>::Stack() :topNode(NULL), size(0)
{}

// �Ҹ���
// topNode�� prevNode�� �Ҵ�Ǿ��� ��� �޸𸮸� �����Ѵ�.
template <typename T>
Stack<T>::~Stack()
{
	// ���� �ֻ��� ��带 ����Ű�� �����͸� top�� �Ҵ��Ѵ�.
	Node<T>* top = this->topNode;
	while (top){
		// �޸� ������ ���� �ӽ÷� ���� old�� top�� �Ҵ��Ѵ�.
		Node<T>* old = top;
		// top->getPrev()�� ���� this->topNode->getPrev()�� �Ǿ��־
		// ���� 1874�� �������� ��� ��Ÿ�� ���� �߻�
		// �����ؼ� �ٸ� ���� �˾Ƴ��ֽ�
		// top�� �Ʒ����� ������Ʈ��Ű��
		top = top->getPrev();
		// old�� �޸𸮸� �����Ѵ�
		delete old;
	}
}

// Push
template <typename T>
void Stack<T>::Push(const T& data)
{
	// ����ִٸ� ���ο� ��ü�� �Ҵ��Ѵ�.
	if (this->topNode == NULL)
		this->topNode = new Node<T>(data, NULL);
	// �ƴ϶�� �����ͺ����� topNode�� ���
	// topNode�� ���ο� ��ü�� �����Ѵ�. temp�� prevNode�� ���Եȴ�.
	else{
		Node<T>* temp = topNode;
		this->topNode = new Node<T>(data, temp);
	}
	this->size++;
}

// ���� ���� �� ���� �� ����
template <typename T>
T Stack<T>::Pop()
{
	// �ӽú����鿡 �����Ϳ� topNode�� ��´�.
	int temp = this->topNode->getData();
	Node<T> *old = this->topNode;

	// ���� prevNode�� NULL�̶�� topNode�� NULL�� �ʱ�ȭ���ָ� �ȴ�.
	if (this->topNode->getPrev() == NULL)
		this->topNode = NULL;
	// �ƴ϶�� topNode�� prevNode�� ��ĭ�� �����ش�.
	else{
		this->topNode = this->topNode->getPrev();
		this->topNode->setPrev(this->topNode->getPrev());
	}

	// �޸𸮿� �Ҵ�Ǿ��� topNode�� �������ְ� ���̰� �پ���.
	// �����͸� �������ش�.
	this->size--;
	delete old;
	return temp;
}

// ����ִ��� ���� ����
template <typename T>
bool Stack<T>::IsEmpty() const
{
	if (this->size) return false;
	else return true;
}

// � �ִ��� ����
template <typename T>
int Stack<T>::Size() const
{
	return this->size;
}

// ���� ���� �� �������� �ʰ� ����
template <typename T>
T Stack<T>::Top() const
{
	return this->topNode->getData();
}

int main(void)
{
	Stack<int> s;

	// ���ÿ� 1,2�� �ִ´�.
	s.Push(1);
	s.Push(2);

	// LIFO�̹Ƿ� 2,1�� ������.
	std::cout << s.Pop() << '\n';
	std::cout << s.Pop() << '\n';

	// ���ÿ� 5�� �ִ´�.
	s.Push(5);
	// ���� �ʰ� ��¸��Ѵ�.
	std::cout << s.Top() << '\n';
	// 5�� �����ϱ� ������� 1
	std::cout << s.Size() << '\n';

	return 0;

}
