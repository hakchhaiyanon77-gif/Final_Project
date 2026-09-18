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
    if (account != 0)
        accounts.push_back(account);
}

vector<BankAccount*>& getAccounts() {
    return accounts;
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
};

#endif