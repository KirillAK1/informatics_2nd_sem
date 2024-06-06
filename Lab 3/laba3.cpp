#include "cmath"
#include <iostream>
#include <limits>
#include <string>
#include <ctime>

using namespace std;

int qty = 0;
double InputProve(double var);
int InputProve(int var);

class Wheel
{
  double current_mileage;
  int status; //повреждено/неповреждено 1/0
public:
  int check_status(double mileage, double speed);
  Wheel()
    {
      status=0;
      current_mileage=0;
    };
  double def_wheel(double mileage, double speed)
  {
    current_mileage = mileage;
    status = check_status(mileage,speed);
    return current_mileage;
  }
  virtual void output();
  int get_status()
  {
       return status;
  }
};


class Engine
{
protected:
  double engpow; //мощность двигателя HP horsepower
  double engintake; //потребление двигателя литров/км l/km
public:
 inline double calculateIntake()
 {
     return fabs(pow(engpow, 1 / 3) + sqrt(engpow) - 6.25);
 }
 Engine()
 {
     engintake=0;
     engpow=0;
 };
  void def_engine(double power);
  virtual void output();
};


class Fuel_system
{
protected:
  double current_fuel; //текущий обЪём топлива литры l;
public:
  double tankcapacity; //обЪём бака литры l
  void calculate_cur_fuel(double engintake, double mileage, double NRefuel);
  Fuel_system()
  {
      tankcapacity=0;
      current_fuel=0;
  };
  void def_fuel_system(double capacity, double engintake, double mileage);
  virtual void output();
};


class Vehicle : public Engine, public Fuel_system
{
private:
  int nwheels;
  double speed; //скорость км/ч
  double time;    //время пути
  int damaged_wheels = 0;
  double mileage; //пробег km
  double nrefuel; //количесвто дозаправок
public:
  Wheel *ptr_wheel;
  string name;
  Vehicle() {
    name = "ADDVEHICLE";
    time = mileage = nrefuel = damaged_wheels = 0;
    ptr_wheel = 0;
  }
  Vehicle(string vehicle_name, int wheels) {
    mileage =damaged_wheels = 0;
    setName(vehicle_name);
    setNwheels(wheels);
    ptr_wheel = new wheel[wheels];
    for (int i = 0; i < wheels; i++) {
      ptr_wheel[i] = wheel();
    }
    def_fuel_system(0, engintake, mileage);
    def_engine(0);
    calculateSpeed();
  }
  void calculateSpeed();
  void setName(string vehicle_name) { name = vehicle_name; }
  void setNwheels(int wheels) { nwheels = wheels; }
  void setMileage(double tracklen) { mileage=tracklen; }
  ~Vehicle() { cout << "Destruction of " << name << endl; }
  inline void calculateRaceTime(double raceLength) {
    time = (raceLength / speed);
  };








  int main()
{
    clean();
    Vehicle *adres=nullptr;
    double trackLen = 0;
    int flag = 1;
    int rez = 0;
    while (flag == 1)
    {
    int choice = 10;
    choice = menu(rez);
    if ((choice > 5) || (choice < 0))
    {
      cout << "\nError, try another number!\n";
    }
    switch (choice)
    {
    case (0):
    {
      cout << "Are you sure you want to get out?\n1-yes\n0-go back\n";
      int exit = 2;
      exit = InputProve(exit);
      if (exit == 1)
      {
        flag = 0;
        break;
      }
       else
      {
        clean();
      }
      break;
    }
     case (1):
    {
      clean();
      string vehicle_name = "";
      cout << "\nName of the car: ";
      cin >> vehicle_name;
      int Nwheels = 0;
      cout << "Number of wheels: ";
      Nwheels = InputProve(Nwheels);

      Vehicle cars(vehicle_name, Nwheels);
      clean();
      create_vehicle(adres, qty, cars);
      rez = 0;
      break;
    }
    case (2):
    {
      clean();
      for (int i = 0; i < qty; i++)
      {
        cout << adres[i].name << endl;
        adres[i].output();
        cout << "__OR__" << endl;
        cout << adres[i];
      }
      break;
    }
    case (3):
    {
      clean();
      cout << "Enter the length of the track (km): ";
      trackLen = InputProve(trackLen);
      rez = 0;
      break;
    }
    case (4):
    {
      clean();
      if (trackLen == 0)
      {
        cout << "You haven't entered the length of the track!\n";
        rez = 0;
        break;
      }
      else
      {
        for (int i = 0; i < qty; i++)
        {
          adres[i].calculateRaceTime(trackLen);
          adres[i].setMileage(trackLen);
          for (int j = 0; j < adres[i].getNwheels(); j++)
          {
          adres[i].ptr_wheel[j].def_wheel(trackLen,adres[i].get_speed());
          }
          adres[i].number_of_damaged_wheels();
          adres[i].calculateRefuel(trackLen);
          adres[i].calculate_cur_fuel(adres[i].calculateIntake(), trackLen,adres[i].get_NRefuel());
          adres[i].calculateSpeed();
        }
      }
      break;
    }
    case (5):
    {
      clean();
      outputResults(adres,qty);
      break;
    }
    default:
      clean();
      break;
    }

  }
  return 0;
}







