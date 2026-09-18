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
};

#endif