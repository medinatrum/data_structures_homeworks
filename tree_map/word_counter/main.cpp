#include<iostream>
#include <map>
#include <fstream> 
#include "words_counting.hpp"
using namespace std;

int main(){
  map<string, vector<int>> map_of_words_with_positions;
  vector<string> all_words = loadWords("story.txt");

  ifstream file ("story.txt");
  if(!file.good()){
    cerr<<"File not found!"<<endl;

  }

  string word;
  vector<string>words;
  vector<int>positions;

  while(file >> word){
    if(alreadyCounted(words, word))
      continue;
    else{
      positions = getPositions(all_words, word);
      map_of_words_with_positions.insert(make_pair(word, positions));
      words.push_back(word);

    }

  }

  for(auto it = map_of_words_with_positions.begin(); it != map_of_words_with_positions.end(); ++it){
    cout<<"Rijec je "<< it->first <<" i nalazi se na sljedecim pozicijama:"<<endl;
    for(int x : it->second)
      cout<<x<<"\t";
    cout<<endl;

  }

  file.close();

  return 0;


}
