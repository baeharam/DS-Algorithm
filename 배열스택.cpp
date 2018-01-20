#include <iostream>
#include <string>
#include <stack>

template<typename T>
class Stack{
private:
	int top;
	int size;
	T* data;
public:
	// ������ �� ũ�⸦ �ް� �� ũ��� �������� �迭�� �Ҵ��Ѵ�.
	// ó�� top�� 0���� �ʱ�ȭ
	Stack(int _size) :size(_size), top(0)
	{
		data = new T[size];
	}

	// �Ҹ��ڿ��� �����Ҵ� �޸� ����
	~Stack()
	{
		delete[] data;
	}

	// �����͸� �޾Ƽ� ���ÿ� �ִ´�.
	void push(T val)
	{
		// �ְ� top ����
		data[top++] = val;
		size++;
	}

	// �����͸� �����ϰ� ��ȯ�Ѵ�.
	// top�� push�� �����Ǿ����Ƿ� ���ҽ�Ű�� ��ȯ
	T pop()
	{
		if (empty()){
			std::cout << "Stack is empty!" << '\n';
			return static_cast<T>(-1);
		}
		else{
			size--;
			return data[--top];
		}
	}

	// �����͸� ��ȯ�Ѵ�.
	// top�� push�� �����Ǿ����Ƿ� �ϳ����� ��ȯ
	T Top()
	{
		return data[top-1];
	}

	// ������ ����� ��� true�� ��ȯ�Ѵ�.
	bool empty() const
	{
		return top ? false : true;
	}

	// ������ ũ�⸦ ��ȯ�Ѵ�.
	int Size() const
	{
		return size;
	}
};

int main(void)
{
	Stack<char> a(10);
	std::stack<std::string> s;
	s.pop();

	a.pop();

	a.push('a');
	a.push('b');

	std::cout << a.pop() << '\n';
	std::cout << a.Top() << '\n';
	std::cout << a.empty() << '\n';
	std::cout << a.Size() << '\n';

	return 0;
}