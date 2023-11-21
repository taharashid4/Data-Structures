#include <iostream>
#pragma once

template <typename T> struct Node {
  Node *behind;
  T data;
  Node(T dat = NULL) : behind(nullptr), data(dat) {}
  ~Node() {
    if (behind) {
      delete behind;
      behind = nullptr;
    }
  }
};

template <typename T> class Stack {
  int currSize;

public:
  Node<T> *tail;

  Stack() : tail(nullptr), currSize(0) {}

  void push(const T data) {
    if (tail == nullptr) {
      tail = new Node<T>(data);
    } else {
      Node<T> *newNode = new Node<T>(data);
      newNode->behind = tail;
      tail = newNode;
    }
    ++currSize;
  }

  T pop() {
    if (tail != nullptr) {
      T data = tail->data;
      tail = tail->behind;
      --currSize;
      return data;
    }
  }

  T peek() {
    if (tail)
      return tail->data;
  }

  void clear() {
    while (!isEmpty())
      pop();
    tail = nullptr;
  }

  bool isEmpty() { return tail == nullptr; }

  int size() { return currSize; }

  ~Stack() { clear(); }
};
