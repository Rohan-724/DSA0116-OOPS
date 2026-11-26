#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
class Cart {
    array<string,10> items{}; array<double,10> prices{};
    int n=0; double discount=0;
public:
    Cart& add(const string& item,double price){
        if(n>=static_cast<int>(items.size())) throw out_of_range("cart is full");
        if(price<0) throw invalid_argument("negative price");
        items[n]=item;prices[n]=price;++n;return *this;
    }
    Cart& setDiscount(double discount){
        if(discount<0||discount>100) throw invalid_argument("discount must be 0..100");
        this->discount=discount;return *this;
    }
    double total() const{
        double t=0;for(int i=0;i<n;++i)t+=prices[i];
        return t*(100-discount)/100;
    }
};
int main(){
    Cart c;c.add("Rice",60).add("Dal",120).setDiscount(10);
    Cart* p=&c;p->add("Oil",180);
    cout<<fixed<<setprecision(2)<<p->total()<<'\n';
    Cart direct;direct.add("Milk",40);
    Cart* ptr=&direct;ptr->add("Bread",35);
    Cart& ref=direct;ref.add("Eggs",30);
    Cart* heap=new Cart;heap->add("Apples",80);
    cout<<"Direct/reference total: "<<direct.total()<<", dynamic total: "<<heap->total()<<'\n';
    delete heap;
    Cart a,b,d;a.add("A",100);b.add("B",250);d.add("C",175);
    Cart* carts[]={&a,&b,&d};Cart* highest=carts[0];
    for(Cart* x:carts)if(x->total()>highest->total())highest=x;
    cout<<"Highest cart total: "<<highest->total()<<'\n';
}