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
  int status; //����������/������������ 1/0
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
  double engpow; //�������� ��������� HP horsepower
  double engintake; //����������� ��������� ������/�� l/km
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
  double current_fuel; //������� ��ڸ� ������� ����� l;
public:
  double tankcapacity; //��ڸ� ���� ����� l
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
  double speed; //�������� ��/�
  double time;    //����� ����
  int damaged_wheels = 0;
  double mileage; //������ km
  double nrefuel; //���������� ����������
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
    ptr_wheel = new Wheel[wheels];
    for (int i = 0; i < wheels; i++) {
      ptr_wheel[i] = Wheel();
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
  double get_Time()
  {
      return time;
  };
  double get_NRefuel()
  {
      return nrefuel;
  };
 double get_speed()
  {
     return speed;
  };
  void calculateRefuel(double raceLength);
  void time_display();
  int getNwheels()
  {
       return nwheels;
  }
  void number_of_damaged_wheels();
  void output();
  friend Vehicle *RatingResults(int qty);
  friend void outputResults(Vehicle *&car,int qty);
  friend ostream &operator<<(ostream &stream, const Vehicle &obj)
  {
    return stream << "Number of wheels: " << obj.nwheels << ";\n"
                  << "Damaged wheels: " << obj.damaged_wheels << ";\n"
                  << "Speed: " << obj.speed << " km/h;\n"
                  << "Mileage: " << obj.mileage << " km;\n"
                  << "fuel capacity: " << obj.tankcapacity << "l;\n"
                  << "current fuel: " << obj.current_fuel << "l\n"
                  << "engine power: " << obj.engpow << " HP;\n"
                  << "engine intake: " << obj.engintake << " l/100km;" << endl;
  }
};

int menu(int &flag);
void clean(int var = 1);
void create_Vehicle(Vehicle *&adres, int &qty, Vehicle cars);






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
      string Vehicle_name = "";
      cout << "\nName of the car: ";
      cin >> Vehicle_name;
      int Nwheels = 0;
      cout << "Number of wheels: ";
      nwheels = InputProve(nwheels);

      Vehicle cars(Vehicle_name, nwheels);
      clean();
      create_Vehicle(adres, qty, cars);
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

void clean(int var)
{
  for (int i = 0; i < 3; i = i + 1)
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
  cout << "4 for route calculation\n"; //������ ����������� ������
  if (rez == 1)
    cout << "5 for results of last race\n";
  int choice = 0;
  choice = InputProve(choice);
  if (choice == 4)
    {
    rez = 1;
    }
  return choice;
}


void create_vehicle(vehicle *&adres, int &qty, vehicle cars)
{
  Vehicle *tempArray;
  if (adres != nullptr)
    {
    tempArray = new Vehicle[qty + 1];
    for (int i = 0; i < qty; i++) {
      tempArray[i] = adres[i];
    }
    delete[] adres;
    } else
  {
    tempArray = new vehicle[1];
  }
  tempArray[qty] = cars;
  adres = tempArray;
  qty++;
}


Vehicle *RatingResults(vehicle *&adres, int qty)
{
  Vehicle *results = new Vehicle[qty];
  Vehicle *rez_copy = new Vehicle[1];
  for (int i = 0; i < qty; i++) {
    results[i] = adres[i];
  }
  for (int i = 0; i < qty; i++) {
    for (int j = 0; j < qty; j++) {
      if ((results[i].get_Time()- results[j].get_Time() < 0) &&
          (results[i].get_NRefuel() - results[i].get_NRefuel() <= 0)) {
        rez_copy[0] = results[i];
        results[i] = results[j];
        results[j] = rez_copy[0];
      }
    }
  }
  delete[] rez_copy;
  return results;
}


void outputResults(vehicle *&adres, int qty)
{
  Vehicle *results = RatingResults(adres,qty);
  for (int i = 0; i < qty; i++)
  {
    cout << results[i].name << endl;
    results[i].time_display();
    cout << "Refuel times: " << int(results[i].NRefuel) << endl;
  }
  delete[] results;
}

