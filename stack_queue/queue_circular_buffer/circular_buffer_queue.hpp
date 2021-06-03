#pragma once
#include<iostream>
#include<stdexcept>

template<typename T>
class buffer{
  int size_{}; 
  int capacity_{};   
  int front_{-1};
  int back_={-1};
  T* elements_=nullptr;

  public:
  buffer() : capacity_{100}, elements_{new T[capacity_]} { } 
  buffer(int max) : capacity_{max}, elements_{new T[max]}  { }  
  buffer(const buffer& rhs) : size_{rhs.size_}, capacity_{rhs.capacity_}, front_{rhs.front_}, back_{rhs.back_}, elements_{new T[rhs.capacity_]} {
    std::copy(rhs.elements_, rhs.elements_+capacity_, elements_); 
  }

  buffer(buffer&& rhs) : size_{rhs.size_}, capacity_{rhs.capacity_}, front_{rhs.front_}, back_{rhs.back_}, elements_{rhs.elements_}{
    rhs.size_=0; 
    rhs.capacity_=0;
    rhs.front_=-1;
    rhs.back_=-1;
    rhs.elements_=nullptr;

  }

  buffer& operator=(const buffer& rhs){
    if(this != &rhs){
      delete[] elements_;
      elements_=new T[rhs.capacity_]; 
      size_=rhs.size_;
      std::copy(rhs.elements_, rhs.elements_+rhs.capacity_, elements_);  
      capacity_=rhs.capacity_;
      front_=rhs.front_;
      back_=rhs.back_;

    }
    return *this;
  }

  buffer& operator=(buffer&& rhs){
    delete[] elements_;
    elements_=rhs.elements_;
    size_=rhs.size_;
    capacity_=rhs.capacity_;
    front_=rhs.front_;
    back_=rhs.back_;
    rhs.capacity_=0;
    rhs.size_=0;
    rhs.front_=-1;
    rhs.back_=-1;
    rhs.elements_=nullptr;

    return *this;
  }

  ~buffer() {
    delete elements_;
    size_=0; 
    capacity_=0;
    front_=-1;
    back_=-1;
    elements_=nullptr;

  }

  bool full() const {
    return ((back_+1) % capacity_ == front_);
}

  template<typename U>
    buffer& push(U&& el){

      if(full()){
        throw std::out_of_range("Element can't be added"); } 

      back_ = (back_+1) % capacity_;
      elements_[back_] = std::forward<U>(el);
      if(front_ == -1)
        front_ = 0;

      ++size_;
      return *this;

    }

  T pop(){ 
    T el;
    if(front_ == -1){
      throw std::out_of_range("Queue is empty!"); 
    }
    else if(front_ == back_){
      el=std::move(elements_[front_]);     
      front_ =back_ = -1;

    }
    else{
      el=std::move(elements_[front_]);

      (front_ = front_ + 1) % capacity_;

    }
    --size_;
    return el;
  }

  bool empty(){ return size_ == 0; }
  int size()  { return size_;}
  int capacity() const { return capacity_; }

  T& front(){
    if(!empty()) {
      return elements_[front_];
    }
    else{
      throw std::out_of_range("Queue is empty!");
    }
  }

  const T& front() const {
    if(!empty()) {
      return elements_[front_];
    }
    else{
      throw std::out_of_range("Queue is empty!");
    }
  }

  T& back(){
    if(!empty()) {
      return elements_[back_];
    }
    else{
      throw std::out_of_range("Queue is empty!");
    }
  }

  const T& back() const {
    if(!empty()) {
      return elements_[back_];
    }
    else{
      throw std::out_of_range("Queue is empty!");
    }
  }

  void print(){
    if(!empty()){
      if(front_ <= back_){
        for(int i=front_; i<=back_; ++i){
          std::cout<<elements_[i]<<" ";
          std::cout<<std::endl;
        }
      }
      else{
        for(int i=front_; i<capacity_; ++i)
          std::cout<<elements_[i]<<" ";
        for(int i=front_; i<=back_; ++i)
          std::cout<<elements_[i]<<" ";

      }
    }
    else { std::cout<<"Queue is empty!"<<std::endl; }
  }


};
