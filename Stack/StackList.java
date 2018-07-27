package stack;

class Stack<E> {
	private Node<E> top;
	private int size;
	
	public Stack() {
		this.top = null;
		this.size = 0;
	}
	
	private class Node<T> {
		private T data;
		private Node<T> nextNode;
		
		public Node(T data) {
			this.data = data;
			nextNode = null;
		}
	}
	
	public void push(E data) {
		Node<E> newNode = new Node<E>(data);
		newNode.nextNode = top;
		top = newNode;
		size++;
	}
	
	public void pop() {
		if(size==0) System.out.println("Stack is empty!!");
		else {
			top = top.nextNode;
			size--;
		}
	}
	
	public int size() {
		return size;
	}
	
	public boolean empty() {
		return size==0 ? true : false;
	}
	
	public E top() {
		if(empty()) {
			System.out.println("Stack is empty!!");
			return null;
		} else
			return top.data;
	}
}

public class StackList {
	
	public static void main(String[] args) {
		Stack<Integer> s = new Stack<Integer>();
		Stack<String> s2 = new Stack<String>();
		s.push(1);
		s.push(2);
		s2.push("hi");
		System.out.println(s2.top());
	}

}
