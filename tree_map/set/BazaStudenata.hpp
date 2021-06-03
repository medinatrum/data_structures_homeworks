#pragma once
#include <iostream>
#include <algorithm>
#include <set>
#include <iterator>


class Student{
  private:
    int index_;
    std::string ime_prezime_;
    double prosjOcjena_;

  public:
    Student(int index, std::string ime_prezime) : index_(index), ime_prezime_(ime_prezime), prosjOcjena_(0) {}

    int getIndex() const {
      return index_;

    }

    std::string getStudent() const {
      return ime_prezime_;

    }

    void ispis() const {
      std::cout<<"Ime i prezime studenta: "<<ime_prezime_<<"  Broj index-a:"<<index_<<std::endl;

    }

};

bool operator < (const Student& s1, const Student& s2) { return s1.getIndex() < s2.getIndex() || (s1.getStudent() == s2.getStudent() 
    && s1.getIndex() < s2.getIndex() );  }

using namespace std;
set<Student>::iterator it;

void Menu(){
  cout<<"\n1. Unos studenta \n2. Brisanje studenta \n3. Prikaz svih studenata \n4. Prikaz određenog studenta \n5. Izlaz"<<endl;
  cout<<string(30,'*')<<endl;
  cout<<"Vaš izbor: "; }


  bool postojiStudent(const int& index, set<Student>& setStudenata){   ///find
    bool is_in = false;
    for( it = setStudenata.begin(); it != setStudenata.end(); ++it){
      if(it -> getIndex() == index) {
        is_in=true;
        break;
      } 
    }
    return is_in;
  }

void unosStudenta(set<Student>& setStudenata){
  cout<<"Dodavanje novog studenta: \n Unesite broj index-a: ";
  int index;
  string ime_prezime;
  cin>>index;
  cout<<"Ime i prezime: ";
  std::cin.clear();
  std::cin.ignore();
  getline(cin, ime_prezime);
  Student studentic(index, ime_prezime);

  auto result = setStudenata.insert(studentic);     //ili sa postojiStudent
  if(!result.second) { 
    std::cout<<"Ubacivanje studenta neuspješno, već postoji student sa tim brojem index-a."<<std::endl;
  }
  else{ 
    std::cout<<"Student se sada nalazi u bazi podataka."<<std::endl;
  }

}


void brisanjeStudenta(set<Student>& setStudenata, const int& index){
  if(setStudenata.empty()) { cout<<"Baza studenata je prazna!"<<endl; return; }
  if(postojiStudent(index, setStudenata)){
    auto it = setStudenata.begin();
    for(; it != setStudenata.end(); ++it){
      if(it->getIndex() == index)
        break;
    }

    cout<<"Jeste li sigurni da želite obrisati studenta sa brojem indexa "<<index<<"\nY/N"<<endl;
    char izbor;
    cin>>izbor;
    while(izbor != 'Y' && izbor != 'N'){
      cout<<"Wrong input!!!"<<endl;
      break;
      cin>>izbor;
    }

    if(izbor == 'Y'){
      setStudenata.erase(it);
      cout<<"Student izbrisan.";

    }
    if(izbor == 'N') 
      return;

  }else
    cout<<"Student sa datim brojem index-a ne postoji."<<endl;

}

void ispisiSveStudente(const set<Student>& setStudenata) {
  if(setStudenata.empty()) { cout<<"Baza studenata je prazna!"<<endl; return; }

  for(const Student& s : setStudenata)
    s.ispis();

}

void ispisiStudenta(const int& index, set<Student>& setStudenata){

  for(const Student& s : setStudenata){
    if(s.getIndex() == index){
      s.ispis();
      return;

    }
  } 

  cout<<"Ne postoji student sa datim brojem indexa."<<endl;

}

bool postojiIstoimeni(const string& ime_prez, set<Student> setStudenata) {
  for(Student s : setStudenata){
    if(s.getStudent().compare(ime_prez))  //!s
      return true;

  }

  return false;
}

void ispisiStudenta(const string& ime_prezime, set<Student>& setStudenata){ 
  /* for(set<Student>::iterator it=setStudenata.begin(); it != setStudenata.end(); ++it) { */
  /*   if(it ->getStudent() == ime_prezime) { */
  /*     if(postojiIstoimeni(ime_prezime, setStudenata)) { */
  /*       cout<<"Postoji više studenata sa datim imenom i prezimenom. Molimo unesite broj index-a traženog studenta: "; */
  /*       int index; */
  /*       cin>>index; */
  /*       ispisiStudenta(index, setStudenata); */
  /*     } */
  /*     else { */

  /*     cout<<"Traženi student je: "; */   
  /*     it ->ispis(); */

  /*   } */
  /*   } */

  /*   else {cout<<"Ne postoji student sa datim imenom i prezimenom.\n"; */
  /* } */
  /* } */
  /* } */ 


auto kriterij = [ime_prezime](const Student& s) -> bool { return s.getStudent() == ime_prezime;  };
set<Student>::iterator iter = find_if(setStudenata.begin(), setStudenata.end(), kriterij);
//setStudenata.begin();

while(iter != setStudenata.end()) {
  cout<<"Traženi student je: ";
  iter ->ispis();
  iter = find_if(++iter, setStudenata.end(), kriterij);
}

}
