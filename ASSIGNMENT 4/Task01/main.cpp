#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class Staff {
    string name_; int id_; double basic_;
protected:
    static constexpr double DA_RATE=0.42;
    double basicWithDA() const { return basic_*(1+DA_RATE); }
public:
    Staff(string n,int id,double b):name_(move(n)),id_(id),basic_(b) {
        if(b<0) throw invalid_argument("negative basic pay");
    }
    virtual ~Staff()=default;
    virtual double pay() const=0;
    virtual string category() const=0;
    void display() const { cout<<category()<<" | "<<name_<<" | "<<id_<<" | Rs "<<pay()<<'\n'; }
};
class Professor final:public Staff {
    double research;
public:
    Professor(string n,int i,double b,double r):Staff(move(n),i,b),research(r) {
        if(r<0) throw invalid_argument("negative research allowance");
    }
    double pay() const override { return basicWithDA()+research; }
    string category() const override { return "Professor"; }
};
class LabAssistant final:public Staff {
public:
    using Staff::Staff;
    double pay() const override { return basicWithDA(); }
    string category() const override { return "Lab Assistant"; }
};
class GuestFaculty final:public Staff {
    double hours,rate;
public:
    GuestFaculty(string n,int i,double h,double r):Staff(move(n),i,0),hours(h),rate(r) {
        if(h<0||r<0) throw invalid_argument("invalid hours or rate");
    }
    double pay() const override { return hours*rate; }
    string category() const override { return "Guest Faculty"; }
};
int main() {
    vector<unique_ptr<Staff>> payroll;
    payroll.push_back(make_unique<Professor>("Anita",101,50000,8000));
    payroll.push_back(make_unique<LabAssistant>("Bala",102,30000));
    payroll.push_back(make_unique<GuestFaculty>("Charan",103,40,900));
    double total=0;
    for(const auto& s:payroll) { s->display(); total+=s->pay(); }
    cout<<"Total payroll: Rs "<<total<<'\n';
}