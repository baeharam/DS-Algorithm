package stack;


class Stack {
	private Object[] stack;
	private int top;
	private int size;
	private int capacity;
	
	public Stack(int capacity) {
		this.capacity = capacity;
		this.stack = new Object[capacity];
		this.top = 0;
		this.size = 0;
	}
	
	public void push(Object data) {
		if(top==capacity-1) System.out.println("Stack is full!");
		else {
			stack[top]=data;
			top++;
			size++;
			System.out.println(data + " is pushed");
		}
	}
	
	public void pop() {
		if(top==0) {
			System.out.println("Stack is empty!");
		}
		else {
			top--;
			size--;
		}
	}
	
	public boolean empty() {
		return size==0 ? true : false;
	}
	
	public boolean full() {
		return size==capacity ? true : false;
	}
	
	public Object top() {
		if(empty()) {
			System.out.println("Stack is empty, cannot access to top!");
			return null;
		} else 
			return stack[top-1];
	}
}


public class StackArray {
	public static void main(String[] args) {
		Stack s = new Stack(10);
		s.push("hello world");
		s.push(13);
		System.out.println(s.top());
	}
}
