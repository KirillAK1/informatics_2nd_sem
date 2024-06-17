#include <iostream>
#include "cmath"
#include <limits>
#include <string>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
using namespace std;
double Refuel_time=0.0003;//примерно 1 секунда
double Change_time=0.008;//примерно 30 секунд
double dt=0.0003;
double InputProve(double var);
int InputProve(int var);
int menu(int &rez);
void clean(int var = 1);


class Wheel
{
  double current_mileage;
  bool status; //ïîâðåæäåíî/íåïîâðåæäåíî 1/0
public:
  bool check_status(double mileage, double speed);
  Wheel()
    {
      status=0;
      current_mileage=0;
    };
virtual ~wheel(){};//требуется для корректной работы компилятора
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
   void set_status(bool status)
   {
    this->status = status;
  }
};


class Engine
{
protected:
  double engpow; //ìîùíîñòü äâèãàòåëÿ HP horsepower
  double engintake; //ïîòðåáëåíèå äâèãàòåëÿ ëèòðîâ/êì l/km
public:
double calculateIntake()
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
  double current_fuel; //òåêóùèé îáÚ¸ì òîïëèâà ëèòðû l;
public:
  double tankcapacity; //îáÚ¸ì áàêà ëèòðû l
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
  double speed; //ñêîðîñòü êì/÷
  double time;    //âðåìÿ ïóòè
  int damaged_wheels;
  double mileage; //ïðîáåã km
  double nrefuel; //êîëè÷åñâòî äîçàïðàâîê
  double current_mileage;//текущее положение на круге km
  int current_circles;
public:
    vector<Wheel> vec_wheels;
    string name;
    double pit_stop_time;
    Vehicle()
    {
    name = "ADDVEHICLE";
    time = current_mileage = mileage = nrefuel = pit_stop_time = 0;
    damaged_wheels=current_circles=0;
    }

     Vehicle(string vehicle_name, int wheels)
     {
    current_mileage = mileage = pit_stop_time = 0;
    damaged_wheels = current_circles = 0;
    name = vehicle_name;
    nwheels = wheels;
    for (int i = 0; i < wheels; i++)
    {
      wheel newWheel;
      vec_wheels.push_back(newWheel);
    }
    def_fuel_system();
    def_engine(0);
    calculateSpeed();
    }

    void calculateSpeed();
  void setMileage(double tracklen) { mileage=tracklen; }

   ~Vehicle()
   {
        cout << "Destruction of " << name << endl;
   }
    void calculateRaceTime(double raceLength)
   {
    time = (raceLength / speed);
   }
    void reset();

     void total_time()
  {
    time=time+pit_stop_time;
  }

  int calc_circles(double trackLen)
  {
    if (current_mileage-trackLen>=0)
    {
      current_circles=int(mileage/trackLen);
      current_mileage=0;
      return 1;
    }
    else {return 0;}
  }

  double wheels_change()
  {
    double time=damaged_wheels*Change_time;
    return time;
  }

  double refuel_time()
  {
    double time=((tankcapacity-current_fuel)*Refuel_time);
    return time;
  }

   double get_Time(){return time;};
  void set_Time(double time){this->time=ime;};
  double get_NRefuel(){return nrefuel;};
  void plus_NRefuel(){nrefuel++;}
  double get_speed(){return speed;};
  int get_damaged_wheels(){return damaged_wheels;};
  double get_mileage(){return mileage;};
  void set_mileage(double len){this->mileage=len;};
  void mileage_plus(){this->mileage+=(speed*dt);};
  double get_current_mileage(){return current_mileage;};
  void set_current_mileage(double len){this->current_mileage=len;};
  void current_mileage_plus(){this->current_mileage+=(speed*dt);};
  int get_current_circles(){return current_circles;};
  void set_current_circles(int circles){this->current_circles=circles;};
  void current_circles_plus(){this->current_circles++;}
  void calculateRefuel(double raceLength,int circles);
  void need_refuel(double tracklen);
  void need_change();
  void time_display();
  int getNwheels() { return nwheels; }
  double get_current_fuel() { return current_fuel; }
  void number_of_damaged_wheels();
  void output();
  friend vehicle *RatingResults(int qty);
  friend void outputResults(vector <vehicle> car,int qty);

   friend ostream &operator<<(ostream &stream, const vehicle &obj) {
    return stream <<"\n"<<"Name: "<<obj.name<<"\n"
      << "Number of wheels: " << obj.Nwheels << ";\n"
                  << "Damaged wheels: " << obj.damaged_wheels << ";\n"
                  << "Speed: " << obj.speed << " km/h;\n"
                  << "Mileage: " << obj.mileage << " km;\n"
                  << "fuel capacity: " << obj.TankCapacity << " l;\n"
                  << "current fuel: " << obj.current_fuel << " l\n"
                  << "engine power: " << obj.engPow << " HP;\n"
                  << "engine intake: " << obj.engIntake << " l/100km;" << endl;
  }


   friend istream &operator >> (istream &stream,Vehicle& obj)
    {
      cout<<"Vehicle name: ";
      stream>>obj.name;
      try
        {
          cout<<"Number of wheels: ";
          stream>>obj.nwheels;
          if (obj.nwheels < 2){
              throw "Uncorrect number of wheels! try again";
        }
        }
        catch (const char* msg) {
          cerr << "Exception caught: " << msg <<endl;
          obj.nwheels=inputprove(obj.nwheels);
        }
        for (int i = 0; i < obj.nwheels; i++) {
          wheel newWheel;
          obj.vec_wheels.push_back(newWheel);
          }
        try
          {
            cout<<"Tank capacity: ";
            stream>>obj.tankcapacity;
            if (obj.tankcapacity<=0){
              throw "Uncorrect tank capacity! try again";
            }
          }
          catch (const char* msg)
          {
            cerr << "Exception caught: " << msg <<endl;
            obj.tankcapacity=inputprove(obj.tankcapacity);
          }
        try
          {
            cout<<"Engine power: ";
            stream>>obj.engpow;
            if (obj.engpow<=0){
              throw "Uncorrect power of engine! try again";
            }
          }
          catch (const char* msg)
          {
            cerr << "Exception caught: " << msg <<endl;
            obj.engpow=inputprove(obj.engpow);
          }
          obj.current_fuel=obj.tankcapacity;
          obj.def_engine(obj.engpow);
          obj.calculateSpeed();
      return stream;
    }

Vehicle& operator=(const Vehicle& other)
{
  name = other.name;
  nwheels = other.nwheels;
  speed = other.speed;
  mileage = other.mileage;
  current_mileage=other.current_mileage;
  current_circles=other.current_circles;
  time=other.time;
  return *this;
}
};


  int allfinished(vector<vehicle> &v,double trackLen,int circles);
  int skip(vector<int> skip_id, int i);

  vector<vehicle>RatingResults(vector<vehicle> v);
  void outputResults(vector<vehicle> v);









