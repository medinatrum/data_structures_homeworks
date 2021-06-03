#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

struct measurement {
  std::string year_;  
  std::string month_;
  std::string t_max_{"N/A"};
  std::string t_min_{"N/A"};
  measurement(const std::string& year, const std::string& month, const std::string& t_max, const std::string& t_min)
      : year_(year), month_(month), t_max_(t_max), t_min_(t_min) {  }

  measurement(const int& month) : month_(std::to_string(month)) {  }
  measurement(const std::string&);

void printMeasurement() const;
void printMeasMonth() const;
};

measurement::measurement(const std::string& line) {   //u stationsystem 
    std::istringstream istring(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(istring, token,',')) { 
      tokens.push_back(token);
    }
  try {
      year_ = tokens.at(1).substr(0, 4);
      month_ = tokens.at(1).substr(5, 7);
      if (tokens.at(2) == " ")
        t_max_ = "N/A";
      else
        t_max_ = tokens.at(2);
      if (tokens.at(3) == " ")
        t_min_ = "N/A";
      else
        t_min_ = tokens.at(3);
    } catch (...) {
      if (t_max_ == " ")
        t_max_ = "N/A";
      if (t_min_ == "")
        t_min_ = "N/A";
    }
  }


std::string toMonth(const std::string& num) {
  if (num == "01")
    return "Jan";
  else if (num == "02")
    return "Feb";
  else if (num == "03")
    return "Mar";
  else if (num == "04")
    return "Apr";
  else if (num == "05")
    return "May";
  else if (num == "06")
    return "Jun";
  else if (num == "07")
    return "Jul";
  else if (num == "08")
    return "Aug";
  else if (num == "09")
    return "Sep";
  else if (num == "10")
    return "Oct";
  else if (num == "11")
    return "Num";
  else
    return "Dec";
}
 void measurement::printMeasurement() const {
    std::cout << toMonth(month_) << "\t" << t_max_ << "\t\t" << t_min_ << "\n";
  }

void measurement::printMeasMonth() const {
    std::cout << t_max_ << "\t\t" << t_min_ << "\n";
  }

