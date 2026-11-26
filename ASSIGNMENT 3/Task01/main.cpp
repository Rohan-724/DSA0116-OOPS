#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
using namespace std;

class Book {
    string title, author;
    int copies;
public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(string t) : Book(move(t), "Unknown", 1) {}
    Book(string t, string a, int c) : title(move(t)), author(move(a)), copies(c) {
        if (copies < 0) throw invalid_argument("Copies cannot be negative");
    }
    void display() const {
        cout << title << " | " << author << " | copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book defaultBook;
        Book titledBook("The Alchemist");
        Book fullBook("Clean Code", "Robert C. Martin", 4);
        defaultBook.display();
        titledBook.display();
        fullBook.display();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
