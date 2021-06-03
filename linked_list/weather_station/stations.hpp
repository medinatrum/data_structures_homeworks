#pragma one
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"measurement.hpp"

class Station {
private:
  std::string id_;
  std::string latitude_;
  std::string longitude_;
  std::string elevation_;
  std::string name_;
  std::vector<measurement> measurements;

public:
  Station(const std::string& id, const std::string& latitude, const std::string& longitude, const std::string& elevation, const std::string& name) : id_(id), latitude_(latitude), longitude_(longitude), elevation_(elevation), name_(name) {  }
  
  std::string getName() const { return name_; }
  std::string getID() const { return id_; }

  void addMeasurement(const measurement& mes) {
    measurements.push_back(std::move(mes));
  }

  void printStation() const {
    std::cout << "\nStationID: " << id_ << "\nLatitude: " << latitude_
               << "\nLongitude: " << longitude_ << "\nElevation: " << elevation_<< std::endl;
  }

void printYear(const std::string& year) const;
void printMonth(const std::string& year, const std::string& month);
void insertData(const std::string& year, const std::string& month, const std::string& t_min, const std::string& t_max);

};

  void Station::printYear(const std::string& year) const {  
    std::vector<measurement> mes;
    for (int i = 1; i < 13; ++i)
      mes.push_back(measurement(i));  
    for (auto el : measurements) {
      if (el.year_ == year) {
        if (el.month_ == "01")
          mes[0] = el;
        else if (el.month_ == "02")
          mes[1] = el;
        else if (el.month_ == "03")
          mes[2] = el;
        else if (el.month_ == "04")
          mes[3] = el;
        else if (el.month_ == "05")
          mes[4] = el;
        else if (el.month_ == "06")
          mes[5] = el;
        else if (el.month_ == "07")
          mes[6] = el;
        else if (el.month_ == "08")
          mes[7] = el;
        else if (el.month_ == "09")
          mes[8] = el;
        else if (el.month_ == "10")
          mes[9] = el;
        else if (el.month_ == "11")
          mes[10] = el;
        else if (el.month_ == "12")
          mes[11] = el;
      }
    }
    std::cout << "Month\tMax temp\tMin temp\n";
    for (auto el : mes)
      el.printMeasurement();
  }

  void Station::printMonth(const std::string& year, const std::string& month) {
    std::cout << "Max temp\tMin temp\n";
    auto it = std::find_if(measurements.begin(), measurements.end(), [=](const measurement& m) {
                             return (m.year_ == year && m.month_ == month); });
    if (it != measurements.end())
      it->printMeasMonth();
    else {
      std::cout << "N/A\tN/A\n";
    }
  }

  void Station::insertData(const std::string& year, const std::string& month, const std::string& t_min, const std::string& t_max) {
    auto it = find_if(measurements.begin(), measurements.end(), [=](const measurement& m) {
                        return (m.year_ == year && m.month_ == month);
                      });
    if (it != measurements.end()) {
      it->t_min_ = t_min;
      it->t_max_ = t_max;//ako  postoji prebrisi postojece vrijednosti a ako ne postoji dodaj 
    } else
      measurements.push_back(measurement(year, month, t_max, t_min));
  }


