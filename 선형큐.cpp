#include <iostream>

template <typename T>
class Queue{
private:
	T* data;
	int size;
	int front;
	int back;
public:
	// �����ڿ��� ũ�⸦ �ް� front�� back�� �ʱ�ȭ���ش�.
	// �����Ҵ����.
	Queue(int _size) :size(_size), front(0), back(-1)
	{
		data = new T[size];
	}
	// �Ҹ��ڿ��� �����Ҵ� ����
	~Queue()
	{
		delete[] data;
	}

	// ���� �޾Ƽ� back�� ����Ű�� �ִ� ���� ���� �� ������Ų��.
	void enqueue(T val)
	{
		data[++back] = val;
		size++;
	}

	// ���� ���� ���� ���������� �ڿ������� ���ܾ� �Ѵ�.
	// �� �κ� ������ ������ ��ȿ�����̴�. ������ ���� ��ȯ�Ѵ�.
	T dequeue()
	{
		T temp = data[front];
		for (int i = front + 1; i <= back; i++)
			data[i - 1] = data[i];
		back--; size--;
		return temp;
	}

	// ���� ���� ��ȯ
	// ����ִ��� �ݵ�� Ȯ���ؾ���
	T Front() const
	{
		return data[front];
	}

	// ���� ���� ��ȯ
	// ����ִ��� �ݵ�� Ȯ���ؾ���
	T Back() const
	{
		return data[back];
	}

	// ũ�� ��ȯ
	int Size() const
	{
		return size-1;
	}

	// ����ִ��� ���� ��ȯ
	bool empty() const
	{
		return back==-1 ? true : false;
	}
};

int main(void)
{
	Queue<char> q(10);

	q.enqueue('a');
	q.enqueue('b');

	std::cout << q.dequeue() << '\n';
	std::cout << q.Front() << '\n';
	std::cout << q.Back() << '\n';

	return 0;
}