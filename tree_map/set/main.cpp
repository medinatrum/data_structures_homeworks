#include<iostream>
#include "BazaStudenata.hpp"
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <iterator>

using namespace std;

//std::set<Student>::iterator it;
std::pair<std::set<Student>::iterator, bool> result;

int main()
{
  set<Student> studenti;
  int izbor;

  while(izbor){
    Menu();
    cin>>izbor;
    switch (izbor){
      case 1 :
        unosStudenta(studenti);
        break;
      case 2 :
        if(studenti.empty()) { cout<<"Baza studenata je prazna!"<<endl;
          break; }
        cout<<"Unesite index studenta kojeg zelite obrisati: ";
        int index;
        cin>>index;
        brisanjeStudenta(studenti, index);
        break;
      case 3:
        ispisiSveStudente(studenti);
        break;
      case 4:
        if(studenti.empty()) { cout<<"Baza studenata je prazna!"<<endl;
          break; }

        cout<<"1. Pretraga studenta po broju indexa \n2. Pretraga studenta po imenu i prezimenu"<<endl;
        int izbor;
        cin>>izbor;
        if(izbor == 1){
          int index;
          cout<<"Unesite broj indexa: ";
          cin>>index;
          ispisiStudenta(index, studenti);

        }else if(izbor == 2){
          cout<<"Unesite ime i prezime: ";
          cin.clear();
          cin.ignore();
          string ime_prezime;
          getline(cin, ime_prezime);
          ispisiStudenta(ime_prezime, studenti);

        }else 
          cout<<"Pogrešan unos."<<endl;
        break;
      default:
        return 0;
        break;

    }

  }

}
