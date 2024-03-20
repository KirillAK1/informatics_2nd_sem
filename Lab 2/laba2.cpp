#include <iostream>
#include <string>
#include "cmath"
using namespace std;
class Vehicle
{
    double tankcapacity;
    double speed;
    double engintake;

public:
    int nwheels;
    double mileage;
    double engpow;
    double time;
    string name;
    double nrefuel;
    double CalculateIntake(){return pow(engpow,1/3)+sqrt(engpow)-6.25;}
    double CalculateSpeed(){return sqrt(engpow)*(70/nwheels-2.5);}
    double CalculateRaceTime(double race){return (race/speed);}
    double CalculateRefuel(){return ((mileage*(engintake/100))/tankcapacity);}
    vehicle ()
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
    ~vehicle()
    {
        cout<<"Destruction of "<<name<<endl;
    }

};


void clean(int var =1);

int main()
{

    return 0;
}

void clean(int var)
{
    for(int i=0; i<100; i=i+1)
    {
        cout<<"\n";
    }
}
