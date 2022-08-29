#ifndef __CUSTOMER_H
#define __CUSTOMER_H

#include <iostream>
#include <vector>
#include <fstream>

class Customer
{
  public:
    Customer(std::string name, std::string phone, std::string email);
    virtual void save(std::ostream &ost);
    Customer(std::istream &ist);
    friend std::ostream &operator<<(std::ostream &ost, const Customer &customer);
    std::string getCustomerName() { return _name; }

  protected:
    virtual std::string to_string() const;

  private:
    std::string _name;
    std::string _phone;
    std::string _email;
};

#endif
