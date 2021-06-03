#pragma once
#include <iostream>
#include<ctime>
#include<stdexcept> 

class Transaction
{
  public:
    double value{};
    std::string datetime{}; 
    bool dodaj=false;
    bool oduzmi=false;

    Transaction* next{nullptr};
    Transaction() {
      time_t now=time(0);
      datetime=ctime(&now);
    }

    template <typename U>
      Transaction(U&& val) : value(std::forward<U>(val)) { 
        time_t now=time(0);
        datetime=ctime(&now);
      } 
};


class Account {
  Transaction* first{nullptr};
  Transaction* last{nullptr};
  size_t transactions_{};
  double balance{};
  bool dodaj=false;
  bool oduzmi=false;

  void destroyAcc(){
    auto temp = first;
    while(first){
      temp = temp -> next;
      delete first;
      first = temp;
    }
    first=last=nullptr;
    transactions_=0;
  }

  public:
  Account() = default;
  Account(const Account& rhs) {
    auto otherNode=rhs.first;
    while(otherNode){
      this->addTransaction(otherNode->value);
      otherNode=otherNode->next;
    }
  }

  Account(Account&& rhs) : first{rhs.first}, last{rhs.last}, transactions_{rhs.transactions_} {
    rhs.first=rhs.last=nullptr;
    rhs.transactions_=0;
  }

  template <typename U>
    void addTransaction(U&& el)
    {
      auto newTransaction = new Transaction(std::forward<U>(el));
      if (first == nullptr)
      {
        first = last = newTransaction;
      }
      else
      {
        last->next = newTransaction;
        last = last->next;
      }
      ++transactions_;
    }

  Account& operator=(const Account& rhs) {
    if(this!= &rhs){
      destroyAcc();
      auto otherNode= rhs.first;
      while(otherNode){
        this->addTransaction(otherNode->value);
        otherNode=otherNode->next;

      }
    }

    return *this;
  }

  Account& operator=(Account&& rhs) {
    first=rhs.first;
    last=rhs.last;
    transactions_=rhs.transactions_;
    first=last=nullptr;
    transactions_=0;

    return *this;
  }

  ~Account() { destroyAcc(); } 

  void addTransaction()
  {
    std::cout<<"Please choose one of the following options: \n 1. Deposit money \n 2. Withdraw money \n";
    int choice;
    std::cin>>choice;
    double value;

    if(choice == 1){
      std::cout<<"Enter value: "; 
      std::cin>>value;
      dodaj = true;
    }
    else if(choice == 2){
      std::cout<<"Enter value: ";
      std::cin>>value;
      oduzmi = true;
    }
    else{ std::cout<<"Wrong input!!!\n"; 

    }

    if(value){
      auto newTransaction=new Transaction(value);

      if (first == nullptr) {
        first = last = newTransaction;
      }
      else{
        last->next = newTransaction;
        last = last->next;
      }
      ++transactions_;

      std::cout<<"Transaction added!\n";
    }
  }

  void applyTransaction() {
    if(!empty()){ 
      if(dodaj){ (this->balance) += first->value;
      }
      else{ (this->balance) -= first->value;
      }
      std::cout<<"Transaction applied!"<<std::endl;
      discardTransaction();
    }

    else{ std::cout<<"Transaction not found!"<<std::endl; }
  }

  void discardTransaction() 
  {
    if (size() == 0)
      throw std::out_of_range("Nema tekućih transakcija!");
    else if (size() == 1)
    {
      delete first;
      first = last=nullptr;
    }
    else
    {
      auto tmp = first;
      first = first->next;
      delete tmp;
    }
    --transactions_;
    std::cout<<"Transaction discarded!\n";
  }

  double getBalance() const { return this->balance; }

  const double& front() const 
  {
    if (!first)
      throw std::out_of_range("Nema tekućih transakcija!");

    return first->value;  
  }

  double& front() 
  {
    if (!first)
      throw std::out_of_range("Nema tekućih transakcija!");

    return first->value;
  }

  const double& back() const 
  {
    if (!first)
      throw std::out_of_range("Nema tekućih transakcija");
    return last->value;
  }

  double& back() 
  {
    if (!first)
      throw std::out_of_range("Nema tekućih transakcija!");
    return last->value;
  }

  size_t size() const 
  {
    return transactions_;
  }

  bool empty() const 
  {
    return transactions_==0;
  }

  void printTransaction() const {
    if(!empty()) {
      std::cout<<"Pending transaction is: "<<front()<<", at  "<<this->first->datetime<<std::endl;   
    }
    else{ std::cout<<"Transaction not found!\n"; }
  }

};

