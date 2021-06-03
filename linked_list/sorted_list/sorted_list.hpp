#pragma once
#include<iostream>
#include<cstddef>

template<typename T>
class sorted_list;

template<typename T>
class Node{
  Node* next_;
  Node* prev_;
  T val_;
  Node(T val) : next_{nullptr}, prev_{nullptr}, val_{val}{  }
  Node(T&& val) : val_{std::move(val)} {  };

  friend sorted_list<T>;
};

template<typename T>
class sorted_list{  
 public:
Node<T>* head_;
Node<T>* tail_;
size_t size_;

sorted_list( ) : head_{nullptr}, tail_{nullptr}, size_{0}{  }// prazna listu
sorted_list(const sorted_list&);
sorted_list(sorted_list&&);
sorted_list& operator=(const sorted_list&);
sorted_list& operator=(sorted_list&&);
~sorted_list();

size_t size()const {return size_;}
bool empty() const {return  size_==0;
}
void add(const T&);
void add(T&&);
void print();

class Iterator;
Iterator begin();
Iterator end();
void clear();
void remove(Iterator);
Iterator find(const T&);
template<typename U>
Iterator find_if(U predicate);

};

template<typename T>
class sorted_list<T>::Iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{ 
  Node<T>* currNode_;
  Node<T>* prevNode_;
  public:
  Iterator()=default;
  Iterator(Node<T>*t, Node<T>* p) : currNode_{t}, prevNode_{p}{  }
  T& operator*(){ return currNode_->val_; }
  const T& operator*() const{ return currNode_->val_;}

  Iterator& operator++() {
    prevNode_ = currNode_;
    if (currNode_) 
      currNode_ = currNode_->next_;
    return *this;               
  }

  Iterator operator++(int) {
    auto old = *this;
    ++(*this);
    return old;
  }

  Iterator& operator--(){    
  currNode_= prevNode_;
  if(prevNode_) 
  prevNode_=prevNode_->prev_;
  return *this;
  }
  
  Iterator operator--(int){
   auto old=*this;
   --(*this);
    return old;
  }

  bool operator==(const Iterator& b) const{ return currNode_=b.currNode_; }
  bool operator!=(const Iterator& b) const { return currNode_!=b.currNode_; }

  Node<T>* getNode() const{ return currNode_; }
  Node<T>* getprevNode() const{ return prevNode_; }

friend class sorted_list;
};

template <typename T>
typename sorted_list<T>::Iterator sorted_list<T>::begin() {
    return Iterator(head_, nullptr);
}

template <typename T>
typename sorted_list<T>::Iterator sorted_list<T>::end() {
    return Iterator(nullptr, tail_);
}

template<typename T>
void sorted_list<T>::clear(){  
 Node<T>* temp=head_;
  while(temp!=nullptr){
    head_=head_->next_;
    delete temp;
    temp=head_;
  }
  tail_=nullptr;
  size_=0;
}

template<typename T>
void sorted_list<T>::add(const T& v){
  //ako je prazna
  if(head_==nullptr){
    head_=new Node<T>(v);
    tail_=head_;
    ++size_;
  }
  else if(v>tail_->val_){
    Node<T>* sljedeci=new Node<T>{v};
    tail_->next_=sljedeci;
    sljedeci->prev_=tail_;
    tail_=sljedeci;
    ++size_;
  }
  else if(v<head_->val_){
  Node<T>* temp=head_;
    Node<T>* prvi=new Node<T>{v};
    prvi->next_=temp;
    head_=prvi;
    temp->prev_=head_;
    ++size_;
  } 
  else{  //nije prazna i između head i tail se nalazi vrij
    Node<T>* temp=head_->next_;
    while(temp!=nullptr){
      if(v<temp->val_){
        Node<T>* prethodni=new Node<T>{v};
        prethodni->next_=temp;
        temp->prev_->next_=prethodni;
        prethodni->prev_=temp->prev_;
        temp->prev_=prethodni;
        ++size_; 
        break;
      }
      temp=temp->next_;
    }
  }
}

