#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Account {
protected:
    string idNumber;
    string holderFullName;
    double accountBalance;

public:
    Account(const string& id, const string& fullName, double initialBalance)
        : idNumber(id), holderFullName(fullName), accountBalance(initialBalance) {}

    void depositAmount(double amount) {
        accountBalance += amount;
    }

    virtual void withdrawal(double amount) = 0;

    double getBalance() const {
        return accountBalance;
    }

    virtual void displayDetails() const {
        cout << "The Account Information for " << holderFullName << " (ID: " << idNumber << "):\n";
        cout << "   The Account Holder's Name: " << holderFullName << "\n";
        cout << "   The Balance: $" << fixed << setprecision(2) << accountBalance << "\n";
    }

    void transferFunds(Account& recipient, double amount) {
        if (accountBalance >= amount) {
            withdrawal(amount);
            recipient.depositAmount(amount);
            cout << "The Transfer was successful.\n";
        } else {
            cout << "There is Insufficient balance for a transfer.\n";
        }
    }

    friend ostream& operator<<(ostream& os, const Account& acc);
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const string& id, const string& fullName, double initialBalance, double rate)
        : Account(id, fullName, initialBalance), interestRate(rate) {}

    void withdrawal(double amount) override {
        const double minBalance = 100; // Minimum balance required for savings account
        if (accountBalance - amount >= minBalance) {
            accountBalance -= amount;
        } else {
            cout << "There is Insufficient balance fora withdrawal.\n";
        }
    }

    void displayDetails() const override {
        Account::displayDetails();
        cout << " Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%\n";
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(const string& id, const string& fullName, double initialBalance, double limit)
        : Account(id, fullName, initialBalance), overdraftLimit(limit) {}

    void withdrawal(double amount) override {
        if (accountBalance + overdraftLimit >= amount) {
            accountBalance -= amount;
        } else {
            cout << "Withdrawal amount exceeds overdraft limit.\n";
        }
    }

    void displayDetails() const override {
        Account::displayDetails();
        cout << "  Overdraft Limit: $" << fixed << setprecision(2) << overdraftLimit << "\n";
    }
};

ostream& operator<<(ostream& os, const Account& acc) {
    acc.displayDetails();
    return os;
}

int main() {
    string fullName1 = "John Doe";
    string fullName2 = "Jane Doe";
    string id1 = "S123";
    string id2 = "C456";
    string id0 = "S123";
    double overdraftLimit = 500;
    double interestRate = 0.02;
    double initialBalance1 = 1000;
    double initialBalance2 = 2000;

    SavingsAccount savings(id0, fullName1, initialBalance1, interestRate);
    CurrentAccount current(id2, fullName2, initialBalance2, overdraftLimit);

    cout << savings;
    cout << current;

    savings.depositAmount(500);
    current.withdrawal(1000);

    cout << savings;
    cout << current;

    savings.transferFunds(current, 300);

    cout << savings;
    cout << current;

    return 0;
}
