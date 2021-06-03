#pragma once
#include "stack.hpp"
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

class PostfixCalc{
  Stack<int>operands;
  public:
  PostfixCalc() = default;

  bool isOperator(const std::string& op);
  void readIn(std::istream& input);
};

bool PostfixCalc::isOperator(const std::string& op){
  if(op.at(0)=='+' || op.at(0)=='-' || op.at(0)=='/' || op.at(0)=='*'){
    return true;
  }
  return false;
}

void PostfixCalc::readIn(std::istream& in){
  int left, right, result;
  std::string tmp;

  while(getline(in, tmp))
  {
    std::istringstream tokens{tmp};  
    std::string num{};

    try{
      while(tokens >> num){
        if(!isOperator(num)){
          operands.push(std::stoi(num)); 
        }
        else{ //ako jeste operator 
          right=operands.top(); 
          operands.pop();
          left=operands.top();
          operands.pop();

          switch(num.at(0)) {
            case '+': {

                        result=left+right;
                        operands.push(result);
                        break;

                      }
            case '-' : {
                         result = left - right;
                         operands.push(result);
                         break;
                       }
            case '/': {
                        result = left / right;
                        operands.push(result);
                        break;
                      }
            case '*' : {
                         result = left * right;
                         operands.push(result);
                         break;
                       }

            default : break;
          }
        }
      }
      std::cout<<"Result: "<<operands.top()<<std::endl;

    }

    catch(...){ 
      std::cout<<"Wrong input!!!"<<std::endl;
    }

  }

}
