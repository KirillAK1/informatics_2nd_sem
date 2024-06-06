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
  wheel()
    {
      status=0;current_mileage=0;
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
  double engPow; //мощность двигателя HP horsepower
  double engIntake; //потребление двигателя литров/км l/km
public:
 inline double calculateIntake()
 {
     return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25);
 }
 engine(){engIntake=0;engPow=0;};
  void def_engine(double power);
  virtual void output();
};


class Fuel_system
{
protected:
  double current_fuel; //текущий обЪём топлива литры l;
public:
  double TankCapacity; //обЪём бака литры l
  void calculate_cur_fuel(double engIntake, double mileage, double NRefuel);
  fuel_system(){TankCapacity=0;current_fuel=0;};
  void def_fuel_system(double capacity, double engIntake, double mileage);
  virtual void output();
};


class vehicle : public engine, public fuel_system {
private:
  int Nwheels;
  double speed; //скорость км/ч km/h
  double Time;    //время пути hour
  int damaged_wheels = 0;
  double mileage; //пробег km
  double NRefuel; //количесвто дозаправок
public:
  wheel *ptr_wheel;
  string name;
  vehicle() {
    name = "ADDVEHICLE";
    Time = mileage = NRefuel = damaged_wheels = 0;
    ptr_wheel = 0;
  }
  vehicle(string vehicle_name, int wheels) {
    mileage =damaged_wheels = 0;
    setName(vehicle_name);
    setNwheels(wheels);
    ptr_wheel = new wheel[wheels];
    for (int i = 0; i < wheels; i++) {
      ptr_wheel[i] = wheel();
    }
    def_fuel_system(0, engIntake, mileage);
    def_engine(0);
    calculateSpeed();
  }
  void calculateSpeed();
  void setName(string vehicle_name) { name = vehicle_name; }
  void setNwheels(int wheels) { Nwheels = wheels; }
  void setMileage(double tracklen) { mileage=tracklen; }
  ~vehicle() { cout << "Destruction of " << name << endl; }
  inline void calculateRaceTime(double raceLength) {
    Time = (raceLength / speed);
  };






