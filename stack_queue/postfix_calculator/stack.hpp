#pragma once
#include <stdexcept>
#include<iostream>

template <typename T>
class Stack {
  private:
    class Node;
    Node* first_ = nullptr;
    size_t size_ = 0;
    Node* getFirst() {return first_;}

    void destroy() {
      auto tmp = getFirst();
      while (first_)
      {
        tmp = tmp->getNext();
        delete first_;
        first_ = tmp;
      }
      first_ = nullptr;
    }

  public:
    Stack() = default;
    // copy cons
    Stack(const Stack& rhs) {
      first_=new Node(rhs.first_->value_);
      auto temp=rhs.first_->next_;
      while(temp)
      {
        first_->next_=new Node(temp->value_);
        temp=temp->next_;

      }
      size_=rhs.size_;
    }

    // move cons
    Stack(Stack&& rhs) : first_{rhs.first_}, size_{rhs.size_} {
      rhs.first_=nullptr;
      rhs.size_=0;

    }

    // copy op=
    Stack& operator=(const Stack& rhs) {
      if(this!= &rhs){
        destroy();
        size_=rhs.size_;
        first_=new Node(rhs.first_->value_);
        auto otherNode=rhs.first_->next_;
        while(otherNode){
          first_->next_=new Node(otherNode->value_);
          otherNode=otherNode->next_;

        }
        first_->next_=nullptr;

      }
      return *this;
    }

    // move op=
    Stack& operator=(Stack&& rhs) {
      destroy();
      first_=rhs.first_;
      size_=rhs.size_;
      rhs.first-=nullptr;
      rhs.size_=0;
      return *this;
    }

    // ~dtor
    ~Stack (){ destroy(); }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    template<typename U>
    void push(U&& value) {
      auto node = new Node{std::forward<U>(value), first_};
      first_ = node;
      size_++;
    }

    void pop() {
      if (empty()) return;

      auto temp = first_;
      first_ = first_->getNext();
      delete temp;
      size_--;
    }

    T& top() {
      if (first_ == nullptr)
       throw std::runtime_error("Stack is empty!");

      return first_->getValue();
    }

    const T& top() const {
      if (first_ == nullptr) 
        throw std::runtime_error("Stack is empty!");

      return first_->getValue();
    }
};

template <typename T>
class Stack<T>::Node {
  T value_;
  Node* next_;

  public:
  Node(const T& value, Node* next) : value_{value}, next_{next} {}
  Node(T&& value, Node* next) : value_{std::move(value)}, next_{next} {}

  T& getValue() { return value_; }
  Node* getNext() { return next_; }
};

