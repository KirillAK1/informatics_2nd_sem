#include <iostream>
#include <string>
#include "cmath"
using namespace std;
double InputProve(double var);
class Vehicle
{
    double tankcapacity;// объём бака
    double speed; // скорость
    double engintake; // двигатель потребление литр/км
    double engpow; // двигатель мощность в лошадинных силах

public:
    int nwheels; // колёса
    double mileage; //пробег
    double time; // время в пути в часах
    string name;
    double nrefuel; //количество дозаправок на путь
    double CalculateIntake()
        {
            return pow(engpow,1/3)+sqrt(engpow)-6.25;
        }
    double CalculateSpeed()
        {
            return sqrt(engpow)*(70/nwheels-2.5);
        }
    double CalculateRaceTime(double race)
        {
            return (race/speed);
        }
    double CalculateRefuel()
        {
            return ((mileage*(engintake/100))/tankcapacity);
        }
    void setTankcapacity(double tank)
        {
            tankcapacity = tank;
        }
    void setEngpow(double power)
        {
            engpow = power;
        }
    void setName (string vehicle_name)
        {
            name = vehicle_name;
        }
    void setNwheels (int wheels)
        {
            nwheels = wheels;
        }

    Vehicle ()
    {
         name="";
         tankcapacity=0;
         speed=0;
         engintake=0;
         nwheels=0;
         mileage=0;
         engpow=0;
         time=0;
         nrefuel=0;
    }

    Vehicle(string vehicle_name, double tank, double power, int wheels)
    {
        mileage = time = nrefuel = 0;
        cout << "\nEnter name of vehicle: ";
        cin >> vehicle_name;
        setName(vehicle_name);
        cout << "\nEnter number of wheels: ";
        cin >> wheels;
        setNwheels (wheels);
        cout << "Power of the engine:";
        power = InputProve(power);
        setEngpow(power);
        cout << "\nEnter tank capacity: ";
        cin >> tank;
        setTankcapacity (tank);
        speed = CalculateSpeed();
        engintake = CalculateIntake();
        cout << "\nThe car has been created" << endl;
    }

    ~vehicle()
    {
        cout << "Destruction of "<<name<<endl;
    }

};


void clean(int var =1);
int menu(int &flag);
void create_vehicle(Vehicle *&adres, int &qty, Vehicle cars);
vehicle *RatingResults(Vehicle *&adres, int qty);
void outputResults(Vehicle *&adres, int qty);

int main()
{
    clean();
    Vehicle *adres=nullptr;
    double trackLen = 0;
    int flag = 1;
    int rez = 0;
    while (flag == 1) {
    int choice = 10;
    choice = menu(rez);
    if ((choice > 5) || (choice < 0)) {
      cout << "\nError, try another number!\n";
    }
    switch (choice) {
    case (0): {
      cout << "Are you sure you want to get out?\n1-yes\n0-go back\n";
      int exit = 2;
      exit = InputProve(exit);
      if (exit == 1) {
        flag = 0;
        break;
      } else {
        clean();
      }
      break;
    }
      delete[] adres;
      break;



    return 0;
}

void clean(int var)
{
    for(int i=0; i<100; i=i+1)
    {
        cout<<"\n";
    }
}

int menu(int &rez)
{
  cout << "\nInter a number to choose action:\n";
  cout << "0 for exit\n";
  cout << "1 for adding Vehicle\n";
  cout << "2 for output information about Vehicle\n";
  cout << "3 to enter length of the track\n";
  cout << "4 for route calculation\n"; //расчет прохождения трассы
  if (rez == 1)
    cout << "5 for results of last race\n";
  int choice = 0;
  choice = InputProve(choice);
  if (choice == 4) {
    rez = 1;
  }
  return choice;
}

