#include <iostream>
#include <string>
#include <utility>
using namespace std;
class Person {
protected: string name; int id; string phone;
public:
    Person(string n,int i,string p):name(move(n)),id(i),phone(move(p)){}
    virtual ~Person()=default;
    void printPerson() const { cout<<name<<" #"<<id<<" "<<phone; }
};
class Student:virtual public Person {
protected: string programme; double cgpa;
public:
    Student(string n,int i,string p,string prog,double g)
      :Person(move(n),i,move(p)),programme(move(prog)),cgpa(g){}
};
class Staff:virtual public Person {
protected: string department; double salary;
public:
    Staff(string n,int i,string p,string d,double s)
      :Person(move(n),i,move(p)),department(move(d)),salary(s){}
};
class TeachingAssistant:public Student,public Staff {
public:
    TeachingAssistant(string n,int i,string p,string prog,double g,string dept,double s)
      :Person(n,i,p),Student(n,i,p,move(prog),g),Staff(move(n),i,move(p),move(dept),s){}
    void display() const {
        printPerson(); cout<<" | "<<programme<<" CGPA "<<cgpa
        <<" | "<<department<<" salary "<<salary<<'\n';
    }
};
class ResearchScholar:public Student {
    double fellowship;
public:
    ResearchScholar(string n,int i,string p,string prog,double g,double f)
      :Person(n,i,p),Student(move(n),i,move(p),move(prog),g),fellowship(f){}
    void display() const {
        printPerson(); cout<<" | "<<programme<<" CGPA "<<cgpa
        <<" | fellowship Rs "<<fellowship<<'\n';
    }
};
int main() {
    TeachingAssistant ta("Kavya",201,"9000000001","CSE",8.7,"Computing",25000);
    ResearchScholar rs("Arun",202,"9000000002","ECE",9.1,18000);
    ta.display(); rs.display();
}