#include <iostream>
using namespace std;

class BankAccount {
private:
    int accNo;
protected:
    double balance;
public:
    string name;
    BankAccount(string n, int a, double b) : name(n), accNo(a), balance(b) {}
    void deposit(double amt) { balance += amt; }
    void show() { cout << name << " (Acc: " << accNo << ") Bal: " << balance << "\n"; }
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(string n, int a, double b) : BankAccount(n, a, b) {}
    void addInterest() { balance += balance * 0.05; }
};

int main() {
    SavingsAccount s("Aarav", 101, 5000);
    s.deposit(1000);
    s.addInterest();
    s.show();
    return 0;
}
