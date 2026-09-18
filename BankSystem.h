#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

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

        Customer* customer = new Customer(makeCustomerId(), name, phone, address,
                                          username, password);

        double initialDeposit = readAmount("Enter Initial Deposit: $");
        string accountNumber = makeAccountNumber();
        customer->addAccount(new CurrentAccount(accountNumber, initialDeposit));
        customer->addTransaction("Opened Current Account " + accountNumber +
                                 " with $" + amountText(initialDeposit));

        customers.push_back(customer);
        saveData();

        cout << "\nAccount created successfully." << endl;
        cout << "Customer ID   : " << customer->getCustomerId() << endl;
        cout << "Account Number: " << accountNumber << endl;
    }

    string amountText(double amount) const {
        return toAmountString(amount);
    }

    string toAmountString(double amount) const {
        long long cents = static_cast<long long>(amount * 100.0 + 0.5);
        long long dollars = cents / 100;
        long long remainder = cents % 100;
        string result = to_string(dollars) + ".";
        if (remainder < 10) result += "0";
        result += to_string(remainder);
        return result;
    }

    void adminMenu() {
        string username = readLine("Admin Username: ");
        string password = readLine("Admin Password: ");

        if (username != adminUsername || password != adminPassword) {
            cout << "Invalid admin login." << endl;
            return;
        }

        int choice;
        do {
            cout << "\n========================================" << endl;
            cout << "             ADMIN MENU" << endl;
            cout << "========================================" << endl;
            cout << "1. Search User" << endl;
            cout << "2. Delete User" << endl;
            cout << "3. View Client List" << endl;
            cout << "4. Update Information" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore(10000, '\n');

            switch (choice) {
                case 1: searchUser(); break;
                case 2: deleteUser(); break;
                case 3: viewUsers(); break;
                case 4: updateUser(); break;
                case 5: cout << "Returning to main menu..." << endl; break;
                default: cout << "Invalid choice." << endl;
            }
        } while (choice != 5);
    }

    void searchUser() {
        string key = readLine("Enter Customer ID or Username: ");
        Customer* customer = findCustomerById(key);
        if (customer == 0) customer = findCustomerByUsername(key);

        if (customer == 0) {
            cout << "User not found." << endl;
            return;
        }

        customer->displayInfo();
        customer->displayAccounts();
    }

    void deleteUser() {
        string id = readLine("Enter Customer ID to delete: ");
        for (vector<Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
            if ((*it)->getCustomerId() == id) {
                delete *it;
                customers.erase(it);
                saveData();
                cout << "User deleted successfully." << endl;
                return;
            }
        }
        cout << "User not found." << endl;
    }

    void viewUsers() const {
        if (customers.empty()) {
            cout << "No users registered." << endl;
            return;
        }

        cout << "\n============== CLIENT LIST ==============" << endl;
        for (const Customer* customer : customers) customer->displayInfo();
    }

    void updateUser() {
        string id = readLine("Enter Customer ID: ");
        Customer* customer = findCustomerById(id);
        if (customer == 0) {
            cout << "User not found." << endl;
            return;
        }

        cout << "Press Enter to keep the current value." << endl;
        string name = readLine("New Name [" + customer->getFullName() + "]: ");
        string phone = readLine("New Phone [" + customer->getPhone() + "]: ");
        string address = readLine("New Address [" + customer->getAddress() + "]: ");

        if (!name.empty()) customer->setFullName(name);
        if (!phone.empty()) customer->setPhone(phone);
        if (!address.empty()) customer->setAddress(address);

        saveData();
        cout << "Information updated successfully." << endl;
    }

    void userLogin() {
        string username = readLine("Username: ");
        string password = readLine("Password: ");

        Customer* customer = findCustomerByUsername(username);
        if (customer == 0 || !customer->checkPassword(password)) {
            cout << "Invalid username or password." << endl;
            return;
        }

        userMenu(customer);
    }

    void userMenu(Customer* customer) {
        int choice;
        do {
            cout << "\n========================================" << endl;
            cout << "              USER MENU" << endl;
            cout << "========================================" << endl;
            cout << "Welcome, " << customer->getFullName() << endl;
            cout << "1. View Balance" << endl;
            cout << "2. Deposit" << endl;
            cout << "3. Withdraw" << endl;
            cout << "4. Open Saving Account" << endl;
            cout << "5. Loan" << endl;
            cout << "6. Payment for Bill or Tax" << endl;
            cout << "7. View Transaction History" << endl;
            cout << "8. Transfer to Other Account" << endl;
            cout << "9. Open Current Account" << endl;
            cout << "10. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore(10000, '\n');

            switch (choice) {
                case 1: viewBalance(customer); break;
                case 2: depositMoney(customer); break;
                case 3: withdrawMoney(customer); break;
                case 4: openSavingAccount(customer); break;
                case 5: requestLoan(customer); break;
                case 6: payBillOrTax(customer); break;
                case 7: viewHistory(customer); break;
                case 8: transferMoney(customer); break;
                case 9: openCurrentAccount(customer); break;
                case 10: cout << "Returning to main menu..." << endl; break;
                default: cout << "Invalid choice." << endl;
            }
        } while (choice != 10);
    }

    BankAccount* chooseAccount(Customer* customer) {
        const vector<BankAccount*>& accounts = customer->getAccounts();
        if (accounts.empty()) {
            cout << "No account available." << endl;
            return 0;
        }

        cout << "\nYour accounts:" << endl;
        for (size_t i = 0; i < accounts.size(); ++i) {
            cout << i + 1 << ". " << accounts[i]->getAccountNumber()
                 << " - " << accounts[i]->getAccountType()
                 << " - $" << fixed << setprecision(2)
                 << accounts[i]->getBalance() << endl;
        }

        int number;
        cout << "Choose account number: ";
        cin >> number;
        cin.ignore(10000, '\n');

        if (number < 1 || number > static_cast<int>(accounts.size())) {
            cout << "Invalid account selection." << endl;
            return 0;
        }
        return accounts[number - 1];
    }

    void viewBalance(Customer* customer) {
        BankAccount* account = chooseAccount(customer);
        if (account == 0) return;
        cout << "Current Balance: $" << fixed << setprecision(2)
             << account->getBalance() << endl;
    }

    void depositMoney(Customer* customer) {
        BankAccount* account = chooseAccount(customer);
        if (account == 0) return;

        double amount = readAmount("Enter deposit amount: $");
        if (amount <= 0) {
            cout << "Deposit must be greater than zero." << endl;
            return;
        }

        account->deposit(amount);
        customer->addTransaction("Deposit $" + toAmountString(amount) +
                                 " to " + account->getAccountNumber());
        saveData();
        cout << "Deposit successful." << endl;
    }

    void withdrawMoney(Customer* customer) {
        BankAccount* account = chooseAccount(customer);
        if (account == 0) return;

        double amount = readAmount("Enter withdrawal amount: $");
        if (amount <= 0) {
            cout << "Withdrawal must be greater than zero." << endl;
            return;
        }

        if (!account->withdraw(amount)) {
            cout << "Withdrawal failed. Check your balance or account rules." << endl;
            return;
        }

        customer->addTransaction("Withdraw $" + toAmountString(amount) +
                                 " from " + account->getAccountNumber());
        saveData();
        cout << "Withdrawal successful." << endl;
    }

    void openSavingAccount(Customer* customer) {
        double initialDeposit = readAmount("Enter initial saving deposit: $");
        if (initialDeposit <= 0) {
            cout << "Initial deposit must be greater than zero." << endl;
            return;
        }

        string number = makeAccountNumber();
        customer->addAccount(new SavingAccount(number, initialDeposit));
        customer->addTransaction("Opened Saving Account " + number +
                                 " with $" + toAmountString(initialDeposit));
        saveData();

        cout << "Saving account opened successfully." << endl;
        cout << "Account Number: " << number << endl;
    }

    void openCurrentAccount(Customer* customer) {
        double initialDeposit = readAmount("Enter initial current-account deposit: $");
        if (initialDeposit < 0) {
            cout << "Invalid initial deposit." << endl;
            return;
        }

        string number = makeAccountNumber();
        customer->addAccount(new CurrentAccount(number, initialDeposit));
        customer->addTransaction("Opened Current Account " + number +
                                 " with $" + toAmountString(initialDeposit));
        saveData();

        cout << "Current account opened successfully." << endl;
        cout << "Account Number: " << number << endl;
    }

    void requestLoan(Customer* customer) {
        double amount = readAmount("Enter loan amount: $");
        if (amount <= 0) {
            cout << "Loan amount must be greater than zero." << endl;
            return;
        }

        cout << "Loan request of $" << fixed << setprecision(2) << amount
             << " has been recorded for review." << endl;
        customer->addTransaction("Loan request: $" + toAmountString(amount));
        saveData();
    }

    void payBillOrTax(Customer* customer) {
        BankAccount* account = chooseAccount(customer);
        if (account == 0) return;

        string billName = readLine("Enter Bill/Tax Name: ");
        double amount = readAmount("Enter payment amount: $");

        if (billName.empty() || amount <= 0) {
            cout << "Invalid bill/tax information." << endl;
            return;
        }

        if (!account->withdraw(amount)) {
            cout << "Payment failed due to insufficient funds or account rules." << endl;
            return;
        }

        customer->addTransaction("Payment for " + billName + ": $" +
                                 toAmountString(amount));
        saveData();
        cout << "Payment completed successfully." << endl;
    }

    void viewHistory(Customer* customer) const {
        const vector<string>& history = customer->getTransactions();
        cout << "\n========== TRANSACTION HISTORY ==========" << endl;
        if (history.empty()) {
            cout << "No transactions recorded." << endl;
            return;
        }

        for (size_t i = 0; i < history.size(); ++i)
            cout << i + 1 << ". " << history[i] << endl;
    }

    void transferMoney(Customer* customer) {
        BankAccount* source = chooseAccount(customer);
        if (source == 0) return;

        string targetNumber = readLine("Enter receiver account number: ");
        BankAccount* target = 0;
        Customer* receiver = 0;

        for (Customer* other : customers) {
            target = other->findAccount(targetNumber);
            if (target != 0) {
                receiver = other;
                break;
            }
        }

        if (target == 0 || receiver == customer) {
            cout << "Receiver account not found." << endl;
            return;
        }

        double amount = readAmount("Enter transfer amount: $");
        if (amount <= 0) {
            cout << "Transfer amount must be greater than zero." << endl;
            return;
        }

        if (!source->withdraw(amount)) {
            cout << "Transfer failed. Check your balance or account rules." << endl;
            return;
        }

        target->deposit(amount);
        customer->addTransaction("Transfer $" + toAmountString(amount) +
                                 " to " + targetNumber);
        receiver->addTransaction("Received $" + toAmountString(amount) +
                                 " from " + source->getAccountNumber());
        saveData();

        cout << "Transfer completed successfully." << endl;
    }

    void saveData() const {
        ofstream file("bank_data.bin", ios::binary);
        if (!file) return;

        int customerCount = static_cast<int>(customers.size());
        file.write(reinterpret_cast<const char*>(&customerCount), sizeof(customerCount));
        file.write(reinterpret_cast<const char*>(&nextCustomerNumber), sizeof(nextCustomerNumber));
        file.write(reinterpret_cast<const char*>(&nextAccountNumber), sizeof(nextAccountNumber));

        for (const Customer* customer : customers) customer->save(file);
    }

    string readString(ifstream& file) {
        int length = 0;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (length < 0 || length > 100000) return "";
        string value(length, ' ');
        if (length > 0) file.read(&value[0], length);
        return value;
    }

    void loadData() {
        ifstream file("bank_data.bin", ios::binary);
        if (!file) return;

        int customerCount = 0;
        file.read(reinterpret_cast<char*>(&customerCount), sizeof(customerCount));
        file.read(reinterpret_cast<char*>(&nextCustomerNumber), sizeof(nextCustomerNumber));
        file.read(reinterpret_cast<char*>(&nextAccountNumber), sizeof(nextAccountNumber));

        if (!file || customerCount < 0 || customerCount > 10000) return;

        for (Customer* customer : customers) delete customer;
        customers.clear();

        for (int i = 0; i < customerCount; ++i) {
            string id = readString(file);
            string name = readString(file);
            string phone = readString(file);
            string address = readString(file);
            string username = readString(file);
            string password = readString(file);

            Customer* customer = new Customer(id, name, phone, address, username, password);

            int accountCount = 0;
            file.read(reinterpret_cast<char*>(&accountCount), sizeof(accountCount));
            if (!file || accountCount < 0 || accountCount > 1000) {
                delete customer;
                break;
            }

            for (int a = 0; a < accountCount; ++a) {
                int type = 0;
                file.read(reinterpret_cast<char*>(&type), sizeof(type));
                string accountNumber = readString(file);
                double balance = 0.0;
                file.read(reinterpret_cast<char*>(&balance), sizeof(balance));

                if (!file) break;

                if (type == 1) {
                    double rate = 0.02;
                    file.read(reinterpret_cast<char*>(&rate), sizeof(rate));
                    customer->addAccount(new SavingAccount(accountNumber, balance, rate));
                } else if (type == 2) {
                    double minimum = 0.0;
                    file.read(reinterpret_cast<char*>(&minimum), sizeof(minimum));
                    customer->addAccount(new CurrentAccount(accountNumber, balance, minimum));
                } else {
                    customer->addAccount(new CurrentAccount(accountNumber, balance));
                }
            }

            int transactionCount = 0;
            file.read(reinterpret_cast<char*>(&transactionCount), sizeof(transactionCount));
            if (transactionCount < 0 || transactionCount > 10000) transactionCount = 0;

            for (int t = 0; t < transactionCount; ++t)
                customer->addTransaction(readString(file));

            customers.push_back(customer);
        }
    }

    void run() {
        loadData();
        if (adminUsername.empty()) setupAdmin();

        int choice;
        do {
            cout << "\n========================================" << endl;
            cout << "       BANK APPLICATION SYSTEM" << endl;
            cout << "========================================" << endl;
            cout << "1. Admin Login" << endl;
            cout << "2. User Login" << endl;
            cout << "3. Sign Up Account" << endl;
            cout << "4. Exit System" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore(10000, '\n');

            switch (choice) {
                case 1: adminMenu(); break;
                case 2: userLogin(); break;
                case 3: signUp(); break;
                case 4: saveData(); cout << "Thank you for using the Bank Application System." << endl; break;
                default: cout << "Invalid choice." << endl;
            }
        } while (choice != 4);
    }
};

#endif
