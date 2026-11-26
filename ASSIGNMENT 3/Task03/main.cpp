#include <iostream>
#include <stdexcept>
using namespace std;

class Auditorium {
    size_t rows, columns, bookings;
    bool** seats;
public:
    Auditorium(size_t r, size_t c) : rows(r), columns(c), bookings(0), seats(nullptr) {
        if (!rows || !columns) return;
        seats = new bool*[rows]{};
        try {
            for (size_t i=0; i<rows; ++i) seats[i]=new bool[columns]{};
        } catch (...) {
            for (size_t i=0; i<rows; ++i) delete[] seats[i];
            delete[] seats; seats=nullptr; throw;
        }
    }
    Auditorium(const Auditorium&) = delete;
    Auditorium& operator=(const Auditorium&) = delete;
    bool book(size_t r, size_t c) {
        if (r>=rows || c>=columns) throw out_of_range("seat coordinate");
        if (seats[r][c]) return false;
        seats[r][c]=true; ++bookings; return true;
    }
    bool cancel(size_t r, size_t c) {
        if (r>=rows || c>=columns) throw out_of_range("seat coordinate");
        if (!seats[r][c]) return false;
        seats[r][c]=false; --bookings; return true;
    }
    ~Auditorium() {
        if (seats) {
            for (size_t i=0; i<rows; ++i) delete[] seats[i];
            delete[] seats;
        }
        cout << "Auditorium destroyed; active bookings: " << bookings << '\n';
    }
};
int main() {
    Auditorium local(2,3);
    local.book(0,1); local.cancel(0,1); local.book(1,2);
    { Auditorium blockObject(1,2); blockObject.book(0,0); }
    Auditorium* heapObject = new Auditorium(3,4);
    heapObject->book(2,2);
    delete heapObject;
    Auditorium empty(0,5);
}
