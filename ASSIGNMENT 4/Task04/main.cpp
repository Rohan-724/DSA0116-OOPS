#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class Account {
public:
    virtual double rate() const{return 3.5;}
    virtual ~Account(){cout<<"Account destroyed\n";}
};
class SeniorAccount:public Account {
    unique_ptr<double[]> history;
public:
    SeniorAccount():history(make_unique<double[]>(100)){}
    double rate() const override{return 4.0;}
    ~SeniorAccount() override{cout<<"SeniorAccount destroyed\n";}
};
int main(){
    vector<unique_ptr<Account>> accounts;
    accounts.push_back(make_unique<Account>());
    accounts.push_back(make_unique<SeniorAccount>());
    for(const auto& a:accounts) cout<<a->rate()<<'\n';
    cout<<"Objects retain their dynamic types; smart pointers own them.\n";
}