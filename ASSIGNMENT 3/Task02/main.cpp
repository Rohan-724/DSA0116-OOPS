#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Prescription {
    size_t count;
    string* medicines;
public:
    explicit Prescription(size_t n = 0) : count(n), medicines(n ? new string[n] : nullptr) {}
    Prescription(const Prescription& other)
        : count(other.count), medicines(count ? new string[count] : nullptr) {
        for (size_t i=0; i<count; ++i) medicines[i]=other.medicines[i];
    }
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            string* copy = other.count ? new string[other.count] : nullptr;
            for (size_t i=0; i<other.count; ++i) copy[i]=other.medicines[i];
            delete[] medicines;
            medicines=copy; count=other.count;
        }
        return *this;
    }
    ~Prescription() { delete[] medicines; }
    void set(size_t i, const string& value) {
        if (i>=count) throw out_of_range("medicine index");
        medicines[i]=value;
    }
    const string& get(size_t i) const {
        if (i>=count) throw out_of_range("medicine index");
        return medicines[i];
    }
    size_t size() const { return count; }
};
void passByValue(Prescription p) { cout << "Value copy size: " << p.size() << '\n'; }
void passByReference(const Prescription& p) { cout << "Reference size: " << p.size() << '\n'; }

int main() {
    Prescription original(2);
    original.set(0,"Paracetamol"); original.set(1,"ORS");
    Prescription copied(original);
    copied.set(1,"Cetirizine");
    Prescription assigned(1); assigned=original;
    original.set(0,"Ibuprofen");
    assigned=assigned; // self-assignment
    cout << original.get(0) << ", " << original.get(1) << '\n';
    cout << copied.get(0) << ", " << copied.get(1) << '\n';
    cout << assigned.get(0) << ", " << assigned.get(1) << '\n';
    passByValue(original); passByReference(original);
}
