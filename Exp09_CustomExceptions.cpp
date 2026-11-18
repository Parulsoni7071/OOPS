#include <iostream>
#include <exception>
using namespace std;

class BankException : public exception {
protected:
    string msg;
public:
    BankException(string m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class InvalidAmount : public BankException {
public:
    InvalidAmount() : BankException("Error: Amount must be positive!") {}
};

class InsufficientFunds : public BankException {
public:
    InsufficientFunds() : BankException("Error: Insufficient balance!") {}
};

void withdraw(double& balance, double amt) {
    if (amt <= 0) throw InvalidAmount();
    if (amt > balance) throw InsufficientFunds();
    balance -= amt;
    cout << "Withdrawn: " << amt << " | Balance: " << balance << "\n";
}

int main() {
    double bal = 1000;
    try {
        withdraw(bal, 400);
        withdraw(bal, -50);
    } catch (const InvalidAmount& e) {
        cout << e.what() << "\n";
    }

    try {
        withdraw(bal, 800);
    } catch (const InsufficientFunds& e) {
        cout << e.what() << "\n";
    }
    return 0;
}
