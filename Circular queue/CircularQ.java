package com.haram;

class CircularQueue {
    private Object queue[];
    private int front, back;
    private int capacity;

    public CircularQueue(int capacity) {
        this.capacity = capacity;
        this.queue = new Object[capacity];
        this.front = this.back = 0;
    }

    public void enqueue(Object data) {
        queue[back]=data;
        if(back == capacity-1) back = 0;
        else back++;
    }

    public void dequeue() {
        if(size()==0)
            System.out.println("There is no data!");
        else {
            if(front == capacity-1) front=0;
            else front++;
        }
    }

    public int size() {
        if(front <= back) return back-front;
        else return capacity-front+back;
    }

    public boolean empty() {
        if(front <= back) return (back-front)==(capacity-1);
        else return back+1==front;
    }

    public Object front() {
        return queue[front];
    }
}

public class CircularQ {
    public static void main(String[] args) {
        CircularQueue cq = new CircularQueue(10);
        cq.enqueue(3);
        cq.enqueue("hi");
        cq.enqueue(2.53);

        System.out.println(cq.front());
        cq.dequeue();
        System.out.println(cq.front());
        System.out.println(cq.size());
        cq.dequeue();
        cq.dequeue();
        cq.dequeue();
    }
}
