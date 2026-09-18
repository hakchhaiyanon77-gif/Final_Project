#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class BankAccount {
protected:
    string accountNumber;
    double balance;

public:
    BankAccount() : accountNumber(""), balance(0.0) {}

    BankAccount(const string& number, double initialBalance)
        : accountNumber(number), balance(initialBalance) {}

    virtual ~BankAccount() {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void setAccountNumber(const string& number) { accountNumber = number; }

    virtual string getAccountType() const = 0;

    virtual void displayAccount() const {
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Type   : " << getAccountType() << endl;
        cout << "Balance        : $" << fixed << setprecision(2) << balance << endl;
    }

    virtual bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    virtual void save(ofstream& file) const {
        int type = 0;
        file.write(reinterpret_cast<const char*>(&type), sizeof(type));
        int length = static_cast<int>(accountNumber.size());
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(accountNumber.c_str(), length);
        file.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
    }
};