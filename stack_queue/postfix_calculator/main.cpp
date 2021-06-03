#include "PostfixCalc.hpp"
#include<iostream>

using namespace std;
int main(){

cout<<"Welcome to RPN calculator. Please enter values and after this operator:"<<endl;
cout<<"(or CTRL+C for end!)"<<endl;

    PostfixCalc calculator;
    calculator.readIn(std::cin);

return 0;
}
