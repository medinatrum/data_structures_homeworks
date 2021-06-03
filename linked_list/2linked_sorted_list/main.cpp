#include"sorted_list2.hpp"
#include"ToDoTask.hpp"
#include<iostream>
#include<stdexcept>
using namespace std;

void Menu(){
  cout<<"1.Unesite novi zadatak\n2.Prikaz trenutnih zadataka\n3.Označi zadatak kao završen\n"
    <<"4.Zadaci s najmanjim/najvećim prioritetom\n5.Izlaz\n"<<endl;
 }
int main(){
  int izbor;
  string naslov;
  string opis;
  int prioritet;
  sorted_list<ToDoTask> lista_zadataka;
  ToDoTask zadatak;
  Menu();
  while(cin>>izbor && izbor!=5){
    switch(izbor){
      case 1:{
               cin>>zadatak;
               lista_zadataka.add(std::move(zadatak));
               Menu();
               break;

             }
      case 2:{
               lista_zadataka.print();
               Menu();
               break;
             }
      case 3:{
               int id{};
               cout<<"Unesite ID zadatka kojeg želite obrisati:"<<endl;
               cin>>id;
            auto it=lista_zadataka.find_if([=](const ToDoTask& temp){return temp.getId()==id;});
             //generisati exception u sluaju da je prazna
               lista_zadataka.remove(it);
               Menu();
               break;
               }
      case 4 :{ std::cout << "Obaveze sa najvećim/najmanjim prioritetom su:" << std::endl;
             
               lista_zadataka.print_rang_list();
             }
               Menu();
               break;
             
      case 5:{
               return 0;

             }
      default:
             return 0 ;
    }
  }

return 0;}

