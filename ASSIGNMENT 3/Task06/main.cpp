#include <iostream>
#include <cstring>
using namespace std;

class Text {
    char* data;
public:
    explicit Text(const char* value="") {
        data=new char[strlen(value)+1];
        strcpy(data,value);
    }
    Text(const Text& other) {
        data=new char[strlen(other.data)+1];
        strcpy(data,other.data);
    }
    Text& operator=(const Text& other) {
        if (this!=&other) {
            char* replacement=new char[strlen(other.data)+1];
            strcpy(replacement,other.data);
            delete[] data;
            data=replacement;
        }
        return *this;
    }
    ~Text() { delete[] data; }
    friend Text operator+(const Text& lhs,const Text& rhs) {
        size_t n=strlen(lhs.data)+strlen(rhs.data);
        char* joined=new char[n+1];
        strcpy(joined,lhs.data); strcat(joined,rhs.data);
        Text result(joined);
        delete[] joined;
        return result;
    }
    bool operator==(const Text& rhs) const { return strcmp(data,rhs.data)==0; }
    bool operator!=(const Text& rhs) const { return !(*this==rhs); }
    friend ostream& operator<<(ostream& os,const Text& value) { return os<<value.data; }
};
int main() {
    Text first("Operator "), second("overloading"), punctuation("!");
    Text sentence=first+second+punctuation;
    cout << sentence << '\n';
    Text copy; copy=sentence;
    cout << boolalpha << "Equal after deep copy: " << (copy==sentence) << '\n';
    copy=copy;
    cout << "Different from first: " << (copy!=first) << '\n';
    Text empty("");
    cout << "Empty text: [" << empty << "]\n";
}
