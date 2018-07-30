package com.company;

class Queue {
    private Object[] queue;
    private int capacity;
    private int size;

    public Queue(int size) {
        queue = new Object[size];
        capacity = 0;
        this.size = size;
    }

    public void enqueue(Object data) {
        if(full())
            System.out.println("Queue is full!");
        else {
            queue[capacity] = data;
            capacity++;
        }
    }

    public void dequeue() {
        if(empty())
            System.out.println("Queue is empty!");
        else{
            queue[capacity-1] = 0;
            capacity--;
        }
    }

    public boolean empty() {
        return capacity==0;
    }

    public boolean full() {
        return capacity==size;
    }

    public int size() {
        return capacity;
    }

    public Object front() {
        if(empty()) {
            System.out.println("There is no data!");
            return null;
        } else
            return queue[0];
    }
}

public class QueueArray {

    public static void main(String[] args) {
        Queue q = new Queue(5);
        q.enqueue(1);
        q.enqueue("hello world");
        q.enqueue(true);

        System.out.println(q.front());

        q.dequeue();
        System.out.println(q.front());
        q.dequeue();
        q.dequeue();
        System.out.println(q.front());
    }
}
