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

queue<Customer> waitingQueue;
priority_queue<pair<int, Customer>> vipQueue;
vector<Customer> customerDatabase;

void addCustomer(string name, string phone, int arrivalTime) {
    Customer c(name, phone, arrivalTime);
    waitingQueue.push(c);
    customerDatabase.push_back(c);
    cout << "Customer " << name << " added.\n";
}

void serveCustomer() {
    if (waitingQueue.empty()) {
        cout << "No customers to serve.\n";
        return;
    }
    Customer c = waitingQueue.front();
    waitingQueue.pop();
    cout << "Serving customer:\n";
    c.display();
}
void sortByTime() {
    sort(customerDatabase.begin(), customerDatabase.end(), [](Customer a, Customer b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });
    cout << "Sorted by Time:\n";
    for (const auto& c : customerDatabase) c.display();
}

void sortByName() {
    sort(customerDatabase.begin(), customerDatabase.end(), [](Customer a, Customer b) {
        return a.getName() < b.getName();
    });
    cout << "Sorted by Name:\n";
    for (const auto& c : customerDatabase) c.display();
}
void showAllCustomers() {
    cout << "Customer Database:\n";
    for (const auto& c : customerDatabase)
        c.display();
}
