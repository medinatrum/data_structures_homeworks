#include<iostream>
#include "circular_buffer_queue.hpp"

using namespace std;

int main(){
  buffer<int> prvi;
  prvi.push(5).push(6).push(7).push(8);

std::cout<<"Nakon dodavanja 5, 6, 7, 8: "<<std::endl;
prvi.print();
std::cout<<prvi.front()<<" je prvi element."<<endl;
cout<<prvi.back()<<" je posljednji element."<<endl;
auto uklonjen=prvi.pop();
cout<<"Uklanjamo prvi element: "<<uklonjen<<endl;
prvi.print();

cout<<"Testiranje copy konstruktora: (buffer drugi=prvi) "<<std::endl;
buffer<int> drugi=prvi;
std::cout<<"Drugi: \n";
drugi.print();
cout<<"Drugi red nakon dodavanja 10 i 20 "<<endl;
drugi.push(10);
drugi.push(20);
drugi.print();

cout<<"Copy operator = "<<endl;
cout<<"Prvi=drugi"<<endl;
prvi=drugi;
cout<<"Prvi: \n";
prvi.print();
cout<<"velicina prvog reda je sada "<<prvi.size()<<",  a kapacitet zbog default konstrukcije "<<prvi.capacity()<<endl;

cout<<"Pravimo novi red čiji kapacitet sami određujemo. \n";
buffer<char> novi(50);
cout<<"Ispisujemo novi red čiji je kapacitet: "<<novi.capacity()<<endl;
novi.print();

cout<<"Testiranje move konstruktora: \n(Treci=std::move(drugi)"<<endl;
buffer<int> treci=std::move(drugi);
cout<<"Treci:\n";
treci.print();
cout<<"Drugi nakon move: "<<endl;
drugi.print();

cout<<"Move operator = \n(treci = buffer<int>(10);) \nSadržaj trećeg u koji nisu dodani elementi: "<<endl;
treci=buffer<int>(10);
treci.print();

    return 0;
}
