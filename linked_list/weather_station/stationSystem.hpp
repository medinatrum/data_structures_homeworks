#pragma once
#include"stations.hpp"
#include"measurement.hpp"
#include<fstream>
#include<algorithm>
#include<sstream>

class System {
private:
  std::ifstream file_;
  std::vector<Station> stations_;

public:
System(const std::string& file);   
void Menu() ; 
  
}; 

System::System(const std::string& file) {
    file_.open(file);
    std::string input;

    while (getline(file_, input)) {
      std::istringstream istring(input);
      std::string token;
      std::vector<std::string> tokens;
      while (std::getline(istring, token,','))
        tokens.push_back(token);
      std::string station_id = tokens.at(0);
      std::string latitude = tokens.at(1);
      std::string longitude = tokens.at(2);
      std::string elevation = tokens.at(3);
      std::string name = tokens.at(4);
      std::ifstream station;
      station.open(name + ".csv");
      Station tmp_station(station_id, latitude, longitude, elevation, name);
      std::string station_input;

      while (std::getline(station, station_input)) {
        try {
          measurement tmp_mes(station_input);  //kons iz measurements koji uzima std:.string
          tmp_station.addMeasurement(tmp_mes);
        } catch (...) {
          std::cout << station_input << std::endl;
        }
      }
      stations_.push_back(tmp_station);
    }
  }

