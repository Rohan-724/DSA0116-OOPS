#include <iostream>
#include <iomanip>
using namespace std;

class Money {
    long long paise;
    explicit Money(long long totalPaise, bool) : paise(totalPaise) {}
public:
    Money(long long rupees=0, long long extraPaise=0)
        : paise(rupees*100 + extraPaise) {}
    static Money fromPaise(long long p) { return Money(p,true); }
    Money operator+(const Money& rhs) const { return fromPaise(paise+rhs.paise); }
    Money operator-(const Money& rhs) const { return fromPaise(paise-rhs.paise); }
    Money& operator+=(const Money& rhs) { paise+=rhs.paise; return *this; }
    bool operator==(const Money& rhs) const { return paise==rhs.paise; }
    bool operator<(const Money& rhs) const { return paise<rhs.paise; }
    friend ostream& operator<<(ostream& os,const Money& m) {
        long long amount=m.paise;
        if (amount<0) { os << "-Rs "; amount=-amount; }
        else os << "Rs ";
        return os << amount/100 << '.' << setw(2) << setfill('0')
                  << amount%100 << setfill(' ');
    }
    friend istream& operator>>(istream& is,Money& m) {
        long long rupees, p; char dot;
        if (is>>rupees>>dot>>p && dot=='.' && p>=0 && p<100)
            m=fromPaise(rupees*100+p);
        else is.setstate(ios::failbit);
        return is;
    }
};
int main() {
    Money a(120,75), b(79,25);
    Money sum=a+b;
    cout << "Sum: " << sum << '\n';
    cout << "Equal to Rs 200: " << boolalpha << (sum==Money(200)) << '\n';
    cout << "Paise carry: " << Money(0,75)+Money(0,50) << '\n';
    cout << "Subtraction: " << Money(2)-Money(3) << '\n';
    Money total; total+=a; total+=b;
    cout << "Accumulated: " << total << '\n';
}
