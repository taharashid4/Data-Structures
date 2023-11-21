#include <iostream>
#pragma once

template <typename T> class Node {
public:
  T data;
  Node *next;

  Node(T d = NULL) : data(d), next(nullptr) {}
};

template <typename T> class Queue {
public:
  Node<T> *front;
  Node<T> *rear;

  Queue() : front(nullptr), rear(nullptr) {}

  void enqueue(T item) {
    Node<T> *newNode = new Node<T>(item);

    if (front == nullptr)
      front = newNode;

    if (rear == nullptr)
      rear = newNode;
    else {
      rear->next = newNode;
      rear = newNode;
    }
  }

  T dequeue() {
    if (front != nullptr) {
      if (front == rear) {
        T temp = front->data;
        delete front;
        front = nullptr;
        rear = nullptr;
        return temp;
      } else {
        T temp = front->data;
        Node<T> *nextNode = front->next;
        delete front;
        front = nextNode;
        return temp;
      }
    }
  }

  T peek() {
    if (front != nullptr)
      return front->data;
  }

  bool is_empty() { return front == nullptr; }

  int size() {
    int size = 0;
    Node<T> *temp = front;
    while (temp) {
      ++size;
      temp = temp->next;
    }
    return size;
  }

  void clear() {
    int s = size();
    for (int i = 0; i < s; ++i) {
      Node<T> *temp = front;
      front = front->next;
      delete temp;
    }
  }

  ~Queue() { clear(); }
};
