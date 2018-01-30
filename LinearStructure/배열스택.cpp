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
	// 생성할 때 크기를 받고 그 크기로 동적으로 배열을 할당한다.
	// 처음 top은 0으로 초기화
	Stack(int _size) :size(_size), top(0)
	{
		data = new T[size];
	}

	// 소멸자에서 동적할당 메모리 해제
	~Stack()
	{
		delete[] data;
	}

	// 데이터를 받아서 스택에 넣는다.
	void push(T val)
	{
		// 넣고 top 증가
		data[top++] = val;
		size++;
	}

	// 데이터를 제거하고 반환한다.
	// top이 push때 증가되었으므로 감소시키고 반환
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

	// 데이터를 반환한다.
	// top이 push때 증가되었으므로 하나빼서 반환
	T Top()
	{
		return data[top-1];
	}

	// 스택이 비었을 경우 true를 반환한다.
	bool empty() const
	{
		return top ? false : true;
	}

	// 스택의 크기를 반환한다.
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