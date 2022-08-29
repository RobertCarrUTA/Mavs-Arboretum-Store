#include "customer.h"

Customer::Customer(std::string name, std::string phone, std::string email)
    : _name{name}, _phone{phone}, _email{email} {}

void Customer::save(std::ostream &ost)
{
    ost << _name << '\n';
    ost << _phone << '\n';
    ost << _email << '\n';
}

Customer::Customer(std::istream &ist)
{
    std::getline(ist, _name);
    std::getline(ist, _phone);
    std::getline(ist, _email);
}

std::string Customer::to_string() const
{
    return _name + " (" + _phone + ", " + _email + ")";
}

std::ostream &operator<<(std::ostream &ost, const Customer &customer)
{
    ost << customer.to_string();
    return ost;
}

// void Customer::sortByCustomerName() {std::sort(_name.begin(), _name.end());}
