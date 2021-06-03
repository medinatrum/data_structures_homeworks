#include "stationSystem.hpp"

int main(void)
{
  System stanica("stations.csv");
  stanica.Menu();

return 0;
}
  
void PrintMenu() {
    std::cout<< "**************Historical temperature information**************\n";
    std::cout << "\t 1. Get information for entire year\n";
    std::cout << "\t 2. Get information for specific month\n";
    std::cout << "\t 3. Insert new historical temperature information\n\n";
    std::cout << "\t 4. Exit\n";
    std::cout<<"Your choice?: ";

  }

  void System::Menu() {
    int choice;
    PrintMenu();
    while (std::cin >> choice && choice != 4) {
      switch (choice) {
      case 1: {
        std::string location, year;
        std::cout << "Enter a location where station is placed: ";
        std::cin >> location;
        auto it= std::find_if(stations_.begin(), stations_.end(), [=](const Station& s) { 
          return s.getName() == location; });
        if (it!= stations_.end()) {
          it->printStation();
          std::cout << "Enter a year: ";
          std::cin >> year;
          it->printYear(year);
        } else
          std::cout << "Station not found!\n";
        PrintMenu();
        break;
      }
      case 2: {
        std::string location;
        std::cout << "Enter a location where station is placed: ";
        std::cin >> location;
        auto it = std::find_if(
        stations_.begin(), stations_.end(), [=](const Station& s) { 
          return s.getName() == location; });
        if (it!= stations_.end()) {
         it->printStation();
         std::string year, month;
         std::cout << "Enter year: ";
         std::cin >> year;
         std::cout << "Enter month: ";
         std::cin >> month;
          if (std::stoi(month) < 10)
            month = "0" + month;
          it->printMonth(year, month);
        } else
          std::cout << "Station not found!\n";
        PrintMenu();
        break;
      }
      case 3: {
        std::string id, year, month, t_max, t_min;
        std::cout << "Enter ID of a station: ";
        std::cin >> id;
        auto it= std::find_if(stations_.begin(), stations_.end(), [=](const Station& s) { 
          return s.getID() == id; });
        if (it!= stations_.end()) {
          it->printStation();
          std::cout << "Enter  year: ";
          std::cin >> year;
          std::cout << "Enter month: ";
          std::cin >> month;
          if (std::stoi(month) < 10)
            month = "0" + month;
          std::cout << "Enter min temperature: ";
          std::cin >> t_min;
          std::cout << "\n Enter max temperature: ";
          std::cin >> t_max;
          it->insertData(year, month, t_min, t_max);
        } else
          std::cout << "Station not found!\n";
        PrintMenu();
        break;
      }
      default:
        break;
      }
    }
  }


 