double InputProve(double var)
{
  cin >> var;
  if (cin.fail() || var <= 0)
  {
    while (!(cin >> var) || var <= 0)
    {
      cout << "Uncorrect, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}

int InputProve(int var)
{
  cin >> var;
  if (cin.fail() || var < 0)
  {
    while (!(cin >> var) || var < 0)
    {
      cout << "Uncorrect, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}


int Wheel::check_status(double mileage, double speed)
{
  double ratio = (1/(mileage*sqrt(speed)));
  if (ratio>=0.5)
  {
    //cout<< "Wheel is not damaged"<<endl;
    return 0;
  }
  else
  {
    //cout<<"Wheel is damaged"<<endl;
    return 1;
  }
}


/*
  int wheel::check_status(double mileage, double time) {
    int ratio = int(mileage / time);
    //cout<<"TIME"<<time<<endl;
    //cout<<"Ratio"<<ratio<<endl;
    int damageProb = (rand() % (ratio+1))+1;
    //cout<<"DAMAGE"<<damageProb<<endl;
    // cout << "CHECKING STATUS OF WHEELS..." << endl;
    if (damageProb > (ratio / 2))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }*/


  void Wheel ::output()
  {
  if (status == 1)
  {
    cout << "damaged" << endl;
  }
  else
  {
    cout << "not damaged" << endl;
  }
}


void Engine ::output()
{
  cout << "engine power: " << engpow << " HP;" << endl;
  cout << "engine intake: " << engIntake << " l/100km;" << endl;
}

void Engine::def_engine(double power)
{
  cout << "Engine power in HP: ";
  power = inputprove(power);
  engpow = power;
  engintake = calculateIntake();
}


void Fuel_system ::calculate_cur_fuel(double engintake, double mileage,double nrefuel)
{ //������ �������� ��ڸ�� �������
  if (nrefuel == 0) {
    current_fuel=double(tankcapacity - ((engintake / 100) * mileage));
  } else {
    current_fuel=(((nrefuel)*tankcapacity) - ((engIntake / 100) * mileage));
  }
}


void Fuel_system ::def_fuel_system(double capacity, double engIntake,double mileage)
{
  cout << "fuel capacity: ";
  capacity = inputprove(capacity);
  tankcapacity = capacity;
  current_fuel = capacity;
}

void Fuel_system ::output()
{
  cout << "fuel capacity: " << TankCapacity << "l" << endl;
  cout << "current fuel: " << current_fuel << "l" << endl;
}

void Vehicle::output()
{
  cout << "Number of wheels: " << nwheels << ";\n"
       << "Damaged wheels: " << damaged_wheels << ";\n"
       << "speed: " << speed << " km/h;\n"
       << "mileage: " << mileage << " km;" << endl;
  engine::output();
  fuel_system::output();
}

void Vehicle ::time_display()
{
  double t = this->time;
  int hours = int(t);
  double cur_time = (t - hours) * 60;
  int minutes = int(cur_time);
  int seconds = int((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}

void Vehicle ::calculateSpeed()
{
  if (damaged_wheels == 0) {
speed= double(fabs(sqrt(engpow) * (70.0 / double(nwheels) - 2.5) * (current_fuel / 100.0)));
 }
 else
 {
   speed = (fabs(sqrt(engpow) * (70.0 / double(nwheels) - 2.5) * (current_fuel / 100.0))/(pow(2., double(damaged_wheels))));
     }
  }


  void Vehicle ::number_of_damaged_wheels()
  {
  int count = 0;
  for (int i = 0; i < nwheels; i++)
  {
    if (ptr_wheel[i].get_status() == 1)
    {
      count++;
    }
  }
  damaged_wheels = count;
}

void Vehicle ::calculateRefuel(double raceLength)
{
  double refuel = (raceLength * (engintake / 100)) / tankcapacity;
  if (refuel > 1)
    this->nrefuel= ceil(refuel);
  else
    this->nrefuel= floor(refuel);
}
