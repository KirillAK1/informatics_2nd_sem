#include <iostream>
#include <string>
#include <limits>
#include "cmath"
using namespace std;
double InputProve(double var);
int InputProve(int var);
int qty = 0;
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
    double CalculateRefuel(double raceLength)
        {
            double nrefuel = ((mileage*(engintake/100))/tankcapacity);
            if(nrefuel>1)
                return ceil(nrefuel);
            else
                return floor(nrefuel);
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

    Vehicle()
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
        cout << "\nThe car has been created" << endl;}

     ~Vehicle()
     {
          cout << "Destruction of " << name << endl;
     }
 void output();
  void time_display();
};


void clean(int var =1);
int menu(int &flag);
void create_vehicle(Vehicle *&adres, int &qty, Vehicle cars);
Vehicle *RatingResults(Vehicle *&adres, int qty);
void outputResults(Vehicle *&adres, int qty);

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
    switch (choice){
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
      double tank = 0;
      double power = 0;
      int Nwheels = 0;
      Vehicle cars(vehicle_name, tank, power, Nwheels);
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
          adres[i].time = adres[i].CalculateRaceTime(trackLen);
          adres[i].mileage = trackLen;
          adres[i].nrefuel = adres[i].CalculateRefuel(trackLen);
        }
      }
      break;
    }

    case (5):
    {
      clean();
      outputResults(*&adres, qty);
      break;
    }
    default:
      clean();
      break;
    }
 delete[] adres;
      break;
    }

    }
    return 0;
}




    void clean(int var)
    {
        for (int i = 0; i < 8; i = i + 1)
        {
            cout << "\n";
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

void create_vehicle(Vehicle *&adres, int &qty, Vehicle cars)
{
  Vehicle *tempArray;
  if (adres != nullptr)
    {
    tempArray = new Vehicle[qty + 1];
    for (int i = 0; i < qty; i++)
    {
      tempArray[i] = adres[i];
    }
    delete[] adres;
  }
   else
    {
    tempArray = new Vehicle[1];
    }
  tempArray[qty] = cars;
  adres = tempArray;
  qty++;
}

Vehicle *RatingResults(Vehicle *&adres, int qty)
{
  Vehicle *results = new Vehicle[qty];
  Vehicle *rez_copy = new Vehicle[1];
  for (int i = 0; i < qty; i++) {
    results[i] = adres[i];
  }
  for (int i = 0; i < qty; i++) {
    for (int j = 0; j < qty; j++) {
      if ((results[i].time - results[j].time < 0) &&
          (results[i].nrefuel - results[i].nrefuel <= 0)) {
        rez_copy[0] = results[i];
        results[i] = results[j];
        results[j] = rez_copy[0];
      }
    }
  }
  delete[] rez_copy;
  return results;
}

void outputResults(Vehicle *&adres, int qty) {
  Vehicle *results = RatingResults(adres, qty);
  for (int i = 0; i < qty; i++) {
    cout << results[i].name << endl;
    results[i].time_display();
    cout << "Refuel times: " << int(ceil(results[i].nrefuel)) << endl;
  }
  delete[] results;
}

void Vehicle::output() {
  cout << "Number of wheels: " << nwheels << ";\n"
       << "power of engine: " << engpow << " HP;\n"
       << "speed: " << speed << " km/h;\n"
       << "Engine intake: " << engintake << " l/100km;\n"
       << "mileage: " << mileage << " km;" << endl;
}

double InputProve(double var) {
  cin >> var;
  if (cin.fail() || var <= 0) {
    while (!(cin >> var) || var <= 0) {
      cout << "Uncorrect, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}

int InputProve(int var) {
  cin >> var;
  if (cin.fail() || var < 0) {
    while (!(cin >> var) || var < 0) {
      cout << "Uncorrect, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}
void Vehicle ::time_display() {
  double t = this->time;
  int hours = static_cast<int>(t);
  double cur_time = (t - hours) * 60;
  int minutes = static_cast<int>((cur_time));
  int seconds = static_cast<int>((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}