template<typename T>
void sorted_list<T>::add(T&& v){
  if(head_==nullptr){
    head_=new Node<T>(v);
    tail_=head_;
    ++size_;
  }
  else if(v>tail_->val_){
    Node<T>* sljedeci=new Node<T>(v);
    tail_->next_=sljedeci;
    sljedeci->prev_=tail_;
    tail_=sljedeci;
    ++size_;
  }
  else if(v<head_->val_){
 Node<T>* temp=head_;
    Node<T>* prvi=new Node<T>{v};
    prvi->next_=temp;
    head_=prvi;
    temp->prev_=head_;
    ++size_;
  
  } 
  else{  //nije prazna i između head i tail se nalazi vrij
    Node<T>* temp=head_->next_;
    while(temp!=nullptr){
      if(v<temp->val_){
        Node<T>* prethodni=new Node<T>{v};
        prethodni->next_=temp;
        temp->prev_->next_=prethodni;
        prethodni->prev_=temp->prev_;
        temp->prev_=prethodni;
        ++size_; 
        break;
      }
      temp=temp->next_;
    }
  }
}

template<typename T>
typename sorted_list<T>::Iterator sorted_list<T>::find(const T& value){
  Node<T>* tmp=head_;
   while (tmp != nullptr) {
    if (tmp->val_ == value) {
      return Iterator{tmp, tmp->prev_};

    }
    tmp->prev_ = tmp;  
    tmp = tmp->next_;
  }
  return end();
}

template<typename T>
template<typename U> 
typename sorted_list<T>::Iterator sorted_list<T>::find_if(U predicate){
   Node<T>* temp=head_;
   while(temp!=nullptr){
     if(predicate(temp->val_)){
            return Iterator(temp, temp->prev_);
               
     }
        temp=temp->next_;        
   }
    return end();
}

template<typename T>
void sorted_list<T>::remove(Iterator it){
  if(head_==nullptr){
  std::cout << "List is empty!" << std::endl;
  }
  else if(head_==it.getNode()){
    Node<T>* temp=head_;
    head_->next_->prev_=nullptr;
    head_=head_->next_;
    delete temp;
    --size_;
   
  }else if(tail_==it.getNode()){
    Node<T>* temp=tail_;
    tail_=tail_->prev_;
    tail_->next_=nullptr;
    delete temp;
    --size_;

  }else{
    it.getprevNode()->next_=it.getNode()->next_;
    it.getNode()->next_->prev_=it.getprevNode(); //clan prije obrisanog 
    delete it.getNode();
    --size_;

  }
}

//copy constructor
template<typename T>
sorted_list<T>::sorted_list(const sorted_list<T>& other) : head_{nullptr}, tail_{nullptr}, size_{0} {
if(!other.empty()){ 
  head_=new Node<T>(other.head_->val_); 
  tail_=head_;
  //napravljen 1. cvor nove liste
 auto temp=other.head_; 
  while(temp){
    tail_->next_=new Node<T>(temp->val_);
    tail_->next_->prev_=tail_;            
    tail_=tail_->next_;
  }
  size_=other.size_;
}
}

//move constructor
template<typename T>
sorted_list<T>::sorted_list(sorted_list&& other) : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
  other.head_=other.tail_=nullptr;
  other.size_=0;
}

//copy op=
template<typename T>
sorted_list<T>& sorted_list<T>::operator=(const sorted_list<T>& other){
 clear();
 
  head_=new Node<T>{other.head_->val_}; //prvi 
  tail_=head_;
  auto temp=other.head_->next_;   //ostali
  while(temp!=nullptr){
    tail_->next_=new Node<T>{temp->value};
    tail_->next_->prev_=tail_;
    tail_=tail_->next_;
    temp=temp->next_;

  }
  size_=other.size_;
  return *this;
}

//move op= 
template<typename T>
sorted_list<T>& sorted_list<T>::operator=(sorted_list<T>&& other){
  clear();

  head_=other.head_;
  tail_=other.tail_;
  size_=other.size_;
  other.head_=nullptr;
  other.tail_=nullptr;
  other.size_=0;

  return *this;
}

//destructor
template<typename T>
sorted_list<T>::~sorted_list(){
 clear();
}

template<typename T>  
void sorted_list<T>::print(){
  Node<T>* temp=head_;
  while(temp!=nullptr){
    std::cout<< temp->val_ << std::endl;
  temp=temp->next_;
  }
}




