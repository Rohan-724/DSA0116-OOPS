#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
using namespace std;
class Vehicle {
    string registration; double dailyRate; bool rented=false;
public:
    Vehicle(string r,double rate):registration(move(r)),dailyRate(rate){
        if(rate<0)throw invalid_argument("negative daily rate");
    }
    virtual ~Vehicle()=default;
    const string& regNo()const{return registration;}
    bool isRented()const{return rented;}
    virtual string type()const=0;
    virtual double rentalCharge(int days)const=0;
    void rent(){if(rented)throw logic_error("already rented");rented=true;}
    double returnVehicle(int lateDays){
        if(!rented)throw logic_error("not rented");
        if(lateDays<0)throw invalid_argument("negative late days");
        rented=false;return lateDays*lateFeePerDay();
    }
    virtual double lateFeePerDay()const{return dailyRate*0.5;}
protected:
    double daily()const{return dailyRate;}
};
class Bicycle:public Vehicle{
public:using Vehicle::Vehicle;
    string type()const override{return "Bicycle";}
    double rentalCharge(int d)const override{return daily()*d;}
};
class MotorVehicle:public Vehicle{
    double fuelLevel;string serviceDue;
public:
    MotorVehicle(string r,double rate,double fuel,string due)
      :Vehicle(move(r),rate),fuelLevel(fuel),serviceDue(move(due)){}
    double fuel()const{return fuelLevel;}
    const string& serviceDate()const{return serviceDue;}
};
class TwoWheeler:public MotorVehicle{
public:using MotorVehicle::MotorVehicle;
    string type()const override{return "Two-wheeler";}
    double rentalCharge(int d)const override{return daily()*d;}
};
class Car:public MotorVehicle{
    int seats;
public:
    Car(string r,double rate,double fuel,string due,int count)
      :MotorVehicle(move(r),rate,fuel,move(due)),seats(count){
        if(count<1)throw invalid_argument("invalid seat capacity");
    }
    string type()const override{return "Car";}
    double rentalCharge(int d)const override{return daily()*d;}
    int seatingCapacity()const{return seats;}
};
class ElectricCar:public Vehicle{
    double batteryKWh,kWhRate;string serviceDue;
public:
    ElectricCar(string r,double rate,double battery,double unitRate,string due)
      :Vehicle(move(r),rate),batteryKWh(battery),kWhRate(unitRate),serviceDue(move(due)){}
    string type()const override{return "Electric car";}
    double rentalCharge(int d)const override{return daily()*d+batteryKWh*kWhRate;}
};
class ElectricBus:public Vehicle{
    int seats;double batteryKWh,kWhRate;
public:
    ElectricBus(string r,double rate,int count,double battery,double unitRate)
      :Vehicle(move(r),rate),seats(count),batteryKWh(battery),kWhRate(unitRate){}
    string type()const override{return "Electric bus";}
    double rentalCharge(int d)const override{return daily()*d+batteryKWh*kWhRate;}
};
class Fleet{
    vector<unique_ptr<Vehicle>> vehicles;
public:
    template<class T,class... A>T& add(A&&... a){
        auto p=make_unique<T>(forward<A>(a)...);T& ref=*p;
        vehicles.push_back(move(p));return ref;
    }
    void list()const{
        for(const auto& v:vehicles)cout<<v->type()<<" | "<<v->regNo()
          <<" | "<<(v->isRented()?"rented":"available")<<'\n';
    }
    void demo(){
        for(const auto& v:vehicles){
            v->rent();
            cout<<v->type()<<" "<<v->regNo()<<" two-day charge Rs "<<v->rentalCharge(2)<<'\n';
            cout<<"Late fee Rs "<<v->returnVehicle(1)<<'\n';
        }
    }
};
int main(){
    Fleet f;
    f.add<Bicycle>("BI-101",100);
    f.add<TwoWheeler>("TW-202",250,70,"2026-12-15");
    f.add<Car>("CA-303",1200,45,"2026-12-20",5);
    f.add<ElectricCar>("EV-404",1500,45,8,"2026-12-22");
    f.add<ElectricBus>("EB-505",4000,250,180,7);
    cout<<fixed<<setprecision(2);
    f.list();cout<<"-- Rentals and returns --\n";f.demo();
    cout<<"-- Fleet after returns --\n";f.list();
}