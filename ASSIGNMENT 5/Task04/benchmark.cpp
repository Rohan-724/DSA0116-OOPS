#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <variant>
#include <vector>
using namespace std;
using Clock=chrono::steady_clock;

struct OP { double consultation,tests; double total()const{return consultation+tests;} };
struct IP { double days,rate,procedure; double total()const{return days*rate+procedure;} };
struct DayCare { double packagePrice; double total()const{return packagePrice;} };
using BillVariant=variant<OP,IP,DayCare>;
struct PolyBill { virtual ~PolyBill()=default; virtual double total()const=0; };
struct PolyOP:PolyBill { double a,b; PolyOP(double x,double y):a(x),b(y){} double total()const override{return a+b;} };
struct PolyIP:PolyBill { double d,r,p; PolyIP(double x,double y,double z):d(x),r(y),p(z){} double total()const override{return d*r+p;} };
struct PolyDay:PolyBill { double p; explicit PolyDay(double x):p(x){} double total()const override{return p;} };
struct Tagged { int type; double a,b,c; };
double taggedTotal(const Tagged& x) {
    switch(x.type) {
        case 0:return x.a+x.b;
        case 1:return x.a*x.b+x.c;
        default:return x.a;
    }
}
template<class F> double timed(const char* label,F f) {
    auto start=Clock::now(); volatile double result=f();
    auto stop=Clock::now();
    cout<<label<<" seconds "<<chrono::duration<double>(stop-start).count()
        <<" checksum "<<result<<'\n';
    return result;
}
int main() {
    cout<<fixed<<setprecision(6);
    mt19937_64 rng(42);
    for(size_t n:{size_t(10),size_t(1000),size_t(1000000),size_t(10000000)}) {
        vector<unique_ptr<PolyBill>> poly; vector<Tagged> tagged; vector<BillVariant> vars;
        poly.reserve(n);tagged.reserve(n);vars.reserve(n);
        for(size_t i=0;i<n;++i) {
            int t=static_cast<int>(rng()%3);
            if(t==0) {
                double a=100+(rng()%1000),b=50+(rng()%500);
                poly.push_back(make_unique<PolyOP>(a,b));tagged.push_back({0,a,b,0});vars.emplace_back(OP{a,b});
            } else if(t==1) {
                double d=1+(rng()%5),r=1000+(rng()%1000),p=2000+(rng()%5000);
                poly.push_back(make_unique<PolyIP>(d,r,p));tagged.push_back({1,d,r,p});vars.emplace_back(IP{d,r,p});
            } else {
                double p=500+(rng()%3000);
                poly.push_back(make_unique<PolyDay>(p));tagged.push_back({2,p,0,0});vars.emplace_back(DayCare{p});
            }
        }
        cout<<"N="<<n<<'\n';
        double a=timed("virtual",[&]{double s=0;for(const auto& x:poly)s+=x->total();return s;});
        double b=timed("switch",[&]{double s=0;for(const auto& x:tagged)s+=taggedTotal(x);return s;});
        double c=timed("variant_visit",[&]{double s=0;for(const auto& x:vars)s+=visit([](const auto& v){return v.total();},x);return s;});
        cout<<"checksums_equal "<<(abs(a-b)<0.01&&abs(a-c)<0.01)<<"\n";
    }

    constexpr size_t N=1000000;
    for(int invalidPct:{0,1,50}) {
        vector<double> amounts(N,500.0);
        for(size_t i=0;i<N*static_cast<size_t>(invalidPct)/100;++i) amounts[i]=-1;
        volatile size_t accepted=0;
        auto t1=Clock::now();
        for(double x:amounts) { if(x>=0) ++accepted; }
        auto t2=Clock::now();
        cout<<"return_code invalid="<<invalidPct<<" seconds "
            <<chrono::duration<double>(t2-t1).count()<<" accepted "<<accepted<<'\n';
        accepted=0;
        auto t3=Clock::now();
        for(double x:amounts) {
            try { if(x<0) throw invalid_argument("negative"); ++accepted; }
            catch(const invalid_argument&) {}
        }
        auto t4=Clock::now();
        cout<<"exception invalid="<<invalidPct<<" seconds "
            <<chrono::duration<double>(t4-t3).count()<<" accepted "<<accepted<<'\n';
    }
}