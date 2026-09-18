#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "BankAccount.h"

class Customer {
private:
    string customerId;
    string fullName;
    string phone;
    string address;
    string username;
    string password;
    vector<BankAccount*> accounts;
    vector<string> transactions;

public:
    Customer() {}

    Customer(const string& id, const string& name, const string& phoneNumber,
         const string& customerAddress, const string& user, const string& pass)
    : customerId(id),
      fullName(name),
      phone(phoneNumber),
      address(customerAddress),
      username(user),
      password(pass) {}

    string getCustomerId() const {
    return customerId;
}

string getFullName() const {
    return fullName;
}

string getPhone() const {
    return phone;
}

string getAddress() const {
    return address;
}

string getUsername() const {
    return username;
}
bool checkPassword(const string& pass) const {
    return password == pass;
}
void setPassword(const string& newPassword) {
    password = newPassword;
}
void setFullName(const string& name) {
    fullName = name;
}

void setPhone(const string& number) {
    phone = number;
}

void setAddress(const string& newAddress) {
    address = newAddress;
}
void addAccount(BankAccount* account) {
    if (account != 0) accounts.push_back(account);
}

vector<BankAccount*>& getAccounts() {
    return accounts;
}

const vector<BankAccount*>& getAccounts() const {
    return accounts;
}
void addAccount(BankAccount* account) {
    if (account != 0){
        accounts.push_back(account);
    }       
}

const vector<BankAccount*>& getAccounts() const {
    return accounts;
}
BankAccount* findAccount(const string& number) {
    for (BankAccount* account : accounts) {
        if (account->getAccountNumber() == number)
            return account;
    }

    return 0;
}
void addTransaction(const string& transaction) {
    transactions.push_back(transaction);
}

const vector<string>& getTransactions() const {
    return transactions;
}
void displayInfo() const {
    cout << "\n----------------------------------------" << endl;
    cout << "Customer ID : " << customerId << endl;
    cout << "Name        : " << fullName << endl;
    cout << "Phone       : " << phone << endl;
    cout << "Address     : " << address << endl;
    cout << "Username    : " << username << endl;
    cout << "Accounts    : " << accounts.size() << endl;
    cout << "----------------------------------------" << endl;
}

void displayAccounts() const {
    if (accounts.empty()) {
        cout << "No bank accounts found." << endl;
        return;
    }

    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << "\nAccount " << i + 1 << endl;
        accounts[i]->displayAccount();
    }
}
void save(ofstream& file) const {
    int length;

    length = static_cast<int>(customerId.size());
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(customerId.c_str(), length);

    length = static_cast<int>(fullName.size());
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(fullName.c_str(), length);

    length = static_cast<int>(phone.size());
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(phone.c_str(), length);

    length = static_cast<int>(address.size());
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(address.c_str(), length);

    length = static_cast<int>(username.size());
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(username.c_str(), length);

    length = static_cast<int>(password.size());
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(password.c_str(), length);

    int accountCount = static_cast<int>(accounts.size());
    file.write(reinterpret_cast<const char*>(&accountCount), sizeof(accountCount));

    for (BankAccount* account : accounts)
        account->save(file);

    int transactionCount = static_cast<int>(transactions.size());
    file.write(reinterpret_cast<const char*>(&transactionCount), sizeof(transactionCount));

    for (const string& transaction : transactions) {
        length = static_cast<int>(transaction.size());
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(transaction.c_str(), length);
    }
}
};

#endif