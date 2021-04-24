#include <iostream>
using namespace std;

class Client{
private:
    static int objectsCount;
    int code;
    string name;
public:
    static int GetObjectsCount();

    Client(int c, string n);
    ~Client();

    int GetCode() const;
    string GetName();
};
int Client::objectsCount = 0;
Client::Client(int c, string n):code(c), name(move(n)){
    Client::objectsCount += 1;
}
int Client::GetCode() const {
    return code;
}
string Client::GetName() {
    return name;
}
int Client::GetObjectsCount() {
    return Client::objectsCount;
}
Client::~Client() {
    Client::objectsCount -=1;
}

class Account{
private:
    int number;
    double interestRate{};

    Client *owner;

protected:
    double balance = 0;

public:
    Account(int n, Client *c);
    Account(int n, Client *c, double ir);

    int GetNumber() const;
    double GetBalance() const;
    double GetInterestRate() const;
    Client *GetOwner();

    virtual bool CanWithdraw(double a);

    void Deposit(double a);
    bool Withdraw(double a);
    void AddInterest(double ir);
};
Account::Account(int n, Client *c):number(n), owner(c){}
Account::Account(int n, Client *c, double ir):number(n), owner(c), interestRate(ir){}
int Account::GetNumber() const{
    return number;
}
double Account::GetBalance() const {
    return balance;
}
double Account::GetInterestRate() const {
    return interestRate;
}
Client *Account::GetOwner() {
    return owner;
}
bool Account::CanWithdraw(double a) {
    return (this->balance>= a);
}
void Account::Deposit(double a) {
    balance += a;
}
bool Account::Withdraw(double a) {
    bool success = false;
    if (this->CanWithdraw(a))
    {
        this->balance -=a;
        success = true;
    }
    return success;
}
void Account::AddInterest(double ir) {
    if (interestRate!=0)
        Deposit(balance*interestRate);
    else
        Deposit(balance*ir);
}

class CreditAccount : public Account
{
private:
    double credit;
public:
    CreditAccount(int n, Client *o, double c);
    CreditAccount(int n, Client *o, double ir, double c);

    bool CanWithdraw(double a) override;
};
bool CreditAccount::CanWithdraw(double a) {
    return (this->GetBalance() + this->credit >= a);
}
CreditAccount::CreditAccount(int n, Client *o, double c) : Account(n, o), credit(c) {}

int main() {
    auto *o = new Client(0, "Smith");
    auto *ca = new CreditAccount(1, o, 1000);

    cout << ca->CanWithdraw(1000) << endl;

    Account *a = ca;

    cout << a->CanWithdraw(1000) << endl;
    cout << ca->Withdraw(1000) << endl;

    a = nullptr;
    delete ca;


    return 0;
}