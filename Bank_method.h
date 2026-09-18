#ifndef BANK_METHOD
#define BANK_METHOD

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Customer.h"

class BankSystem {
private:
    vector<Customer*> customers;
    string adminUsername;
    string adminPassword;
    int nextCustomerNumber;
    int nextAccountNumber;

    string makeCustomerId() {
        string id = "C" + to_string(nextCustomerNumber++);
        return id;
    }

    string makeAccountNumber() {
        string number = "A" + to_string(nextAccountNumber++);
        return number;
    }

    string readLine(const string& message) const {
        string value;
        cout << message;
        getline(cin, value);
        return value;
    }

    double readAmount(const string& message) const {
        double amount;
        while (true) {
            cout << message;
            if (cin >> amount && amount >= 0) {
                cin.ignore(10000, '\n');
                return amount;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid amount. Please enter a valid number." << endl;
        }
    }

public:
    BankSystem() : adminUsername(""), adminPassword(""),
                   nextCustomerNumber(1001), nextAccountNumber(10001) {}

    ~BankSystem() {
        for (Customer* customer : customers) delete customer;
        customers.clear();
    }

    BankSystem(const BankSystem&) = delete;
    BankSystem& operator=(const BankSystem&) = delete;

    bool setupAdmin() {
        cout << "\n========================================" << endl;
        cout << "        ADMIN ACCOUNT SETUP" << endl;
        cout << "========================================" << endl;
        adminUsername = readLine("Enter Admin Username: ");
        adminPassword = readLine("Enter Admin Password: ");
        return !adminUsername.empty() && !adminPassword.empty();
    }

    Customer* findCustomerById(const string& id) {
        for (Customer* customer : customers) {
            if (customer->getCustomerId() == id) return customer;
        }
        return 0;
    }

    Customer* findCustomerByUsername(const string& username) {
        for (Customer* customer : customers) {
            if (customer->getUsername() == username) return customer;
        }
        return 0;
    }

    void signUp() {
        cout << "\n========================================" << endl;
        cout << "          CREATE USER ACCOUNT" << endl;
        cout << "========================================" << endl;

        string name = readLine("Enter Full Name: ");
        string phone = readLine("Enter Phone Number: ");
        string address = readLine("Enter Address: ");
        string username = readLine("Create Username: ");

        if (name.empty() || phone.empty() || address.empty() || username.empty()) {
            cout << "All fields are required." << endl;
            return;
        }

        if (findCustomerByUsername(username) != 0) {
            cout << "Username already exists." << endl;
            return;
        }

        string password = readLine("Create Password: ");
        if (password.empty()) {
            cout << "Password cannot be empty." << endl;
            return;
        }
    }
};
#endif