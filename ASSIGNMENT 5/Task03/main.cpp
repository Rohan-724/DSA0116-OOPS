#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class ClaimError : public runtime_error {
public: using runtime_error::runtime_error;
};

double approve(double billed,double cover) {
    if(billed<0||cover<0) throw invalid_argument("negative amount");
    if(billed>cover) throw ClaimError("exceeds cover");
    return billed;
}
double settle(double billed,double cover) {
    try { return approve(billed,cover); }
    catch(const ClaimError& e) {
        cout<<"audit: "<<e.what()<<'\n';
        throw; // preserve the same exception object and dynamic type
    }
}

void validateAmount(double amount) {
    if(amount<0) throw invalid_argument("negative");
    if(amount>1e6) throw out_of_range("too large");
    cout<<"ok ";
}
void processAmount(double amount) {
    try { validateAmount(amount); }
    catch(const out_of_range& e) {
        cout<<"[log "<<e.what()<<"] ";
        throw;
    }
}
struct Resource {
    string label;
    explicit Resource(string s):label(move(s)){}
    ~Resource() noexcept { cout<<"destroyed "<<label<<'\n'; }
};

int main() {
    cout<<"-- claim approval --\n";
    double cases[][2]={{40000,50000},{60000,50000},{-1,50000}};
    for(auto& c:cases) {
        try { cout<<"approved "<<settle(c[0],c[1])<<'\n'; }
        catch(const ClaimError& e) { cout<<"claim rejected: "<<e.what()<<'\n'; }
        catch(const exception& e) { cout<<"error: "<<e.what()<<'\n'; }
    }

    cout<<"-- validation and rethrow --\n";
    for(double a:{100.0,-5.0,2e6}) {
        try { processAmount(a); cout<<"done "; }
        catch(const exception& e) { cout<<"caught "<<e.what()<<' '; }
    }
    cout<<'\n';

    cout<<"-- conversion errors --\n";
    for(const string s:{"125.5","not-a-number"}) {
        try { cout<<stod(s)<<'\n'; }
        catch(const invalid_argument& e) { cout<<"invalid numeric input: "<<e.what()<<'\n'; }
        catch(const out_of_range& e) { cout<<"numeric input out of range: "<<e.what()<<'\n'; }
    }

    cout<<"-- negative charge and missing patient --\n";
    try { if(-10<0) throw invalid_argument("negative charge"); }
    catch(const exception& e) { cout<<e.what()<<'\n'; }
    try { string patient; if(patient.empty()) throw runtime_error("missing patient record"); }
    catch(const exception& e) { cout<<e.what()<<'\n'; }

    cout<<"-- allocation failure test (run separately if OS overcommit is enabled) --\n";
    try {
        volatile size_t impossible=numeric_limits<size_t>::max();
        char* p=new char[impossible];
        delete[] p;
    } catch(const bad_alloc& e) {
        cout<<"allocation failure caught: "<<e.what()<<'\n';
    } catch(const exception& e) {
        cout<<"allocation request rejected: "<<e.what()<<'\n';
    }

    cout<<"-- RAII during exception --\n";
    try {
        Resource r("claim");
        throw ClaimError("forced failure");
    } catch(const exception& e) {
        cout<<"top-level caught: "<<e.what()<<'\n';
    }
}