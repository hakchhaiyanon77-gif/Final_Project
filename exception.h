#ifndef BANK_EXCEPTION_H
#define BANK_EXCEPTION_H

#include <exception>
#include <string>

class BankException : public std::exception
{
private:
    std::string message;

public:
    BankException(const std::string& errorMessage)
    {
        message = errorMessage;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Invalid amount. Amount must be greater than zero.")
    {
    }
};

class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Insufficient balance for this transaction.")
    {
    }
};

class MinimumBalanceException : public BankException
{
public:
    MinimumBalanceException()
        : BankException("This transaction would go below the minimum balance.")
    {
    }
};

class AccountNotFoundException : public BankException
{
public:
    AccountNotFoundException()
        : BankException("Bank account not found.")
    {
    }
};

class FileException : public BankException
{
public:
    FileException(const std::string& errorMessage)
        : BankException(errorMessage)
    {
    }
};

#endif