#ifndef EXAMPLEPROJECT_QUEUE_H
#define EXAMPLEPROJECT_QUEUE_H

#include <cstddef> // for size_t
#include <iostream>

template <typename E> // E is the element type.
class Queue {
 public:
  Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

  void Enqueue(const E& element) {
    Node* new_node = new Node(element, nullptr);
    if (tail_ != nullptr) {
      tail_->next = new_node;
    }
    tail_ = new_node;
    if (head_ == nullptr) {
      head_ = new_node;
    }
    size_++;
  }

  E* Dequeue() {
    if (head_ == nullptr) {
      return nullptr;
    }
    E* result = new E(head_->data);
    Node* old_head = head_;
    head_ = head_->next;
    delete old_head;
    size_--;
    return result;
  }

  size_t size() const { return size_; }

 private:
  struct Node {
    E data;
    Node* next;
    Node(const E& data, Node* next) : data(data), next(next) {}
  };

  Node* head_;
  Node* tail_;
  size_t size_;
};


#endif
