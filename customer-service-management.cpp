#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

struct Customer {
    int id;
    string name;
    string issue;
    string arrivalTime;

    Customer(int _id, string _name, string _issue, string _arrivalTime)
        : id(_id), name(_name), issue(_issue), arrivalTime(_arrivalTime) {}
};

class CustomerService {
private:
    queue<Customer> customerQueue;
    vector<Customer> customerHistory;
    int nextId = 1;

public:
    void addCustomer() {
        string name, issue, time;
        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter issue description: ";
        getline(cin, issue);
        cout << "Enter arrival time (HH:MM): ";
        getline(cin, time);

        Customer c(nextId++, name, issue, time);
        customerQueue.push(c);
        customerHistory.push_back(c);

        cout << "\nCustomer added successfully!\n\n";
    }

    void serveCustomer() {
        if (customerQueue.empty()) {
            cout << "\nNo customers to serve.\n\n";
            return;
        }

        Customer c = customerQueue.front();
        customerQueue.pop();

        cout << "\nServing Customer ID: " << c.id << "\n"
             << "Name: " << c.name << "\n"
             << "Issue: " << c.issue << "\n"
             << "Arrival Time: " << c.arrivalTime << "\n\n";
    }

    void viewWaitingCustomers() {
        if (customerQueue.empty()) {
            cout << "\nNo customers in queue.\n\n";
            return;
        }

        queue<Customer> temp = customerQueue;
        cout << left << setw(5) << "ID" << setw(20) << "Name" 
             << setw(25) << "Issue" << setw(10) << "Time" << "\n";
        cout << string(60, '-') << "\n";

        while (!temp.empty()) {
            Customer c = temp.front();
            cout << setw(5) << c.id << setw(20) << c.name 
                 << setw(25) << c.issue << setw(10) << c.arrivalTime << "\n";
            temp.pop();
        }
        cout << "\n";
    }

    void sortCustomersByName() {
        if (customerHistory.empty()) {
            cout << "\nNo customer records available.\n\n";
            return;
        }

        vector<Customer> temp = customerHistory;
        sort(temp.begin(), temp.end(), [](Customer a, Customer b) {
            return a.name < b.name;
        });

        cout << "\n--- Customers Sorted by Name ---\n";
        displayCustomerList(temp);
    }

    void sortCustomersByTime() {
        if (customerHistory.empty()) {
            cout << "\nNo customer records available.\n\n";
            return;
        }

        vector<Customer> temp = customerHistory;
        sort(temp.begin(), temp.end(), [](Customer a, Customer b) {
            return a.arrivalTime < b.arrivalTime;
        });

        cout << "\n--- Customers Sorted by Arrival Time ---\n";
        displayCustomerList(temp);
    }

    void displayCustomerList(const vector<Customer>& list) {
        cout << left << setw(5) << "ID" << setw(20) << "Name" 
             << setw(25) << "Issue" << setw(10) << "Time" << "\n";
        cout << string(60, '-') << "\n";

        for (const auto& c : list) {
            cout << setw(5) << c.id << setw(20) << c.name 
                 << setw(25) << c.issue << setw(10) << c.arrivalTime << "\n";
        }
        cout << "\n";
    }

    void saveToFile() {
        ofstream file("customer_data.txt");
        if (!file) {
            cout << "\nFailed to open file for writing.\n";
            return;
        }

        file << left << setw(5) << "ID" << setw(20) << "Name" 
             << setw(25) << "Issue" << setw(10) << "Time" << "\n";
        file << string(60, '-') << "\n";

        for (const auto& c : customerHistory) {
            file << setw(5) << c.id << setw(20) << c.name 
                 << setw(25) << c.issue << setw(10) << c.arrivalTime << "\n";
        }

        file.close();
        cout << "\nCustomer data saved to 'customer_data.txt'\n\n";
    }
};

void showMenu() {
    cout << "========== Customer Service Management ==========\n";
    cout << "1. Add New Customer\n";
    cout << "2. Serve Next Customer\n";
    cout << "3. View Waiting Customers\n";
    cout << "4. Sort Customers by Name\n";
    cout << "5. Sort Customers by Arrival Time\n";
    cout << "6. Save Data to File\n";
    cout << "7. Exit\n";
    cout << "=================================================\n";
    cout << "Enter your choice: ";
}

int main() {
    CustomerService cs;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cs.addCustomer();
                break;
            case 2:
                cs.serveCustomer();
                break;
            case 3:
                cs.viewWaitingCustomers();
                break;
            case 4:
                cs.sortCustomersByName();
                break;
            case 5:
                cs.sortCustomersByTime();
                break;
            case 6:
                cs.saveToFile();
                break;
            case 7:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
