#include <iostream>
#include <string>
#include <utility>
using namespace std;
class Address {
    string city; int pin;
public:
    Address(string c,int p):city(move(c)),pin(p){cout<<"Address constructed\n";}
    ~Address(){cout<<"Address destroyed\n";}
    string str() const{return city+"-"+to_string(pin);}
};
class Course {
    string title;
public:
    explicit Course(string t):title(move(t)){cout<<"Course constructed\n";}
    ~Course(){cout<<"Course destroyed\n";}
    const string& get() const{return title;}
};
class Person {
protected: string name; int age; Address home;
public:
    Person(string n,int a,string city,int pin):name(move(n)),age(a),home(move(city),pin){cout<<"Person constructed\n";}
    virtual ~Person(){cout<<"Person destroyed\n";}
};
class Student:virtual public Person {
    long long regNo; Course course;
public:
    Student(string n,int a,long long r,string city,int pin,string c)
      :Person(n,a,city,pin),regNo(r),course(move(c)){cout<<"Student constructed\n";}
    ~Student() override{cout<<"Student destroyed\n";}
    void print() const{cout<<regNo<<' '<<name<<" ("<<age<<") "<<home.str()<<" | "<<course.get()<<'\n';}
};
class Staff:virtual public Person {
    string department;
public:
    Staff(string n,int a,string city,int pin,string d)
      :Person(move(n),a,move(city),pin),department(move(d)){cout<<"Staff constructed\n";}
    ~Staff() override{cout<<"Staff destroyed\n";}
};
class TeachingAssistant:public Student,public Staff {
public:
    TeachingAssistant(string n,int a,long long r,string city,int pin,string c,string d)
      :Person(n,a,city,pin),Student(n,a,r,city,pin,move(c)),Staff(move(n),a,move(city),pin,move(d)){
        cout<<"TeachingAssistant constructed\n";
    }
    ~TeachingAssistant() override{cout<<"TeachingAssistant destroyed\n";}
};
int main(){
    cout<<"-- Student lifetime --\n";
    {Student s("Kavya",19,192311001,"Salem",636001,"C++");s.print();}
    cout<<"-- Staff lifetime --\n";
    {Staff s("Mohan",42,"Chennai",600001,"IT");}
    cout<<"-- TeachingAssistant lifetime --\n";
    {TeachingAssistant ta("Ravi",25,192311002,"Madurai",625001,"OOP","CSE");}
}