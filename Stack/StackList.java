package stack;

class Stack {
	private Node top;
	private int size;
	
	public Stack() {
		this.top = null;
		this.size = 0;
	}
	
	private class Node {
		private Object data;
		private Node nextNode;
		
		public Node(Object data) {
			this.data = data;
			nextNode = null;
		}
	}
	
	public void push(Object data) {
		Node newNode = new Node(data);
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
	
	public Object top() {
		if(empty()) {
			System.out.println("Stack is empty!!");
			return null;
		} else
			return top.data;
	}
}

public class StackList {
	
	public static void main(String[] args) {
		Stack s = new Stack();
		s.push(1);
		s.push("hello");
		System.out.println(s.top());
	}

}
