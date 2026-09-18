Automate
# Bank Application System

A console-based banking project written in C++ for **BSE1212 – Computer Programming 2** at Limkokwing University of Technology, Cambodia.

This project demonstrates encapsulation, inheritance, polymorphism and abstraction through customer management and different bank account types.

## Team Members

| Name | GitHub Username |
|---|---|
| Hak Chhaiya Non | [hakchhaiyanon77-gif](https://github.com/hakchhaiyanon77-gif) |
| Lychin Ngeth | [ngethlychin9-netizen](https://github.com/ngethlychin9-netizen) |
| Phoung Monyrak | [monyrak0166-star](https://github.com/monyrak0166-star) |

## Features

### Administrator

- Search for customers by ID or username.
- View the customer list.
- Update customer information.
- Delete customers.

### Customer

- Register and log in.
- View account balances.
- Deposit and withdraw money.
- Open saving and current accounts.
- Transfer money to another customer.
- Record loan requests.
- Simulate bill and tax payments.
- View transaction history.

Customer and account records are saved locally in `bank_data.bin`.

## Project Files

| File | Purpose |
|---|---|
| `Main.cpp` | Starts the program. |
| `Bank_method.h` | Defines `BankSystem` and manages menus and banking operations. |
| `BankAccount.h` | Defines `BankAccount`, `SavingAccount` and `CurrentAccount`. |
| `Customer.h` | Stores customer details, accounts and transaction history. |
| `exception.h` | Defines custom banking exception classes. |

`Main.cpp` should include `Bank_method.h`. Do not also include another header that defines the same `BankSystem` class.

## Object-Oriented Design

### Encapsulation

Customer details are private and accessed through public methods. Account numbers and balances are protected so derived account classes can use them.

### Inheritance

`SavingAccount` and `CurrentAccount` inherit common attributes and operations from `BankAccount`.

### Polymorphism

Accounts are stored using `BankAccount*` pointers. Virtual methods such as `displayAccount()`, `getAccountType()` and `save()` allow each account type to provide its own behaviour.

### Abstraction

`BankAccount` is an abstract class because `getAccountType()` is a pure virtual function. It provides a common interface for the different account types.

## How to Run

### Requirements

- A C++ compiler supporting C++11 or later.
- Visual Studio Code, if using the editor instructions below.
- The Code Runner extension, if using **Run Code**.

### Using Visual Studio Code

1. Open the project folder.
2. Make sure `g++` is installed and available in your terminal.
3. Open Settings and enable **Code Runner: Run In Terminal**.
4. Save all project files.
5. Open `Main.cpp`.
6. Click **Run Code**, or press **Ctrl + Alt + N**.

Run `Main.cpp`, not a `.h` file.

### Using the Terminal

Open a terminal in the project folder and compile:

```powershell
g++ -std=c++11 Main.cpp -o Main.exe
```

If compilation succeeds, start the program:

```powershell
.\Main.exe
```

## Using the Program

1. Enter administrator credentials when the setup prompt appears.
2. Select an option from the main menu:
   - Admin Login
   - User Login
   - Sign Up Account
   - Exit System
3. Register a customer account before using customer login.
4. Follow the prompts to select an account and perform a transaction.

Run the application from the project folder to keep the data file in a consistent location.

## Current Limitations

- This is an educational simulation and does not connect to a real bank.
- Loan requests are recorded only; approval and repayment are not implemented.
- Bill and tax payments do not contact external services.
- Saving-account interest calculation exists, but it is not connected to a menu option.
- The supplied exception classes still need integration with banking operations.
- Passwords are stored without encryption or hashing. Use sample credentials only.

## Common Compilation Errors

### `BankSystem was not declared`

Make sure `Main.cpp` includes:

```cpp
#include "Bank_method.h"
```

### `redefinition of class BankSystem`

Both `Bank_method.h` and another header may define `BankSystem`. Include only the intended definition.

### Duplicate methods in `Customer.h`

Keep only one definition of each method. The const and non-const versions of `getAccounts()` are valid together, but neither version should appear twice.

## GitHub Collaboration

Before starting work, check your working tree and get the latest team changes. Develop changes on a feature branch, make clear commits, and open a pull request for a teammate to review.

Compile and check the affected features before merging.

Generated executables and local banking data should not be committed. Add these entries to `.gitignore`:

```gitignore
*.exe
bank_data.bin
```

If these files are already tracked, adding them to `.gitignore` alone will not remove them from Git tracking.

## Repository

[Final_Project on GitHub](https://github.com/hakchhaiyanon77-gif/Final_Project)
