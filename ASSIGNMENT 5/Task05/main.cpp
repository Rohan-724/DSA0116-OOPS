#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class Bill {
    string patient;
protected:
    explicit Bill(string p):patient(move(p)){if(patient.empty())throw invalid_argument("patient required");}
public:
    virtual ~Bill() noexcept=default;
    virtual string type()const=0;
    virtual double total()const=0;
    const string& patientName()const noexcept{return patient;}
};
class OutPatient:public Bill {
    double consult,tests;
public:
    OutPatient(string p,double c,double t):Bill(move(p)),consult(c),tests(t){if(c<0||t<0)throw invalid_argument("negative charge");}
    string type()const override{return "OP";}
    double total()const override{return consult+tests;}
};
class InPatient:public Bill {
    int days;double rate,procedure;
public:
    InPatient(string p,int d,double r,double s):Bill(move(p)),days(d),rate(r),procedure(s){if(d<0||r<0||s<0)throw invalid_argument("negative charge");}
    string type()const override{return "IP";}
    double total()const override{return days*rate+procedure;}
};
// New bill extension, no modification to existing bill classes.
class MaternityBill:public Bill {
    double package,extras;
public:
    MaternityBill(string p,double pkg,double e):Bill(move(p)),package(pkg),extras(e){if(pkg<0||e<0)throw invalid_argument("negative maternity charge");}
    string type()const override{return "MATERNITY";}
    double total()const override{return package+extras;}
};
class Payer {
public:virtual ~Payer()noexcept=default;virtual string name()const=0;virtual double amountCovered(const Bill&)const=0;
};
class SelfPay:public Payer {
public:string name()const override{return "SelfPay";}double amountCovered(const Bill& b)const override{return b.total();}
};
class Insurance:public Payer {
    double limit;
public:explicit Insurance(double l):limit(l){if(l<0)throw invalid_argument("negative cover");}
    string name()const override{return "Insurance";}double amountCovered(const Bill& b)const override{return min(limit,b.total());}
};
// New payer extension, no modification to existing payer classes.
class EmployerScheme:public Payer {
    double percent;
public:explicit EmployerScheme(double p):percent(p){if(p<0||p>100)throw invalid_argument("invalid percent");}
    string name()const override{return "EmployerScheme";}
    double amountCovered(const Bill& b)const override{return b.total()*percent/100.0;}
};
int main(){
    cout<<fixed<<setprecision(2);
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
    bills.push_back(make_unique<InPatient>("Meena",3,2500,40000));
    bills.push_back(make_unique<MaternityBill>("Divya",30000,4500));
    vector<unique_ptr<Payer>> payers;
    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(50000));
    payers.push_back(make_unique<EmployerScheme>(60));
    for(const auto& b:bills)for(const auto& p:payers)
        cout<<b->type()<<' '<<b->patientName()<<" total "<<b->total()
            <<" | "<<p->name()<<" covers "<<p->amountCovered(*b)<<'\n';
}