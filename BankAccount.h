#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class BankAccount
{
protected:
    string accountNumber;
    double balance;

public:
    BankAccount() : accountNumber(""), balance(0.0) {}

    BankAccount(const string &number, double initialBalance)
        : accountNumber(number), balance(initialBalance) {}

    virtual ~BankAccount() {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void setAccountNumber(const string &number) { accountNumber = number; }

    virtual string getAccountType() const = 0;

    virtual void displayAccount() const
    {
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Type   : " << getAccountType() << endl;
        cout << "Balance        : $" << fixed << setprecision(2) << balance << endl;
    }

    virtual bool withdraw(double amount)
    {
        if (amount <= 0 || amount > balance)
            return false;
        balance -= amount;
        return true;
    }

    void deposit(double amount)
    {
        if (amount > 0)
            balance += amount;
    }

    virtual void save(ofstream &file) const
    {
        int type = 0;
        file.write(reinterpret_cast<const char *>(&type), sizeof(type));
        int length = static_cast<int>(accountNumber.size());
        file.write(reinterpret_cast<const char *>(&length), sizeof(length));
        file.write(accountNumber.c_str(), length);
        file.write(reinterpret_cast<const char *>(&balance), sizeof(balance));
    }
};

class SavingAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingAccount() : BankAccount(), interestRate(0.02) {}

    SavingAccount(const string &number, double initialBalance, double rate = 0.02)
        : BankAccount(number, initialBalance), interestRate(rate) {}

    string getAccountType() const override { return "Saving Account"; }

    double getInterestRate() const { return interestRate; }

    void addInterest()
    {
        balance += balance * interestRate;
    }

    void displayAccount() const override
    {
        BankAccount::displayAccount();
        cout << "Interest Rate  : " << fixed << setprecision(2)
             << interestRate * 100 << "%" << endl;
    }

    void save(ofstream &file) const override
    {
        int type = 1;
        file.write(reinterpret_cast<const char *>(&type), sizeof(type));
        int length = static_cast<int>(accountNumber.size());
        file.write(reinterpret_cast<const char *>(&length), sizeof(length));
        file.write(accountNumber.c_str(), length);
        file.write(reinterpret_cast<const char *>(&balance), sizeof(balance));
        file.write(reinterpret_cast<const char *>(&interestRate), sizeof(interestRate));
    }
};

class CurrentAccount : public BankAccount
{
private:
    double minimumBalance;

public:
    CurrentAccount() : BankAccount(), minimumBalance(0.0) {}

    CurrentAccount(const string &number, double initialBalance, double minimum = 0.0)
        : BankAccount(number, initialBalance), minimumBalance(minimum) {}

    string getAccountType() const override { return "Current Account"; }

    double getMinimumBalance() const { return minimumBalance; }

    bool withdraw(double amount) override
    {
        if (amount <= 0 || balance - amount < minimumBalance)
            return false;
        balance -= amount;
        return true;
    }

    void displayAccount() const override
    {
        BankAccount::displayAccount();
        cout << "Minimum Balance: $" << fixed << setprecision(2)
             << minimumBalance << endl;
    }

    void save(ofstream &file) const override
    {
        int type = 2;
        file.write(reinterpret_cast<const char *>(&type), sizeof(type));
        int length = static_cast<int>(accountNumber.size());
        file.write(reinterpret_cast<const char *>(&length), sizeof(length));
        file.write(accountNumber.c_str(), length);
        file.write(reinterpret_cast<const char *>(&balance), sizeof(balance));
        file.write(reinterpret_cast<const char *>(&minimumBalance), sizeof(minimumBalance));
    }
    
};

#endif
