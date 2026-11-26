#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Time {
    int seconds;
public:
    explicit Time(int s=0) : seconds(s) {
        if (s<0) throw invalid_argument("Time cannot be negative");
    }
    Time& operator++() { ++seconds; return *this; }
    Time operator++(int) { Time previous=*this; ++seconds; return previous; }
    bool operator==(const Time& rhs) const { return seconds==rhs.seconds; }
    bool operator<(const Time& rhs) const { return seconds<rhs.seconds; }
    friend ostream& operator<<(ostream& os,const Time& t) {
        return os << t.seconds/3600 << ':' << (t.seconds/60)%60 << ':' << t.seconds%60;
    }
};
class Playlist {
    vector<string> tracks;
public:
    Playlist(initializer_list<string> values) : tracks(values) {}
    string& operator[](size_t i) {
        if (i>=tracks.size()) throw out_of_range("track index");
        return tracks[i];
    }
    const string& operator[](size_t i) const {
        if (i>=tracks.size()) throw out_of_range("track index");
        return tracks[i];
    }
    size_t size() const { return tracks.size(); }
};
int main() {
    Time t(5);
    Time old=t++;
    Time now=++t;
    cout << "Postfix result: " << old << ", prefix result: " << now << '\n';
    Time boundary(3599); ++boundary;
    cout << "After 3599 seconds: " << boundary << '\n';
    Playlist playlist{"Track A","Track B","Track C"};
    playlist[1]="Updated Track B";
    for (size_t i=0;i<playlist.size();++i) cout << playlist[i] << '\n';
    try { cout << playlist[99] << '\n'; }
    catch (const out_of_range& e) { cout << "Checked access: " << e.what() << '\n'; }
}
