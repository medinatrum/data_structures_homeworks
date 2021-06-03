#pragma once
#include<iostream>
#include<string>

int generateId(){
    static int counter=0;
      return ++counter;
}

class ToDoTask{
  int id_;
  std::string title_;
  std::string description_;
  int priority_;
  public:
  ToDoTask()=default;
  ToDoTask(const std::string& naslov, const std::string& opis, const int& prioritet) : title_{naslov},
    description_{opis}, priority_{prioritet} { id_=generateId(); }

  bool operator<(ToDoTask other){
    return priority_<other.priority_;

  }
  bool operator>(ToDoTask other){
    return priority_>other.priority_;

  }

  int getId()const{ return id_;  }
  friend std::ostream& operator<<(std::ostream&, const ToDoTask&);
  friend std::istream& operator>>(std::istream&, ToDoTask&);

};

std::ostream& operator<<(std::ostream& out, const ToDoTask& task){
  out<<"Task id: "<<task.id_<<" "<<"Naslov: "<<task.title_<<" Opis: "<<task.description_<<"Prioritet: "<<task.priority_<<" ";
  return out; 

}

std::istream& operator>>(std::istream& in, ToDoTask& task){
  task.id_=generateId();
  std::cout<<"Upisite naslov vaseg zadataka:";
  in>>task.title_;
  std::cout<<"Upisite opis vaseg zadatka:";
  in>>task.description_;
  std::cout<<"Upisite prioritet vaseg zadatka:";
  in>>task.priority_;
  return in;

}

