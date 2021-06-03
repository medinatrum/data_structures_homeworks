#include<iostream>
#include <vector>
#include <fstream> 


std::vector<int> getPositions(const std::vector<std::string>& vs, const std::string& s){
  std::vector<int> positions;
  int counter = 0;
  for(std::string word : vs){
    if(!s.compare(word))
      positions.push_back(counter);
    ++counter;

  }
  return positions;

}

bool alreadyCounted(const std::vector<std::string>& vs, const std::string& s) {
  for(std::string word : vs){
    if(!word.compare(s))
      return true;

  }
  return false;

}

std::vector<std::string> loadWords (const std::string& file_name){
  std::vector<std::string> loaded;
  std::ifstream file(file_name);
  if(!file.good())
    return loaded;

  std::string str;
  while(file >> str)
    loaded.push_back(str);
  file.close();

  return loaded;

}




