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
};

#endif