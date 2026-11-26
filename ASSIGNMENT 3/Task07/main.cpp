#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Complex {
    double real, imag;
public:
    Complex() : real(0), imag(0) {}
    Complex(double r) : real(r), imag(0) {}
    Complex(double r,double i) : real(r), imag(i) {}
    Complex operator+(const Complex& z) const { return {real+z.real,imag+z.imag}; }
    Complex operator-(const Complex& z) const { return {real-z.real,imag-z.imag}; }
    Complex operator*(const Complex& z) const {
        return {real*z.real-imag*z.imag,real*z.imag+imag*z.real};
    }
    Complex operator/(const Complex& z) const {
        double denominator=z.real*z.real+z.imag*z.imag;
        if (denominator==0) throw domain_error("division by zero complex number");
        return {(real*z.real+imag*z.imag)/denominator,
                (imag*z.real-real*z.imag)/denominator};
    }
    bool operator==(const Complex& z) const { return real==z.real && imag==z.imag; }
    double magnitude() const { return hypot(real,imag); }
    friend ostream& operator<<(ostream& os,const Complex& z) {
        return os << z.real << (z.imag<0 ? " - " : " + ") << abs(z.imag) << 'j';
    }
};
int main() {
    cout << fixed << setprecision(3);
    const double frequency=50.0, omega=2*acos(-1.0)*frequency;
    const double resistance=10.0, inductance=0.02, capacitance=0.001;
    Complex zr(resistance,0), zl(0,omega*inductance), zc(0,-1.0/(omega*capacitance));
    Complex series=zr+zl+zc;
    cout << "Series RLC impedance: " << series << ", magnitude=" << series.magnitude() << '\n';
    Complex z1(10,5), z2(20,-5);
    Complex parallel=(z1*z2)/(z1+z2);
    cout << "Parallel impedance: " << parallel << ", magnitude=" << parallel.magnitude() << '\n';
    try { cout << z1/Complex(0,0) << '\n'; }
    catch (const domain_error& e) { cout << "Handled error: " << e.what() << '\n'; }
}
