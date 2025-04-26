#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
class customer{
    private:
    string name;
    string phone;
    int arrivalTime;
    public:
    customer(){}
    customer(string n,string p,int t):name(n),phone(p),arrivalTime(t){}
    string getName() const {return name;}
    string getPhone() const {return phone;}
    int getArrivalTime()const {return arrivalTime;}
    
    void setName(string n){name = n;}
    void setPhone(string p){phone = p;}

    void display() const{
        cout<<"name: "<<name<<",phone: "<<phone<<",time: "<<arrivalTime<<endl;
    }
    friend istream& operator>>(istream& in, customer& c)
    {
        in >> c.name>>c.phone >> c.arrivalTime;
        return in;
    }
    friend ostream& operator<<ostream& out, const customer& c)
    {
        out<< c.namme <<" "<<c.phone<< " " << c.arrivalTime;
        return out;
    }
};