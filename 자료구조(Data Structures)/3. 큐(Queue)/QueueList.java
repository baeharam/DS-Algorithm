package com.company;

class Queue<E> {

    private Node<E> frontNode;
    private int capacity;

    Queue() {
        frontNode = new Node<E>();
        capacity = 0;
    }

    private class Node<T> {
        private T data;
        private Node<T> backNode;

        private Node(){}

        private Node(T data) {
            this.data = data;
            this.backNode = null;
        }
    }

    void enqueue(E data) {
        System.out.println(data + " is enqueued!");
        Node<E> newNode = new Node<E>(data);
        newNode.backNode = frontNode;
        frontNode = newNode;
        capacity++;
    }

    void dequeue() {
        if(empty()) System.out.println("There is no data!");
        else {
            System.out.println(frontNode.data + " is dequeued!");
            frontNode = frontNode.backNode;
            capacity--;
        }
    }

    E front() {
        if(empty()) {
            System.out.println("There is no data!");
            return null;
        }
        else return frontNode.data;
    }

    boolean empty() {
        return capacity==0;
    }

    int size() {
        return capacity;
    }

}


public class QueueList {
    public static void main(String[] args) {
        Queue<Integer> q = new Queue<Integer>();
        q.enqueue(3);
        q.enqueue(10);
        q.dequeue();
        System.out.println("front data is " + q.front());
        Queue<String> sq = new Queue<String>();
        sq.enqueue("Hello World!");
        System.out.println("front data is " + sq.front());
        sq.dequeue();
        System.out.println("There is "+q.size() + " data in queue q");
    }
}
