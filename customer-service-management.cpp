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
void searchCustomer() {
    if (customerDatabase.empty()) {
        cout << "No customers.\n";
        return;
    }
    cout << "Search by:\n1. Name\n2. Phone\nChoice: ";
    int choice;
    cin >> choice;

    string input;
    bool found = false;

    if (choice == 1) {
        cout << "Enter name: ";
        cin >> input;
        for (const auto& c : customerDatabase)
            if (c.getName() == input) {
                c.display();
                found = true;
            }
    } else if (choice == 2) {
        cout << "Enter phone: ";
        cin >> input;
        for (const auto& c : customerDatabase)
            if (c.getPhone() == input) {
                c.display();
                found = true;
            }
    }

    if (!found) cout << "Customer not found.\n";
}
void updateCustomer() {
    string phone;
    cout << "Enter phone of customer to update: ";
    cin >> phone;
    bool found = false;

    for (auto& c : customerDatabase) {
        if (c.getPhone() == phone) {
            cout << "Current details:\n";
            c.display();
            string newName, newPhone;
            cout << "New name (or . to skip): ";
            cin >> newName;
            if (newName != ".") c.setName(newName);
            cout << "New phone (or . to skip): ";
            cin >> newPhone;
            if (newPhone != ".") c.setPhone(newPhone);
            cout << "Updated successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Customer not found.\n";
}
void deleteCustomer() {
    string phone;
    cout << "Enter phone to delete: ";
    cin >> phone;
    auto it = remove_if(customerDatabase.begin(), customerDatabase.end(), [&](Customer c) {
        return c.getPhone() == phone;
    });
    if (it != customerDatabase.end()) {
        customerDatabase.erase(it, customerDatabase.end());
        cout << "Deleted successfully.\n";
    } else {
        cout << "Customer not found.\n";
    }
}
void saveToFile() {
    ofstream out("customers.txt");
    for (const auto& c : customerDatabase)
        out << c << endl;
    cout << "Database saved.\n";
}

void loadFromFile() {
    ifstream in("customers.txt");
    if (!in) {
        cout << "No file found.\n";
        return;
    }
    customerDatabase.clear();
    Customer c;
    while (in >> c)
        customerDatabase.push_back(c);
    cout << "Database loaded.\n";
}
void addVIPCustomer(string name, string phone, int arrivalTime, int priority) {
    Customer c(name, phone, arrivalTime);
    vipQueue.push({priority, c});
    customerDatabase.push_back(c);
    cout << "VIP Customer added.\n";
}

void serveVIPCustomer() {
    if (vipQueue.empty()) {
        cout << "No VIP customers.\n";
        return;
    }
    Customer vip = vipQueue.top().second;
    vipQueue.pop();
    cout << "Serving VIP:\n";
    vip.display();
}
void reportStats() {
    cout << "Total Customers: " << customerDatabase.size() << endl;
    cout << "VIP Customers: " << vipQueue.size() << endl;
    cout << "Waiting Customers: " << waitingQueue.size() << endl;
}
bool adminLogin() {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    return (user == "admin" && pass == "1234");
}
