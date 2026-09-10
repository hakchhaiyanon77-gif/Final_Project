#ifndef USER_LIBRARY
#define USER_LIBRARY

// {...}
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

class Person {
private:
    string username;
    string password;
    string fullName;

public:
    Person(const string& username = "",
           const string& password = "",
           const string& fullName = "")
        : username(username),
          password(password),
          fullName(fullName) {}

    virtual ~Person() = default;

    const string& getUsername() const {
        return username;
    }

    const string& getFullName() const {
        return fullName;
    }

    const string& getPassword() const {
        return password;
    }

    void setFullName(const string& name) {
        fullName = name;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    bool checkPassword(const string& input) const {
        return password == input;
    }

    virtual string getRole() const = 0;
    virtual void displayInfo() const = 0;
};


// Customer class
class Customer : public Person {
private:
    string accountNumber;
    double balance;
    double loan;

public:
    Customer(const string& username = "",
             const string& password = "",
             const string& fullName = "",
             const string& accountNumber = "",
             double balance = 0.0,
             double loan = 0.0)
        : Person(username, password, fullName),
          accountNumber(accountNumber),
          balance(balance),
          loan(loan) {}

    string getRole() const override {
        return "Customer";
    }

    void displayInfo() const override {
        cout << "Name: " << getFullName() << endl;
        cout << "Username: " << getUsername() << endl;
        cout << "Account: " << accountNumber << endl;
        cout << "Balance: $" << fixed << setprecision(2)
             << balance << endl;
        cout << "Loan: $" << loan << endl;
    }

    const string& getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    double getLoan() const {
        return loan;
    }

    void setBalance(double value) {
        balance = value;
    }

    void setLoan(double value) {
        loan = value;
    }

    bool deposit(double amount) {
        if (amount <= 0)
            return false;

        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance)
            return false;

        balance -= amount;
        return true;
    }

    bool takeLoan(double amount) {
        if (amount <= 0)
            return false;

        loan += amount;
        balance += amount;

        return true;
    }

    string serialize() const {
        ostringstream out;

        out << getUsername() << "|"
            << getPassword() << "|"
            << getFullName() << "|"
            << accountNumber << "|"
            << fixed << setprecision(2)
            << balance << "|"
            << loan;

        return out.str();
    }
};


// Admin class
class Admin : public Person {
public:
    Admin(const string& username = "",
          const string& password = "",
          const string& fullName = "")
        : Person(username, password, fullName) {}

    string getRole() const override {
        return "Admin";
    }

    void displayInfo() const override {
        cout << "Admin: "
             << getFullName()
             << " (" << getUsername() << ")" << endl;
    }
};

#endif