#include <iostream>

template <typename T>
class Queue{
private:
	T* data;
	int size;
	int front;
	int back;
public:
	// 생성자에서 크기를 받고 front와 back을 초기화해준다.
	// 동적할당까지.
	Queue(int _size) :size(_size), front(0), back(-1)
	{
		data = new T[size];
	}
	// 소멸자에서 동적할당 해제
	~Queue()
	{
		delete[] data;
	}

	// 값을 받아서 back이 가리키고 있는 곳에 넣은 후 증가시킨다.
	void enqueue(T val)
	{
		data[++back] = val;
		size++;
	}

	// 제일 앞의 값을 제거함으로 뒤에서부터 땡겨야 한다.
	// 이 부분 때문에 굉장히 비효율적이다. 제거한 값을 반환한다.
	T dequeue()
	{
		T temp = data[front];
		for (int i = front + 1; i <= back; i++)
			data[i - 1] = data[i];
		back--; size--;
		return temp;
	}

	// 앞의 값만 반환
	// 비어있는지 반드시 확인해야함
	T Front() const
	{
		return data[front];
	}

	// 뒤의 값만 반환
	// 비어있는지 반드시 확인해야함
	T Back() const
	{
		return data[back];
	}

	// 크기 반환
	int Size() const
	{
		return size-1;
	}

	// 비어있는지 여부 반환
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