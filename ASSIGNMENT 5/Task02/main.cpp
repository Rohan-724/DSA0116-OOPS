#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class BillingError : public runtime_error { public: using runtime_error::runtime_error; };
class ClaimError : public BillingError { public: using BillingError::BillingError; };
class PackageError : public BillingError { public: using BillingError::BillingError; };
class PatientNotFound : public BillingError { public: using BillingError::BillingError; };

class Bill {
    string patient;
protected:
    explicit Bill(string p) : patient(move(p)) {
        if (patient.empty()) throw PatientNotFound("missing patient record");
    }
public:
    virtual ~Bill() noexcept = default;
    virtual double total() const = 0;
    virtual string type() const = 0;
    const string& patientName() const noexcept { return patient; }
    void print() const { cout << type() << " " << patient << ": " << total() << '\n'; }
};

class OutPatientBill final : public Bill {
    double consultation, tests;
public:
    OutPatientBill(string p,double c,double t):Bill(move(p)),consultation(c),tests(t) {
        if(c<0||t<0) throw invalid_argument("negative outpatient charge");
    }
    double total() const override { return consultation+tests; }
    string type() const override { return "OP"; }
};
class InPatientBill final : public Bill {
    int days; double perDay, procedure, medicines;
public:
    InPatientBill(string p,int d,double rate,double proc,double meds)
      :Bill(move(p)),days(d),perDay(rate),procedure(proc),medicines(meds) {
        if(d<0||rate<0||proc<0||meds<0) throw invalid_argument("negative inpatient charge");
    }
    double total() const override { return days*perDay+procedure+medicines; }
    string type() const override { return "IP"; }
};
class DayCareBill final : public Bill {
    double packagePrice;
public:
    DayCareBill(string p,double price):Bill(move(p)),packagePrice(price) {
        if(price<0) throw invalid_argument("negative day-care package");
    }
    double total() const override { return packagePrice; }
    string type() const override { return "DAYCARE"; }
};
class EmergencyBill final : public Bill {
    double base, perMinute; int minutes;
public:
    EmergencyBill(string p,double b,int m,double rate):Bill(move(p)),base(b),perMinute(rate),minutes(m) {
        if(b<0||m<0||rate<0) throw invalid_argument("negative emergency charge");
    }
    double total() const override { return base+minutes*perMinute; }
    string type() const override { return "ER"; }
};

class Payer {
public:
    virtual ~Payer() noexcept = default;
    virtual string name() const = 0;
    virtual double amountCovered(const Bill&) const = 0;
};
class SelfPay final : public Payer {
public:
    string name() const override { return "SelfPay"; }
    double amountCovered(const Bill& b) const override { return b.total(); }
};
class Insurance final : public Payer {
    double limit, coPayPercent;
public:
    Insurance(double l,double p):limit(l),coPayPercent(p) {
        if(l<0||p<0||p>100) throw invalid_argument("invalid insurance policy");
    }
    string name() const override { return "Insurance"; }
    double amountCovered(const Bill& b) const override {
        return min(b.total(),limit)*(100.0-coPayPercent)/100.0;
    }
};
class GovernmentScheme final : public Payer {
    map<string,double> packageRates;
public:
    GovernmentScheme():packageRates{{"OP",1200},{"IP",30000},{"DAYCARE",18000},{"ER",5000}}{}
    string name() const override { return "Government"; }
    double amountCovered(const Bill& b) const override {
        auto it=packageRates.find(b.type());
        if(it==packageRates.end()) throw PackageError("unknown government package: "+b.type());
        return min(b.total(),it->second);
    }
};
// Extension: add a payer without modifying Bill or existing payer classes.
class CorporateTieUp final : public Payer {
    double percentage, cap;
public:
    CorporateTieUp(double p,double c):percentage(p),cap(c) {
        if(p<0||p>100||c<0) throw invalid_argument("invalid corporate policy");
    }
    string name() const override { return "CorporateTieUp"; }
    double amountCovered(const Bill& b) const override { return min(cap,b.total()*percentage/100.0); }
};

int main() {
    cout<<fixed<<setprecision(2);
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatientBill>("Ravi",500,1200));
    bills.push_back(make_unique<InPatientBill>("Meena",3,2500,40000,0));
    bills.push_back(make_unique<DayCareBill>("Asha",22000));
    bills.push_back(make_unique<EmergencyBill>("Imran",1500,30,100));

    vector<unique_ptr<Payer>> payers;
    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(50000,20));
    payers.push_back(make_unique<GovernmentScheme>());
    payers.push_back(make_unique<CorporateTieUp>(70,25000));

    double dailyTotal=0;
    for(const auto& b:bills) { b->print(); dailyTotal+=b->total(); }
    cout<<"Daily bill total: "<<dailyTotal<<'\n';
    for(const auto& p:payers) {
        cout<<"-- "<<p->name()<<" --\n";
        for(const auto& b:bills)
            cout<<b->type()<<" "<<b->patientName()<<" covered: "<<p->amountCovered(*b)<<'\n';
    }
}