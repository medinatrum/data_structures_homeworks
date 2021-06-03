#include <iostream>
#include "account_linked_list.hpp"
#include<string>

void Menu(){
  std::string stars(50,'*');
  std::cout<<stars<<std::endl;
  std::cout<<"Actions: \n"<<std::string(8, ' ')+"1. New transaction\n"<<std::string(8, ' ')+"2. Apply transaction\n"
    <<std::string(8, ' ')+"3. Pending transaction\n"
    <<std::string(8, ' ')+"4. Discard pending transaction\n"<<std::string(8, ' ')+"5. Ballance\n"
    <<std::string(8, ' ')+"6. Exit\n"<<"Your choice:? \n";

}

int main(){
  Account my_account;
  Transaction pending;
  int choice;
  Menu();
    while(std::cin>>choice && choice!=6)
  {
    switch(choice){
      case 1 : {
                 my_account.addTransaction();
                 Menu();
                 break; 
               }

      case 2 : {
                 my_account.applyTransaction();
                 Menu();
                 break;
               }

      case 3 : {
                 try{
                   my_account.printTransaction();
                 }
                 catch(...){
                   std::cout<<"Transaction not found!\n";
                 }

                 Menu();
                 break;
               }

      case 4 : {
                 try{
                   my_account.discardTransaction();
                 }
                 catch(...){
                   std::cout<<"Transaction not found!\n";
                 }

                 Menu();
                 break;       
               }

      case 5 : {

                 std::cout<<"Ballance on your account: "<<my_account.getBalance()<<std::endl;
                 Menu();
                 break;       
               }

      default :
               std::cout<<"Wrong input!!!\n";
               return 0;
    }
  }

  return 0;

}
